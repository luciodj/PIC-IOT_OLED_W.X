/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "mcc.h"
#include "spi2_driver.h"

void (*spi2_interruptHandler)(void); 

inline void spi2_close(void)
{
    SPI2CON1Lbits.SPIEN = 0;
}

//con == SPIxCONL, brg == SPIxBRGL, operation == Master/Slave
typedef struct { uint16_t con1; uint16_t brg; uint8_t operation;} spi2_configuration_t;
static const spi2_configuration_t spi2_configuration[] = {   
    { 0x0120, 0x0000, 0 },
    { 0x0120, 0x003F, 0 }
};

bool spi2_open(spi2_modes spiUniqueConfiguration)
{
    if(!SPI2CON1Lbits.SPIEN)
    {
        SPI2CON1L = spi2_configuration[spiUniqueConfiguration].con1;
        SPI2BRGL = spi2_configuration[spiUniqueConfiguration].brg;
        
        TRISAbits.TRISA1 = spi2_configuration[spiUniqueConfiguration].operation;
        SPI2CON1Lbits.SPIEN = 1;
        return true;
    }
    return false;
}

// Full Duplex SPI Functions
uint8_t spi2_exchangeByte(uint8_t b)
{
    SPI2BUFL = b;
    while(!SPI2STATLbits.SPIRBF);
    return SPI2BUFL;
}

void spi2_exchangeBlock(void *block, size_t blockSize)
{
    uint8_t *data = block;
    while(blockSize--)
    {
        *data = spi2_exchangeByte(*data );
        data++;
    }
}

// Half Duplex SPI Functions
void spi2_writeBlock(void *block, size_t blockSize)
{
    uint8_t *data = block;
    while(blockSize--)
    {
        spi2_exchangeByte(*data++);
    }
}

void spi2_readBlock(void *block, size_t blockSize)
{
    uint8_t *data = block;
    while(blockSize--)
    {
        *data++ = spi2_exchangeByte(0);
    }
}

void spi2_writeByte(uint8_t byte)
{
    SPI2BUFL = byte;
}

uint8_t spi2_readByte(void)
{
    return SPI2BUFL;
}

/**
 * Interrupt from SPI on bit 8 received and SR moved to buffer
 * If interrupts are not being used, then call this method from the main while(1) loop
 */
void spi2_isr(void)
{
    if(IFS2bits.SPI2IF == 1){
        if(spi2_interruptHandler){
            spi2_interruptHandler();
        }
        IFS2bits.SPI2IF = 0;
    }
}

void spi2_setSpiISR(void(*handler)(void))
{
    spi2_interruptHandler = handler;
}

