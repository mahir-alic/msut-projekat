#include "rot-enc.h"

//TIM3
//TI2FP2 -> DT (PC7) CH2 ,TI1FP1 -> CLK (PC6) CH1
//001: Encoder mode 2 - Counter counts up/down on TI1FP1 edge depending on TI2FP2
//level

int rot=0;


void initRotEnc(void){
	//######### GPIO Config #############################
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    GPIOC->MODER |= 0x0000A000; //PC6, PC7 alternative function
    GPIOC->PUPDR |= 0x00005000;
    GPIOC->AFR[0]=0x22000000;
    //###################################################
    
    //######### TIM3 Config #############################
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
  
    TIM3->CR2 |= 0x00000000;
    TIM3->CNT = 0x0000;
    TIM3->ARR = 0xFFFF;
    
    TIM3->SMCR |= TIM_SMCR_SMS_1; //encoder mode 2  => count up/down on TI1FP1 depending on TI2FP2
    
    //CC2S bits are writable only when the channel is OFF (CC2E = 0 in TIMx_CCER).
    TIM3->CCMR1 |= TIM_CCMR1_CC2S_0 | TIM_CCMR1_CC1S_0 ; // ch1 mapped on TI1 , ch2 mapped on TI2

    TIM3->CCER &= ~(TIM_CCER_CC1NP);
    TIM3->CCER &= ~(TIM_CCER_CC1P);
   
    
      TIM3->CR1 |= TIM_CR1_CEN;
   
	//####################################################
	
	
	
}

int getRotEnc(void){
	
	if(TIM3->CNT>1 && TIM3->CNT<65535/2){
		TIM3->CNT-=2;
    
		return +1;
	}else if(TIM3->CNT<65535 && TIM3->CNT>(65535/2+1)){
		TIM3->CNT +=2;
    
		return -1;
	}else{
    
		return 0;
	}
	
}

