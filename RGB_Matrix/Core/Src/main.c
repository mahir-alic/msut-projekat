#include "stm32f1xx.h"
#include "main.h"

//PA12 SRCLK
//PB15 SER-data
//PA0- PA2 - row0
//PA3- PA5 - row1
//PA6- PA8 - row2
//PA9- PA11 - row3
//PB5,PB8,PB9 - row4
//PB12- PA14 - row5

//USART1 RX - PB7


#define BLUE 1
#define GREEN 2
#define RED 4
#define OFF 0

#define NIGHT 4
#define LEFT 1
#define RIGHT 2
#define BRAKE 3


void SystemClock_Config(void);


void delay(uint32_t);


void printMATRIX(uint8_t);
void rightBlink(void);
void leftBlink(void);
void brakeLight(void);
void bike(void);

uint8_t state=NIGHT;
uint8_t color=RED;
uint32_t t1,t2=0;



uint8_t right_blink[6][13]={
		{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x0,0x0,0x0},
		{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x1,0x0,0x0},
		{0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x0},
		{0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x0},
		{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x1,0x0,0x0},
		{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x0,0x0,0x0}
};

uint8_t matrix[6][13]={
		{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
		{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
		{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
		{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
		{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
		{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0}
};

uint8_t brake_light[6][13]={
		{0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x0},
		{0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x0},
		{0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x0},
		{0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x0},
		{0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x0},
		{0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x0}
};

uint8_t left_blink[6][13]={
		{0x0,0x0,0x1,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
		{0x0,0x1,0x1,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
		{0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x0},
		{0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x0},
		{0x0,0x1,0x1,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
		{0x0,0x0,0x1,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0}
};

uint8_t bike_sign[6][13]={
		{0x1,0x1,0x0,0x0,0x1,0x0,0x1,0x0,0x0,0x1,0x1,0x1,0x1},
		{0x1,0x0,0x1,0x0,0x1,0x0,0x1,0x0,0x1,0x1,0x0,0x0,0x0},
		{0x1,0x1,0x0,0x0,0x1,0x0,0x1,0x1,0x0,0x1,0x1,0x1,0x1},
		{0x1,0x1,0x0,0x0,0x1,0x0,0x1,0x1,0x0,0x1,0x0,0x0,0x0},
		{0x1,0x0,0x1,0x0,0x1,0x0,0x1,0x0,0x1,0x1,0x0,0x0,0x0},
		{0x1,0x1,0x1,0x0,0x1,0x0,0x1,0x0,0x1,0x1,0x1,0x1,0x1}
};

int main(void)
{

  SystemClock_Config();
  //------------------------------------------------------------------

	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	GPIOA->CRH = 0x00000000;
	GPIOA->CRH |= 0x33333333; //A8-A15
	GPIOA->CRL = 0x00000000;
	GPIOA->CRL |= 0x33333333; // A0-A7

	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

		GPIOB->CRH &= ~0xFFFF00FF;
		GPIOB->CRH |= 0x33330033;
		GPIOB->CRL &= ~0xFFF00000;
		GPIOB->CRL |= 0x4A300000; //PB7 floating input,  PB6 Alternate function push-pull

		RCC->APB2ENR |= RCC_APB2ENR_AFIOEN; //enable alternate function remaping
		AFIO->MAPR |= AFIO_MAPR_USART1_REMAP; //remap usart1 on PB6 and PB7

		RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
		USART1->CR1 |= USART_CR1_UE;
		USART1->BRR = 0x0000022B;
		USART1->CR1 |= (USART_CR1_TE) | (USART_CR1_RE) | (USART_CR1_TXEIE) | (USART_CR1_RXNEIE);


		//USART1->CR1 |= USART_CR1_UE;


		RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
			GPIOC->CRH &= ~0xFFF00000;
			GPIOC->CRH |= 0x33300000;

			GPIOA->ODR |= 0x6;


			uint32_t time=0;


			USART1->SR &= ~USART_SR_RXNE; //clear flag


		while(1)
		{
			time++;
			if(state==NIGHT){
				bike();
				color=GREEN;
				t1=1;
				t2=1;
				printMATRIX(color);
			}else if(state==LEFT){
				leftBlink();
				t1=100;
				t2=200;

				if(time<t1){
					GPIOC->ODR |= 0xF000;
					printMATRIX(RED);
					printMATRIX(RED);
					printMATRIX(RED);
					printMATRIX(RED);
					printMATRIX(RED);
					printMATRIX(GREEN);
				}

				if(time<t2){
					printMATRIX(OFF);
					printMATRIX(OFF);
				}else time=0;


			}else if(state==RIGHT){
				rightBlink();
				t1=100;
				t2=200;


							if(time<t1){
								printMATRIX(RED);
								printMATRIX(RED);
								printMATRIX(RED);
								printMATRIX(RED);
								printMATRIX(RED);
								printMATRIX(GREEN);
							}

							if(time<t2){

								printMATRIX(OFF);
								printMATRIX(OFF);
							}else time=0;

			}else if(state==BRAKE){
				brakeLight();
				printMATRIX(RED);
			}

			if((USART1->SR & USART_SR_RXNE)== USART_SR_RXNE){
				uint8_t x= USART1->DR;

				if(x=='R'){
					state=RIGHT;
				}else if(x=='L'){
					state=LEFT;
				}
				else if(x=='0'){
					state=OFF;
				}
				else if(x=='B'){
					state=BRAKE;
				}else if(x=='N'){
					state=NIGHT;
				}

				USART1->SR &= ~USART_SR_RXNE;
			}



		}
}



void delay(uint32_t d){
	volatile uint32_t t=0;
	while(t<(d*1))
	{
		t=t+1;
	}
}


void printMATRIX(uint8_t color){

	uint32_t buffer=0xFFFFFFFE;
	for(uint8_t r=0; r<6; r++){
		buffer=0xFFFFFFFE;
		for(uint8_t c=0; c<13; c++){


    		if((buffer&0x1)==0x1) GPIOB->ODR |= 0x1<<15; //set data on SER
    		else GPIOB->ODR &= ~(0x1<<15);

    		buffer=buffer>>1;
    		GPIOA->ODR |= (0x1<<12);//rise SRCLK

    		delay(1);
    		GPIOA->ODR=0x0;
    		GPIOB->ODR=0x0;
    		GPIOC->ODR=0x0;
    		GPIOA->ODR &= ~(0x1<<12);//fall SRCLK

    		//------------------------------------------------------------------

    				    			if(r==0){
    				    				GPIOA->ODR = matrix[r][c]*color;
    				    			}
    				    			else if(r==1){

    				    				GPIOA->ODR = (matrix[r][c]*color)<<3;
    				    			}
    				    			else if(r==2){
    				    				GPIOA->ODR =(matrix[r][c]*color)<<6;
    				    			}
    				    			else if(r==3){
    				    				GPIOA->ODR =(matrix[r][c]*color)<<9;
    				    			}
    				    			else if(r==4){
    				    				//GPIOC->ODR = (matrix[r][c]*color)<<13;
    				    				GPIOB->ODR = (((matrix[r][c]*color)&0x1)<<5)|(((matrix[r][c]*color)&0x6)<<7) ; //blue on PB5
    				    				 // !!!! LOW on PB7
    				    				//green PB8 red PB9
    				    			}
    				    			else if(r==5){
    				    				GPIOB->ODR = (matrix[r][c]*color)<<12;
    				    			}

    				    		//-----------------------------------------------------------------

   		delay(30);
   		//GPIOA->ODR &= ~(0x1<<12);


		}
		buffer=0xFFFFFFFE;
	}

}


void leftBlink(void){
	for(uint8_t r=0; r<6;r++){
		for(uint8_t c=0; c<=13; c++){
			matrix[r][c]=left_blink[r][c];
		}
	}
}

void rightBlink(void){
	for(uint8_t r=0; r<6;r++){
		for(uint8_t c=0; c<=13; c++){
			matrix[r][c]=right_blink[r][c];
		}
	}
}

void brakeLight(void){
	for(uint8_t r=0; r<6;r++){
		for(uint8_t c=0; c<=13; c++){
			matrix[r][c]=0x1;
		}
	}
}

void bike(void){
	for(uint8_t r=0; r<6;r++){
		for(uint8_t c=0; c<=13; c++){
			matrix[r][c]=bike_sign[r][c];
		}
	}
}



//-----CLOCK CONFIG------------------------------------------------------------------
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}


void Error_Handler(void)
{

}


