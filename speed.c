#include "speed.h"

uint32_t speedTime=0;
uint32_t speedTimeOut;
int speed=0;
extern uint16_t radius=0;
float n_circ=6031.0;
void initSPEED(void){

		initSYSTIMER();
		
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
		GPIOD->MODER &= ~0xFF000000;
		GPIOD->MODER |= 0xAA000000;
		GPIOD->AFR[1] |= 0x22220000;
		
		//TIM4 CH1,CH2,CH3,CH4 -> PD12,PD13,PD14,PD15
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
		
		TIM4->CR1 |= TIM_CR1_ARPE;
		TIM4->CR2 |= 0x00000000;
		TIM4->CNT = 0x0000;
		TIM4->ARR = N_CYCLES;
		TIM4->DIER = TIM_DIER_UIE;
		
		//TIM4->PSC = 0x00000053;
		TIM4->SMCR |= TIM_SMCR_TS_0 | TIM_SMCR_TS_2 | TIM_SMCR_SMS;
		 
		TIM4->CCR1 = 0x0000; 
		TIM4->CCR2 = 0x0000;
		TIM4->CCR3 = 0x0000;
		TIM4->CCR4 = 0x0000;
		
		TIM4->EGR |= TIM_EGR_UG;
		
		TIM4->CR1 |= TIM_CR1_CEN;
		
		NVIC_EnableIRQ(TIM4_IRQn);
		
		
		float prev=0;
		
		speedTime=getSYSTIMER();
		speedTimeOut=getSYSTIMER();
}

void setNCirc(uint16_t r){
	
	n_circ=N_CYCLES*2*r*PI;
}

void TIM4_IRQHandler(){
	if((TIM4->SR & TIM_SR_UIF)== TIM_SR_UIF){
		//float time=(getSYSTIMER()-speedTime)/N_CYCLES;
		float time=(getSYSTIMER()-speedTime);
		//speed=2.1*3*(1000/time)*3.6; //3 obima ? 
		speed= (int)(n_circ*3.6/time); // km/h
		
		speedTime=getSYSTIMER();
		speedTimeOut=getSYSTIMER();
	}
	
	TIM4->SR &= ~TIM_SR_UIF;
	
}
