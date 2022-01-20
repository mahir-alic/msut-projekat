#include "stm32f4xx.h"
#include "lcd16x2.h"
#include "usart.h"
#include "delay.h"


int main(void){
	
	//######## LCD simulation #####################
		
	initLCD();
	
		
	//#############################################
	
	while(1){
		posCursor(1,10); 
		printLCD("0123456789abcdef"); 
		
		for(uint8_t i=1; i<16; i++){
			posCursor(2,1);
			eraseNChar(16);
			posCursor(2,i);
			printLCD("ROW 2");
			delay_ms(100);
		}
		
	}
}

