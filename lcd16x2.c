#include "lcd16x2.h"

uint8_t r=1,c=1;

void initLCD(){
	initUSART2(USART2_BAUDRATE_115200);
	
	//clearScreen();
	putcharUSART2(0x1B);
	putcharUSART2('c');
	printUSART2("\e[?25l");//hide cursor
	printUSART2("\e[34m");//set color     //31 red, 32 green, 33 yellow, 34 blue
	
	printUSART2("|----------------|\n");
	printUSART2("|                |\n");
	printUSART2("|                |\n");
	printUSART2("|----------------|\n");
	
	
}

void printLCD(char * str, ... ){
	uint8_t n= 16-c+1;
	
	char tmp[n+1];
	tmp[n]='\0';
	for(uint8_t i=0; i<n; i++){
		tmp[i]= *str;
		str++;
	}
	printUSART2(tmp);
	//printUSART2(str);


}

void posCursor(uint8_t row, uint8_t column){
	r=row;
	c=column;
	printUSART2("\033[%d;%dH",row+1,column+1);	
}

void eraseNChar(uint8_t N){
	for(uint8_t i=0; i<N; i++){
		putcharUSART2(' ');
	}
}
