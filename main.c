/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system intialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.95-b-SNAPSHOT
        Device            :  PIC24FJ128GA705
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.36
        MPLAB 	          :  MPLAB X v5.10
*/

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

/**
  Section: Included Files
*/
#include "mcc_generated_files/system.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "mcc_generated_files/led.h"
#include "mcc_generated_files/sensors_handling.h"
#include "mcc_generated_files/cloud/cloud_service.h"
#include "mcc_generated_files/application_manager.h"
#include "mcc_generated_files/debug_print.h"

#include "oled.h"
uint8_t OLED_Timer = 0;

//This handles messages published from the MQTT server when subscribed
void receivedFromCloud(uint8_t *topic, uint8_t *payload)
{
    char *pT, c;

    if ((pT = strstr((char*)payload, "text1\":\""))){
        pT+=8;
        OLED_Clear();
        OLED_SetScale(1, 2);
        while((c = *pT++) && (c!='"')) {
            OLED_Putchar(c);
        }
        OLED_Timer = OLED_TIMEOUT;
    }
    else {
        debug_printer(SEVERITY_NONE, LEVEL_NORMAL, "payload: %s", payload);
    }
}

// This will get called every CFG_SEND_INTERVAL only while we have a valid Cloud connection
void sendToCloud(void)
{
   static char json[70];

   int rawTemperature = SENSORS_getTempValue();
   int light = SENSORS_getLightValue();
   int len = sprintf(json, "{\"Light\":%d,\"Temp\":\"%d.%02d\"}", light,rawTemperature/100,abs(rawTemperature)%100);

   if (len >0) {
      CLOUD_publishData((uint8_t*)json, len);
      LED_flashYellow();
   }

   if (OLED_Timer > 0) {
        OLED_Timer--;
        if (OLED_Timer == 0){
            OLED_Clear();
        }
    }
}

//#include "mcc_generated_files/drivers/spi_master.h"

/*
                         Main application
 */
int main(void)
{
    SYSTEM_Initialize();
    application_init();

    OLED_init();
    OLED_Clear();
    OLED_SetScale(2, 4); OLED_Puts(0,0, "PIC-IoT");
    OLED_Timer = OLED_TIMEOUT;

    while (1)
    {
        // Add your application code
        runScheduler();
    }

    return 1;
}
/**
 End of File
*/

