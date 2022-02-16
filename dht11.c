#include "dht11.h"


uint8_t RH_integral=0;
		uint8_t RH_decimal=0;
		uint8_t T_integral=0;
		uint8_t T_decimal=0;
		uint8_t chksum=0;
		uint32_t dht11_data=0;
//uint8_t pin=0;



void dht11Config(){
	
	//pin=dhtPin;
	
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
	
	GPIOE->MODER |= (0x1<<(2*pin)); //config dhtPin as output
	GPIOE->OTYPER |= (0x1<<pin); //dhtPin push-pull type 
	GPIOE->OSPEEDR |=(0x3<<(2*pin)); //max speed;
	
	//TIMER config #########################################
		RCC-> APB1ENR |= RCC_APB1ENR_TIM14EN;
		//TIM2-> PSC |= 0x00000000; //clock = 84 MHz
		TIM14-> PSC = 0x00000053; //counter frequency 1 MHz (0x53 -> 83 dec) (fcnt = fclk/(1+PSC))
		TIM14->CNT = 0x0000;
		TIM14->ARR = 0xFFFF;
		TIM14-> EGR |= 0x00000001;
		
		//###################################################### 
}


 struct dht11Data dht11Read(){
			GPIOE->MODER &= ~(0x3<<(2*pin)); //
		GPIOE->MODER |= 0x1<<(2*pin);
		
		GPIOE->ODR &= ~(0x1<<pin); //pull data line low

		 TIM14->CNT = 0x0000;
		 TIM14->CR1 |= TIM_CR1_CEN;
		 while(TIM14->CNT <= 0x4650){
			 									//delay 18 ms;
		 }
	 	 TIM14->CR1 &= ~TIM_CR1_CEN;
	 	

	
		
		GPIOE->ODR |= 0x1<<pin; // pull data line high

		GPIOE->MODER &= ~(0x3<<(2*pin)); //configure gpio as input

		uint8_t state=0;
		uint8_t i=0;
		
		 
		uint32_t t5=getSYSTIMER(); 
		
		while(i<40)
		{
			
			if(chk4TimeoutSYSTIMER(t5,6)==SYSTIMER_TIMEOUT){
				//communication fail
				i=40;
			}
			
			if(state==0){ //wait for response (pull data line low)
				if((GPIOE->IDR & (0x1<<pin))==0x0000){
					state=1;
					
				}
				
			
			}
			else if(state==1){
					if((GPIOE->IDR & (0x1<<pin))==(0x1<<pin)){
						//wait for high pulse
						state=2;
						
					}
			}
			else if(state==2){
					if((GPIOE->IDR & (0x1<<pin))==0x0000){
						//wait for low pulse
						state=3;
					}
			}
			else if(state==3){
					//wait for data bit
					if((GPIOE->IDR & (0x1<<pin))==(0x1<<pin))
					{
						TIM14->CNT=0x0000;
						TIM14->CR1 |= TIM_CR1_CEN;
						state=4;
			}
			}
			else if (state==4){
					//measure high pulse length
					while((GPIOE->IDR & (0x1<<pin))==(0x1<<pin)){

					}
					TIM14->CR1 &= ~TIM_CR1_CEN;

					if(TIM14->CNT <= 0x0032){
						//'0' received
						dht11_data = (dht11_data<<1) & ~0x1;

					} else if(TIM14->CNT >0x0032){
						//'1' received
						dht11_data = (dht11_data<<1) | 0x1;
					}
					i=i+1;
					if(i>=32){
						state=5;
					} else {
						state=3;
					}
					
			}
			else if(state==5){
					//wait for checksum bit
					if((GPIOE->IDR & (0x1<<pin))==(0x1<<pin))
					{
						TIM14->CNT=0x0000;
						TIM14->CR1 |= TIM_CR1_CEN;
						
						state=6;
				}
			}				
			else if(state==6){
					//measure high pulse length
					while((GPIOE->IDR & (0x1<<pin))==(0x1<<pin)){

					}
					TIM14->CR1 &= ~TIM_CR1_CEN;
					if(TIM14->CNT <= 0x0032){
						//'0' received
						chksum = (chksum<<1) & ~0x1;

					} else if(TIM14->CNT >0x0032){
						//'1' received
						chksum = (chksum<<1) | 0x1;
					}
					i=i+1;
					
					if(i>=40){
						state=0;
						 
					} else {
						state=5;
					}

			}
			//packet received
		}
		
		struct dht11Data data;

		data.RH_integral = (dht11_data & 0xFF000000)>>24;
		data.RH_decimal = (dht11_data & 0x00FF0000)>>16;
		data.T_integral = (dht11_data & 0x0000FF00)>>8;
		data.T_decimal = (dht11_data & 0x000000FF);
		
		return data;
		
	
}
