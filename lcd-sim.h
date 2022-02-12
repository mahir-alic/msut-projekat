#ifndef _LCDSIM_H
#define _LCDSIM_H

#include "stm32f4xx.h"
#include "usart.h"
#include "misc.h"
#include <stdarg.h>
#include "math.h"



//privremeni simulator lcd16x2 displeja

extern uint8_t r,c;

void initLCD();

void printLCD(char * str, ... );
void posCursor(uint8_t, uint8_t);
void eraseNChar(uint8_t);
void printLCDFloat(float);





#endif
