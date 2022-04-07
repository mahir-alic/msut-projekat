#include "lcd16x2.h"


uint8_t ddram_addr=0x00;

void initLCD(){
	
	delay_ms(100);
		
	txI2C2(0x4E,0x3C);
	txI2C2(0x4E,0x38); //interface is 8-bit long
	delay_ms(10);
		
	txI2C2(0x4E,0x3C);
	txI2C2(0x4E,0x38);
	delay_ms(10);
		
	txI2C2(0x4E,0x3C);
	txI2C2(0x4E,0x38);
		
	
	txI2C2(0x4E,0x2C);
	txI2C2(0x4E,0x28); //set inteface 4-bit long
		
	txI2C2(0x4E,0x2C);
	txI2C2(0x4E,0x28); 
	txI2C2(0x4E,0xCC);
	txI2C2(0x4E,0xC8);
	delay_ms(5); //  2 line interface and font
		
	txI2C2(0x4E,0x0C); 
	txI2C2(0x4E,0x08);
	txI2C2(0x4E,0x8C);
	txI2C2(0x4E,0x88); 
	delay_ms(5); //display off
		
	txI2C2(0x4E,0x0C); 
	txI2C2(0x4E,0x08);
	txI2C2(0x4E,0x1C);
	txI2C2(0x4E,0x18); 
	delay_ms(5); //clear display
		
	txI2C2(0x4E,0x0C);
	txI2C2(0x4E,0x08);
	txI2C2(0x4E,0xCC);
	txI2C2(0x4E,0xC8); //set cursor off blink off
	delay_ms(1000);
		
}

void sprintLCD(uint8_t * str)
{
	uint16_t k = 0;
		
	I2C2->CR1 |= I2C_CR1_START; //generate START condition
	//master waits for a read of the SR1 register
	//followed by a write in the DR register with the Slave address
		
	while((I2C2->SR1 & I2C_SR1_SB) != I2C_SR1_SB);
	I2C2 ->DR = addr; //write address	
		
	while((I2C2->SR1 & I2C_SR1_ADDR)!= I2C_SR1_ADDR);
	uint32_t x= I2C2->SR2;
	
	while (str[k] != '\0')
    {
        I2C2->DR = (str[k] & 0xF0)|0x0D;
         while((I2C2->SR1 & I2C_SR1_TXE)!= I2C_SR1_TXE);
		I2C2->DR = (str[k] & 0xF0)|0x09;
		 while((I2C2->SR1 & I2C_SR1_TXE)!= I2C_SR1_TXE);
		I2C2->DR = (str[k] & 0x0F)<<4|0x0D;
		 while((I2C2->SR1 & I2C_SR1_TXE)!= I2C_SR1_TXE);
		I2C2->DR = (str[k] & 0x0F)<<4|0x09;
		 while((I2C2->SR1 & I2C_SR1_TXE)!= I2C_SR1_TXE);
        if (str[k] == '\n')
        {
            //new line
		}
        k++;

        if (k == MAX_PRINT_STRING_SIZE)
            break;
    }
    
    while((I2C2->SR1 & I2C_SR1_TXE)!= I2C_SR1_TXE);
    
    I2C2->CR1 |= I2C_CR1_STOP;
}



void posCursor(uint8_t row, uint8_t column){
	
	
	if(row==1) ddram_addr=0x00+column-1;
	else if(row==2) ddram_addr=0x40+column-1;
	
	I2C2->CR1 |= I2C_CR1_START; //generate START condition
	//master waits for a read of the SR1 register
	//followed by a write in the DR register with the Slave address
		
	while((I2C2->SR1 & I2C_SR1_SB) != I2C_SR1_SB);
	I2C2 ->DR = addr; //write address
		
		
	while((I2C2->SR1 & I2C_SR1_ADDR)!= I2C_SR1_ADDR); //addres written
	uint32_t x= I2C2->SR2;
	
	//write instruction -----------------------------------------------
	I2C2->DR = 0x0C | 0x80 | (0x70&ddram_addr);
	while((I2C2->SR1 & I2C_SR1_TXE)!= I2C_SR1_TXE);
	I2C2->DR = 0x08 | 0x80 | (0x70&ddram_addr);
	while((I2C2->SR1 & I2C_SR1_TXE)!= I2C_SR1_TXE);
	I2C2->DR = 0x0C| ((0x0f&ddram_addr)<<4);
	while((I2C2->SR1 & I2C_SR1_TXE)!= I2C_SR1_TXE);
	I2C2->DR = 0x08 | ((0x0F&ddram_addr)<<4);
	while((I2C2->SR1 & I2C_SR1_TXE)!= I2C_SR1_TXE);
	
	//generate STOP condition -----------------------------------------
	
	I2C2->CR1 |= I2C_CR1_STOP;
	
	
}

void eraseNChar(uint8_t N){
	for(uint8_t i=0; i<N; i++){
		putcharLCD(' ');
	}
}


void printLCD(char *str, ... )
{ /// print text and up to 10 arguments!
    uint8_t rstr[40];													// 33 max -> 32 ASCII for 32 bits and NULL 
    uint16_t k = 0;
	uint16_t arg_type;
	uint32_t utmp32;
	uint32_t * p_uint32; 
	char * p_char;
	va_list vl;
	
	//va_start(vl, 10);													// always pass the last named parameter to va_start, for compatibility with older compilers
	va_start(vl, str);													// always pass the last named parameter to va_start, for compatibility with older compilers
	
	while(str[k] != 0x00)
	{
		if(str[k] == '%')
		{
			if(str[k+1] != 0x00)
			{
				switch(str[k+1])
				{
					case('b'):
					{// binary
						if(str[k+2] == 'b')
						{// byte
							utmp32 = va_arg(vl, int);
							arg_type = (PRINT_ARG_TYPE_BINARY_BYTE);
						}
						else if(str[k+2] == 'h')
						{// half word
							utmp32 = va_arg(vl, int);
							arg_type = (PRINT_ARG_TYPE_BINARY_HALFWORD);
						}
						else if(str[k+2] == 'w')
						{// word	
							utmp32 = va_arg(vl, uint32_t);
							arg_type = (PRINT_ARG_TYPE_BINARY_WORD);
						}
						else
						{// default word
							utmp32 = va_arg(vl, uint32_t);
							arg_type = (PRINT_ARG_TYPE_BINARY_WORD);
							k--;
						}
						
						k++;	
						p_uint32 = &utmp32;
						break;
					}
					case('d'):
					{// decimal
						if(str[k+2] == 'b')
						{// byte
							utmp32 = va_arg(vl, int);
							arg_type = (PRINT_ARG_TYPE_DECIMAL_BYTE);
						}
						else if(str[k+2] == 'h')
						{// half word
							utmp32 = va_arg(vl, int);
							arg_type = (PRINT_ARG_TYPE_DECIMAL_HALFWORD);
						}
						else if(str[k+2] == 'w')
						{// word	
							utmp32 = va_arg(vl, uint32_t);
							arg_type = (PRINT_ARG_TYPE_DECIMAL_WORD);
						}
						else
						{// default word
							utmp32 = va_arg(vl, uint32_t);
							arg_type = (PRINT_ARG_TYPE_DECIMAL_WORD);
							k--;
						}
						
						k++;	
						p_uint32 = &utmp32;
						break;
					}
					case('c'):
					{// character
						char tchar = va_arg(vl, int);	
						//
						arg_type = (PRINT_ARG_TYPE_CHARACTER);
						break;
					}
					case('s'):
					{// string 
						p_char = va_arg(vl, char *);	
						//
						sprintLCD((uint8_t *)p_char);
						arg_type = (PRINT_ARG_TYPE_STRING);
						break;
					}
					case('f'):
					{// float
						uint64_t utmp64 = va_arg(vl, uint64_t);			// convert double to float representation IEEE 754
						uint32_t tmp1 = utmp64&0x00000000FFFFFFFF;
						tmp1 = tmp1>>29;
						utmp32 = utmp64>>32;
						utmp32 &= 0x07FFFFFF;
						utmp32 = utmp32<<3;
						utmp32 |= tmp1;
						if(utmp64 & 0x8000000000000000)
							utmp32 |= 0x80000000;
							
						if(utmp64 & 0x4000000000000000)
							utmp32 |= 0x40000000;
							
						p_uint32 = &utmp32;
						
						arg_type = (PRINT_ARG_TYPE_FLOAT);
						//arg_type = (PRINT_ARG_TYPE_HEXADECIMAL_WORD);
						//arg_type = (PRINT_ARG_TYPE_BINARY_WORD);
						break;
					}
					case('x'):
					{// hexadecimal 
						if(str[k+2] == 'b')
						{// byte
							utmp32 = (uint32_t)va_arg(vl, int);
							arg_type = (PRINT_ARG_TYPE_HEXADECIMAL_BYTE);
						}
						else if(str[k+2] == 'h')
						{// half word
							utmp32 = (uint32_t)va_arg(vl, int);
							arg_type = (PRINT_ARG_TYPE_HEXADECIMAL_HALFWORD);
						}
						else if(str[k+2] == 'w')
						{// word	
							utmp32 = va_arg(vl, uint32_t);
							arg_type = (PRINT_ARG_TYPE_HEXADECIMAL_WORD);
						}
						else
						{
							utmp32 = va_arg(vl, uint32_t);
							arg_type = (PRINT_ARG_TYPE_HEXADECIMAL_WORD);
							k--;
						}
						
						k++;
						p_uint32 = &utmp32;
						break;
					}
					default:
					{
						utmp32 = 0;
						p_uint32 = &utmp32;
						arg_type = (PRINT_ARG_TYPE_UNKNOWN);
						break;
					}
				}
					
				if(arg_type&(PRINT_ARG_TYPE_MASK_CHAR_STRING))	
				{
					getStr4NumMISC(arg_type, p_uint32, rstr);
						
					sprintLCD(rstr);
				}
				k++;
			}
		}
		else
		{// not a '%' char -> print the char
			putcharLCD(str[k]);
			if (str[k] == '\n')
				putcharLCD(str[k]);
		}
		k++;
	}
	
	va_end(vl);
	return;
}

void putcharLCD(uint8_t data){
	I2C2->CR1 |= I2C_CR1_START; //generate START condition
	//master waits for a read of the SR1 register
	//followed by a write in the DR register with the Slave address
		
	while((I2C2->SR1 & I2C_SR1_SB) != I2C_SR1_SB);
	I2C2 ->DR = addr; //write address
		
	while((I2C2->SR1 & I2C_SR1_ADDR)!= I2C_SR1_ADDR); //address written
	uint32_t x= I2C2->SR2;
	
	I2C2->DR = (data & 0xF0)|0x0D;
	while((I2C2->SR1 & I2C_SR1_TXE)!= I2C_SR1_TXE);
	I2C2->DR = (data & 0xF0)|0x09;
	while((I2C2->SR1 & I2C_SR1_TXE)!= I2C_SR1_TXE);
	I2C2->DR = (data & 0x0F)<<4|0x0D;
	while((I2C2->SR1 & I2C_SR1_TXE)!= I2C_SR1_TXE);
	I2C2->DR = (data & 0x0F)<<4|0x09;
	while((I2C2->SR1 & I2C_SR1_TXE)!= I2C_SR1_TXE);
    
	I2C2->CR1 |= I2C_CR1_STOP; //generate STOP condition
}

printLCDFloat(float x){
	int dec=x;
	int frac=abs(round((x-dec)*100));
	if(x>-1.0 && x<0.0) printLCD("-%d.%d",dec,frac);
	else printLCD("%d.%d",dec,frac);
}

void clearLCD(void){
	txI2C2(0x4E,0x0C); 
	txI2C2(0x4E,0x08);
	txI2C2(0x4E,0x1C);
	txI2C2(0x4E,0x18); 
	//delay_ms(10);
		 //clear display
}


