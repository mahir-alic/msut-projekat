#ifndef _LCD16x2_H
#define _LCD16x2_H

#include "stm32f4xx.h"
#include "usart.h"



//privremeni simulator lcd16x2 displeja

extern uint8_t r,c;

void initLCD();

void printLCD(char * str, ... );
void posCursor(uint8_t, uint8_t);
void eraseNChar(uint8_t);



#endif
