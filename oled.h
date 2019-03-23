/*
 * File: oled.h
*/
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/spi2_driver.h"
#include "mcc_generated_files/drivers/spi_master.h"

#include "oled_config.h"

#define OLED_WIDTH             96
#define OLED_HEIGHT            39


#define OLED_TIMEOUT    10
extern uint8_t OLED_Timer;

void OLED_Command(uint8_t);

void OLED_Data(uint8_t);

void OLED_init(void);

// Set row
void OLED_SetRow(uint8_t);

// Set column
void OLED_SetColumn(uint8_t);

// Set scaling factors
void OLED_SetScale(uint8_t, uint8_t);

// Display picture form array in memory
void OLED_PutPicture(const uint8_t *);

// control contrast in steps  from 1 to 256
void OLED_SetContrast(uint8_t);

void OLED_Putchar(char ch);

void OLED_Puts(char x, char y, char *s);

void OLED_Clear(void);