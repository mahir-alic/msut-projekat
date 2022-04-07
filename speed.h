#ifndef _SPEED_H
#define _SPEED_H

#include "stm32f4xx.h"

#define N_CYCLES 3
#define N_MAGNETS 1
#define PI 3.14159

#define TIM_IRQ_IDLE 0
#define TIM_IRQ_DETECTED 1

uint32_t speedTime;
uint32_t speedTimeOut;
extern int speed;
extern uint16_t radius;
void setNCirc(uint16_t);
extern uint32_t distance;
uint8_t tim_irq_state;
float time;

float n_circ;

void initSPEED(void);


#endif

