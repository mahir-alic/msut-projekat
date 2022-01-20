#include "stm32f4xx.h"
#include "lcd16x2.h"
#include "usart.h"
#include "delay.h"


uint8_t speed=0;

int main(void){
	
	//######## LCD simulation #####################
		
	initLCD();
	

		
	//#############################################
	
	while(1){
	
		
		
		posCursor(1,4);
		printLCD("MSUT");
		for(int i=0; i<5; i++){
			posCursor(2,1);
			eraseNChar(16);
			posCursor(2,1);
		printLCD("SPEED: %d",speed);
		
		speed+=5;
		delay_ms(1000);
		}
		speed=0;
	}
}

