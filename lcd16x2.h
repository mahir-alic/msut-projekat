6#ifndef _LCD16x2_H
#define _LCD16x2_H

#include "stm32f4xx.h"
#include "usart.h"
#include "misc.h"
#include "i2c.h"
#include <stdarg.h>

#define addr 0x4E





extern uint8_t r,c;

void initLCD();

void clearLCD(void);
void printLCD(char * str, ... );
void sprintLCD(uint8_t * str);
void putcharLCD(uint8_t data);
void posCursor(uint8_t, uint8_t);
void eraseNChar(uint8_t);
void printLCDFloat(float);





#endif
