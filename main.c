#include "stm32f4xx.h"
#include "lcd16x2.h"
#include "usart.h"
#include "delay.h"
#include "rot-enc.h"



uint8_t speed=0;

int main(void){
	
	//######## LCD simulation #####################
		
	initLCD();
			
	//#############################################
	
	//######## ROTARY ENCODER #####################
	
	initRotEnc();
	
	//#############################################
	
	int radius=0;
	
	posCursor(1,6);
		printLCD("MSUT");
	posCursor(2,1);
	eraseNChar(16);
	posCursor(2,1);
	printLCD("RADIUS: %d mm",radius);
	
	
	while(1){
	
		
		
		
		int tmp = radius + 1* getRotEnc();
		if(tmp!=radius){
			radius=tmp;
			posCursor(2,9);
			eraseNChar(7);
			posCursor(2,9);
			printLCD("%d mm",radius);
		}
		
		
		
	}
}

