#ifndef I2C_H_
#define I2C_H_

#include "stm32f4xx.h"

void initI2C2(void);

void txI2C2(uint8_t,uint8_t);

#endif
