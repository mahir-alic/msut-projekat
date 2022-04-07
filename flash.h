#ifndef _FLASH_H
#define _FLASH_H

#include "stm32f4xx.h"

void unlockFlash(void);
void lockFlash(void);
void eraseFlash(void);
void write2Flash(uint32_t*,uint32_t);
uint32_t readFlash(uint32_t*);

#endif
