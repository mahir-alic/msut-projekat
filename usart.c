#include "usart.h"


volatile uint8_t g_usart2_buffer[USART2_BUFFER_SIZE];
volatile uint16_t g_usart2_widx = 0;
volatile uint16_t g_usart2_ridx = ((USART2_BUFFER_SIZE) - 1);

volatile uint8_t g_usart3_buffer[USART3_BUFFER_SIZE];
volatile uint16_t g_usart3_widx = 0;
volatile uint16_t g_usart3_ridx = ((USART3_BUFFER_SIZE) - 1);

volatile uint8_t cmd=0;


void initUSART2(uint32_t baudrate)
{
	//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
	// USART2: PA2 -> TX & PA3 -> RX
	//------------------------------------------------------------------ 
	
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; 									
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN; 									
	GPIOA->MODER |= (GPIO_MODER_MODER2_1)|(GPIO_MODER_MODER3_1); 		
	GPIOA->AFR[0] |= 0x00007700;										
	
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR2_1;							  
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR3_1;							  
															
	USART2->BRR = baudrate;
	USART2->CR1 = USART_CR1_UE|USART_CR1_TE;							
}

void enIrqUSART2(void)
{
	USART2->CR1 &= ~(USART_CR1_UE);
	
	NVIC_EnableIRQ(USART2_IRQn);
	USART2->CR1 |= (USART_CR1_UE)|(USART_CR1_RE)|(USART_CR1_RXNEIE);
}

void disIrqUSART2(void)
{
	USART2->CR1 &= ~((USART_CR1_UE)|(USART_CR1_RXNEIE));
	
	NVIC_DisableIRQ(USART2_IRQn);
	USART2->CR1 |= (USART_CR1_UE);
}

void putcharUSART2(uint8_t data)
{/// print one character to USART2
	while(!(USART2->SR & USART_SR_TC));									
	
	USART2->DR = data;												    
}

void printUSART2(char *str, ... )
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
						putcharUSART2(tchar);
						arg_type = (PRINT_ARG_TYPE_CHARACTER);
						break;
					}
					case('s'):
					{// string 
						p_char = va_arg(vl, char *);	
						sprintUSART2((uint8_t *)p_char);
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
					sprintUSART2(rstr);	
				}
				k++;
			}
		}
		else
		{// not a '%' char -> print the char
			putcharUSART2(str[k]);
			if (str[k] == '\n')
				putcharUSART2('\r');
		}
		k++;
	}
	
	va_end(vl);
	return;
}

void sprintUSART2(uint8_t * str)
{
	uint16_t k = 0;
	
	while (str[k] != '\0')
    {
        putcharUSART2(str[k]);
        if (str[k] == '\n')
            putcharUSART2('\r');
        k++;

        if (k == MAX_PRINT_STRING_SIZE)
            break;
    }
}

#ifdef USART_ECHO
void USART2_IRQHandler(void)
{
	uint8_t data;
	
	if(USART2->SR&(USART_SR_RXNE))
	{
		data = USART2->DR;
		//USART3->SR &= ~(USART_SR_RXNE);
		USART2->DR = data;
	}
}
#else



void USART2_IRQHandler(void)
{
	uint8_t data;

	if(USART2->SR&(USART_SR_RXNE))
	{
		g_usart2_buffer[g_usart2_widx] = USART2->DR;
		g_usart2_widx++;
		if(g_usart2_widx >= (USART2_BUFFER_SIZE))
		{
			g_usart2_widx = 0;
		}
	}
}

#endif
void chkRxBuffUSART2(void)
{
	uint16_t t_usart2_ridx = g_usart2_ridx;

	t_usart2_ridx++;
	if(t_usart2_ridx >= (USART2_BUFFER_SIZE))
	{
		t_usart2_ridx = 0;
	}

	if(t_usart2_ridx != g_usart2_widx)
	{
		USART2->DR = g_usart2_buffer[t_usart2_ridx];
		g_usart2_ridx = t_usart2_ridx;
	}

}

void putTxBuffUSART3(uint8_t x)
{
	
	g_usart3_buffer[g_usart3_widx] = x;

	g_usart3_widx++;
		if(g_usart3_widx >= (USART3_BUFFER_SIZE))
		{
			g_usart3_widx = 0;
		}
	

}




uint8_t chk4Cmd(void)
{	
	uint8_t command=0;
	//putcharUSART2(g_usart2_buffer[g_usart2_ridx]);
	uint16_t t_usart2_ridx=g_usart2_ridx;
	
	
	t_usart2_ridx++;
		if(t_usart2_ridx >= (USART2_BUFFER_SIZE))
	{
		t_usart2_ridx = 0;
	}
	
	if(t_usart2_ridx != g_usart2_widx)
	{
		
		if(g_usart2_buffer[t_usart2_ridx]==0x1B && cmd==0){
			cmd=1;
		}else if(g_usart2_buffer[t_usart2_ridx]==0x5B && cmd==1){
			cmd=2;
		}else if(cmd==2){
				if(g_usart2_buffer[t_usart2_ridx]=='A')
					command=1;
				else if(g_usart2_buffer[t_usart2_ridx]=='B')
					command=2;
				else if(g_usart2_buffer[t_usart2_ridx]=='C')
					command=3;
				else if(g_usart2_buffer[t_usart2_ridx]=='D')
					command=4;
			
			cmd=0;
		}else cmd=0; 
		
		//USART2->DR = g_usart2_buffer[t_usart2_ridx];
		g_usart2_ridx=t_usart2_ridx;
	
	//return command;
	}
	return command;
	
}

uint8_t getcharUSART2(void)
{/// get one character from USART1
	uint8_t data;
	USART2->CR1 |= USART_CR1_UE|USART_CR1_RE;							// enable usart	and Rx
	while((USART2->SR & USART_SR_RXNE) != USART_SR_RXNE);				// wait until data ready
	
	data = USART2->DR;													// send data
	USART2->SR &= ~(USART_SR_RXNE);										// clear Rx data ready flag
	USART2->CR1 &= ~(USART_CR1_RE);
	return data;
}




///############## USART 3 ####################################################

void initUSART3(uint32_t baudrate)
{
	//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
	// USART3: PD8 -> TX & PD9 -> RX
	//------------------------------------------------------------------ 
	
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; 									
	RCC->APB1ENR |= RCC_APB1ENR_USART3EN; 		
	GPIOD->MODER &= ~(GPIO_MODER_MODER8 || GPIO_MODER_MODER9);							
	GPIOD->MODER |= (GPIO_MODER_MODER8_1)|(GPIO_MODER_MODER9_1);	
	GPIOD->AFR[1] |= 0x00000077;										
	
	GPIOD->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR8_1;							  
	GPIOD->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR9_1;							  
															
	USART3->BRR = baudrate;
	USART3->CR1 = USART_CR1_UE|USART_CR1_TE;							
}

//void enIrqUSART3(void)
//{
	//USART3->CR1 &= ~(USART_CR1_UE);
	
	//NVIC_EnableIRQ(USART3_IRQn);
	//USART3->CR1 |= (USART_CR1_UE)|(USART_CR1_RE)|(USART_CR1_RXNEIE);
//}

void disIrqUSART3(void)
{
	USART3->CR1 &= ~((USART_CR1_UE)|(USART_CR1_RXNEIE));
	
	NVIC_DisableIRQ(USART3_IRQn);
	USART3->CR1 |= (USART_CR1_UE);
}

void putcharUSART3(uint8_t data)
{/// print one character to USART2
	while(!(USART3->SR & USART_SR_TC));									
	
	USART3->DR = data;												    
}

//void printUSART3(char *str, ... )
//{ /// print text and up to 10 arguments!
    //uint8_t rstr[40];													// 33 max -> 32 ASCII for 32 bits and NULL 
    //uint16_t k = 0;
	//uint16_t arg_type;
	//uint32_t utmp32;
	//uint32_t * p_uint32; 
	//char * p_char;
	//va_list vl;
	
	////va_start(vl, 10);													// always pass the last named parameter to va_start, for compatibility with older compilers
	//va_start(vl, str);													// always pass the last named parameter to va_start, for compatibility with older compilers
	//while(str[k] != 0x00)
	//{
		//if(str[k] == '%')
		//{
			//if(str[k+1] != 0x00)
			//{
				//switch(str[k+1])
				//{
					//case('b'):
					//{// binary
						//if(str[k+2] == 'b')
						//{// byte
							//utmp32 = va_arg(vl, int);
							//arg_type = (PRINT_ARG_TYPE_BINARY_BYTE);
						//}
						//else if(str[k+2] == 'h')
						//{// half word
							//utmp32 = va_arg(vl, int);
							//arg_type = (PRINT_ARG_TYPE_BINARY_HALFWORD);
						//}
						//else if(str[k+2] == 'w')
						//{// word	
							//utmp32 = va_arg(vl, uint32_t);
							//arg_type = (PRINT_ARG_TYPE_BINARY_WORD);
						//}
						//else
						//{// default word
							//utmp32 = va_arg(vl, uint32_t);
							//arg_type = (PRINT_ARG_TYPE_BINARY_WORD);
							//k--;
						//}
						
						//k++;	
						//p_uint32 = &utmp32;
						//break;
					//}
					//case('d'):
					//{// decimal
						//if(str[k+2] == 'b')
						//{// byte
							//utmp32 = va_arg(vl, int);
							//arg_type = (PRINT_ARG_TYPE_DECIMAL_BYTE);
						//}
						//else if(str[k+2] == 'h')
						//{// half word
							//utmp32 = va_arg(vl, int);
							//arg_type = (PRINT_ARG_TYPE_DECIMAL_HALFWORD);
						//}
						//else if(str[k+2] == 'w')
						//{// word	
							//utmp32 = va_arg(vl, uint32_t);
							//arg_type = (PRINT_ARG_TYPE_DECIMAL_WORD);
						//}
						//else
						//{// default word
							//utmp32 = va_arg(vl, uint32_t);
							//arg_type = (PRINT_ARG_TYPE_DECIMAL_WORD);
							//k--;
						//}
						
						//k++;	
						//p_uint32 = &utmp32;
						//break;
					//}
					//case('c'):
					//{// character
						//char tchar = va_arg(vl, int);	
						//putcharUSART3(tchar);
						//arg_type = (PRINT_ARG_TYPE_CHARACTER);
						//break;
					//}
					//case('s'):
					//{// string 
						//p_char = va_arg(vl, char *);	
						//sprintUSART3((uint8_t *)p_char);
						//arg_type = (PRINT_ARG_TYPE_STRING);
						//break;
					//}
					//case('f'):
					//{// float
						//uint64_t utmp64 = va_arg(vl, uint64_t);			// convert double to float representation IEEE 754
						//uint32_t tmp1 = utmp64&0x00000000FFFFFFFF;
						//tmp1 = tmp1>>29;
						//utmp32 = utmp64>>32;
						//utmp32 &= 0x07FFFFFF;
						//utmp32 = utmp32<<3;
						//utmp32 |= tmp1;
						//if(utmp64 & 0x8000000000000000)
							//utmp32 |= 0x80000000;
							
						//if(utmp64 & 0x4000000000000000)
							//utmp32 |= 0x40000000;
							
						//p_uint32 = &utmp32;
						
						//arg_type = (PRINT_ARG_TYPE_FLOAT);
						////arg_type = (PRINT_ARG_TYPE_HEXADECIMAL_WORD);
						////arg_type = (PRINT_ARG_TYPE_BINARY_WORD);
						//break;
					//}
					//case('x'):
					//{// hexadecimal 
						//if(str[k+2] == 'b')
						//{// byte
							//utmp32 = (uint32_t)va_arg(vl, int);
							//arg_type = (PRINT_ARG_TYPE_HEXADECIMAL_BYTE);
						//}
						//else if(str[k+2] == 'h')
						//{// half word
							//utmp32 = (uint32_t)va_arg(vl, int);
							//arg_type = (PRINT_ARG_TYPE_HEXADECIMAL_HALFWORD);
						//}
						//else if(str[k+2] == 'w')
						//{// word	
							//utmp32 = va_arg(vl, uint32_t);
							//arg_type = (PRINT_ARG_TYPE_HEXADECIMAL_WORD);
						//}
						//else
						//{
							//utmp32 = va_arg(vl, uint32_t);
							//arg_type = (PRINT_ARG_TYPE_HEXADECIMAL_WORD);
							//k--;
						//}
						
						//k++;
						//p_uint32 = &utmp32;
						//break;
					//}
					//default:
					//{
						//utmp32 = 0;
						//p_uint32 = &utmp32;
						//arg_type = (PRINT_ARG_TYPE_UNKNOWN);
						//break;
					//}
				//}
					
				//if(arg_type&(PRINT_ARG_TYPE_MASK_CHAR_STRING))	
				//{
					//getStr4NumMISC(arg_type, p_uint32, rstr);
					//sprintUSART3(rstr);	
				//}
				//k++;
			//}
		//}
		//else
		//{// not a '%' char -> print the char
			//putcharUSART3(str[k]);
			//if (str[k] == '\n')
				//putcharUSART3('\r');
		//}
		//k++;
	//}
	
	//va_end(vl);
	//return;
//}

void sprintUSART3(uint8_t * str)
{
	uint16_t k = 0;
	
	while (str[k] != '\0')
    {
        putcharUSART3(str[k]);
        if (str[k] == '\n')
            putcharUSART3('\r');
        k++;

        if (k == MAX_PRINT_STRING_SIZE)
            break;
    }
}

#ifdef USART_ECHO
void USART3_IRQHandler(void)
{
	uint8_t data;
	
	if(USART3->SR&(USART_SR_RXNE))
	{
		data = USART3->DR;
		//USART3->SR &= ~(USART_SR_RXNE);
		USART3->DR = data;
	}
}
#else



//void USART3_IRQHandler(void)
//{
	//uint8_t data;

	//if(USART3->SR&(USART_SR_RXNE))
	//{
		//g_usart3_buffer[g_usart3_widx] = USART3->DR;
		//g_usart3_widx++;
		//if(g_usart3_widx >= (USART3_BUFFER_SIZE))
		//{
			//g_usart3_widx = 0;
		//}
	//}
//}

#endif
void chkRxBuffUSART3(void)
{
	uint16_t t_usart3_ridx = g_usart3_ridx;

	t_usart3_ridx++;
	if(t_usart3_ridx >= (USART3_BUFFER_SIZE))
	{
		t_usart3_ridx = 0;
	}

	if(t_usart3_ridx != g_usart3_widx)
	{
		USART3->DR = g_usart3_buffer[t_usart3_ridx];
		g_usart3_ridx = t_usart3_ridx;
	}

}

uint8_t getcharUSART3(void)
{/// get one character from USART1
	uint8_t data;
	USART3->CR1 |= USART_CR1_UE | USART_CR1_RE;							// enable usart	and Rx
	while((USART3->SR & USART_SR_RXNE) != USART_SR_RXNE);				// wait until data ready
	
	data = USART3->DR;													// send data
	USART3->SR &= ~(USART_SR_RXNE);										// clear Rx data ready flag
	USART3->CR1 &= ~(USART_CR1_RE);
	return data;
}

	
