#include "rot-enc.h"

//TIM3
//TI2FP2 -> DT (PC7) CH2 ,TI1FP1 -> CLK (PC6) CH1
//001: Encoder mode 1 - Counter counts up/down on TI2FP2 edge depending on TI1FP1
//level


void rotEncInit(void){
	//GPIO Config
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	
	GPIOC -> MODER |= GPIO_MODER_MODER6_1 | GPIO_MODER_MODER7_1;
	GPIOC ->AFR[0] &= ~0xFF000000;
	GPIOC ->AFR[0] |= 0x22000000; //TIM3-> CH1 CH2
	
	//--------------------------------------
	
	
}
