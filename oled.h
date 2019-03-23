/*
 * File: oled.h
*/
#include "mcc_generated_files/mcc.h"

#include "oled_config.h"

#define OLED_WIDTH             96
#define OLED_HEIGHT            39

extern uint8_t OLED_Timer;

void OLED_init(void);
void OLED_SetRow(uint8_t);
void OLED_SetColumn(uint8_t);
void OLED_SetScale(uint8_t, uint8_t);
void OLED_Putchar(char ch);
void OLED_Puts(char x, char y, char *s);
void OLED_Clear(void);

// Display picture form array in memory
void OLED_PutPicture(const uint8_t *);
// control contrast in steps  from 1 to 256
void OLED_SetContrast(uint8_t);
