/*
 *  File: oled_config.h
 *
 *  Description: adapter for PIC-IOT WG board mikroBUS socket
 */

#include "mcc_generated_files/delay.h"
#include "mcc_generated_files/spi2_driver.h"
#include "mcc_generated_files/drivers/spi_master.h"

#define OLED_TIMEOUT    10 // periods

#define OLED_CS(state)      LATAbits.LATA0 = state      // CS
#define OLED_DC(state)      LATCbits.LATC6 = state      // PWM
#define OLED_RST(state)     LATBbits.LATB15 = state     // RST
#define SPI_Write(data)     spiMaster[OLED].exchangeByte(data)
