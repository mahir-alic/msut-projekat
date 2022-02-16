#include "speed.h"

uint32_t speedTime=0;
uint32_t speedTimeOut;
int speed=0;
uint16_t radius=0;
float n_circ=0.0;
float distance=0.0;



void initSPEED(void){

		initSYSTIMER();
		
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
		GPIOA->MODER &= ~0x00000FF;
		GPIOA->MODER |= 0x000000A0;
		GPIOA->AFR[0] |= 0x00000300;
		
		//TIM4 CH1,CH2,CH3,CH4 -> PD12,PD13,PD14,PD15
		RCC->APB2ENR |= RCC_APB2ENR_TIM9EN;
		
		TIM9->CR1 |= TIM_CR1_ARPE;
		TIM9->CR2 |= 0x00000000;
		TIM9->CNT = 0x0000;
		TIM9->ARR = N_CYCLES;
		TIM9->DIER = TIM_DIER_UIE;
		
		//TIM4->PSC = 0x00000053;
		TIM9->SMCR |= TIM_SMCR_TS_0 | TIM_SMCR_TS_2 | TIM_SMCR_SMS;
		 
		TIM9->CCR1 = 0x0000; 
		TIM9->CCR2 = 0x0000;
		TIM9->CCR3 = 0x0000;
		TIM9->CCR4 = 0x0000;
		
		TIM9->EGR |= TIM_EGR_UG;
		
		TIM9->CR1 |= TIM_CR1_CEN;
		
		NVIC_EnableIRQ(TIM1_BRK_TIM9_IRQn);
		
		
		float prev=0;
		
		speedTime=getSYSTIMER();
		speedTimeOut=getSYSTIMER();
}

void setNCirc(uint16_t r){
	
	n_circ=N_CYCLES*2*r*PI;
}

void TIM1_BRK_TIM9_IRQHandler(){
	if((TIM9->SR & TIM_SR_UIF)== TIM_SR_UIF){
		float time=(getSYSTIMER()-speedTime); 
		speed= (int)(n_circ*3.6/time); // km/h
		
		speedTime=getSYSTIMER();
		speedTimeOut=getSYSTIMER();
		distance+=n_circ/1000;
	}
	
	TIM9->SR &= ~TIM_SR_UIF;
	
}

