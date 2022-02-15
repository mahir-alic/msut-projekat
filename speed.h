#ifndef _SPEED_H
#define _SPEED_H

#include "stm32f4xx.h"

#define N_CYCLES 3
#define PI 3.14159

uint32_t speedTime;
uint32_t speedTimeOut;
extern int speed;
extern uint16_t radius;
void setNCirc(uint16_t);
extern float distance;

float n_circ;

void initSPEED(void);

#endif
