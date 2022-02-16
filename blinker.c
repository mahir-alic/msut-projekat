#include "blinker.h"

#define OFF 0
#define BLINK_DUTY 800
#define HEAD_LIGHT_DUTY 400

//void right(void);
//void left(void);
//void light(void);

void initBlink(void)
{
///wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
	/// setup PWM on TIM4 CH1, CH2, CH3 & CH4 -> PD12, PD13, PD14 & PD15
	///----------------------------------------------------------------
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;  								//
    GPIOD->MODER |= 0xAA000000;             							//
    GPIOD->OTYPER |= 0x00000000; 										//
	GPIOD->AFR[1] |= 0x22220000;
	GPIOD->OSPEEDR |= 0xFF000000;										//  
	
	 
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN; 							// enable TIM4 on APB1 
		TIM4->PSC = 0xA410 - 0x0001;									// set TIM4 counting prescaler 
																		// 84MHz/42k = 2kHz -> count each 1us
		TIM4->ARR = 0x0640;												// period of the PWM 800ms
		
		TIM4->CCR1 = 0x0000;											// duty cycle for the PWM set to 50%
		TIM4->CCR2 = 0x0000;
	//	TIM4->CCR3 = 0x0000;
	//	TIM4->CCR4 = 0x0000;
		
		TIM4->CCMR1 |= (TIM_CCMR1_OC1PE)|(TIM_CCMR1_OC1M_2)|(TIM_CCMR1_OC1M_1);
		TIM4->CCMR1 |= (TIM_CCMR1_OC2PE)|(TIM_CCMR1_OC2M_2)|(TIM_CCMR1_OC2M_1);	
		TIM4->CCMR2 |= (TIM_CCMR2_OC3PE)|(TIM_CCMR2_OC3M_2)|(TIM_CCMR2_OC3M_1);	
		TIM4->CCMR2 |= (TIM_CCMR2_OC4PE)|(TIM_CCMR2_OC4M_2)|(TIM_CCMR2_OC4M_1);					
																			// set PWM 1 mod, enable OC1PE preload mode 
																			
		// set active mode high for pulse polarity
		TIM4->CCER &= ~((TIM_CCER_CC1P)|(TIM_CCER_CC2P)|(TIM_CCER_CC3P)|(TIM_CCER_CC4P));
		TIM4->CR1 |= (TIM_CR1_ARPE)|(TIM_CR1_URS);
		
		// update event, reload all config 
		TIM4->EGR |= TIM_EGR_UG;											
		// activate capture compare mode
		TIM4->CCER |= (TIM_CCER_CC1E)|(TIM_CCER_CC2E)|(TIM_CCER_CC3E)|(TIM_CCER_CC4E);
		// start counter										
		TIM4->CR1 |= TIM_CR1_CEN;											
	}

void right(void) {
	TIM4->CCR1 = OFF;
	TIM4->CCR2 = BLINK_DUTY;
}
void left(void) {
	TIM4->CCR2 = OFF;
	TIM4->CCR1 = BLINK_DUTY;
}
void light(void) {
	TIM4->CCR3 = HEAD_LIGHT_DUTY;	
}
