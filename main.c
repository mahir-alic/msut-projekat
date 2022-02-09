#include "stm32f4xx.h"
#include "lcd16x2.h"
#include "usart.h"
#include "delay.h"
#include "rot-enc.h"

#define SCROLL 0
#define ADJUST 1
#define CHANGED 1
#define NO_CHANGE 0

#define IRQ_IDLE			0
#define IRQ_DETECTED		1
#define IRQ_WAIT4LOW		2
#define IRQ_DEBOUNCE		3
#define IRQ_CNT

volatile uint32_t g_irq_cnt = 0;
volatile uint8_t g_gpiod_irq_state = (IRQ_IDLE);
volatile uint32_t g_irq_timer = 0;
uint8_t reMode=ADJUST;


int main(void){
	
	//######## LCD simulation #####################
		
	initLCD();
			
	//#############################################
	
	//######## ROTARY ENCODER #####################
	
	initRotEnc();
	
	//#############################################
	
    //######### PBTN CONFIG  ######################
    
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    GPIOD->PUPDR |= GPIO_PUPDR_PUPDR1_0;
    
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;								// enable clock on SYSCFG register
	SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI1_PD;						// select PC 8 as interrupt source p259
	EXTI->IMR = EXTI_IMR_MR1;											// enable interrupt on EXTI_Line8
	EXTI->EMR &= ~EXTI_EMR_MR1;											// disable event on EXTI_Line8
	EXTI->FTSR = EXTI_FTSR_TR1;	
	EXTI->RTSR = 0x00000000;	
	
	NVIC_EnableIRQ(EXTI1_IRQn);
	
	
	uint32_t led_timer;
	initSYSTIMER();
	
    
    //#############################################
	
	uint8_t state=0;
	uint8_t chg=0;
	uint8_t speed=17;
	uint8_t distance=12000;
	uint8_t temperature=30;
	
	while(1){
	    
			if(reMode==SCROLL){int tmp=state;
			state+=getRotEnc();
			if(state>=5) state=4;
			else if(state<=0) state=1;
			if(state!=tmp){
				chg=CHANGED;
			}
			}
	    
		
		//nazivi parametara
		
		if(chg==CHANGED){
			if(state==1){
				posCursor(2,1);
				eraseNChar(16);
				posCursor(2,1);
				printLCD("RADIUS:");
			}else if(state==2){
				posCursor(2,1);
				eraseNChar(16);
				posCursor(2,1);
				printLCD("SPEED:");
				posCursor(2,12);
				printLCD("kph");
			}else if(state==3){
				posCursor(2,1);
				eraseNChar(16);
				posCursor(2,1);
				printLCD("DIST:");
			    posCursor(2,13);
				printLCD("m");
			}else if(state==4){
				posCursor(2,1);
				eraseNChar(16);
				posCursor(2,1);
				printLCD("TEMP");
				posCursor(2,11);
				printLCD("C");
			}
		
		    chg=NO_CHANGE;
		
	   }
	   
	   //vrijednosti parametara
	   
			if(state==1){
				posCursor(2,8);
				eraseNChar(8);
				posCursor(2,9);
				printLCD("0");
			}else if(state==2){
				posCursor(2,7);
				eraseNChar(5);
				posCursor(2,8);
				printLCD("%d",speed);
			}else if(state==3){
				posCursor(2,7);
				eraseNChar(5);
				posCursor(2,7);
				printLCD("%d", distance);
			}else if(state==4){
				posCursor(2,7);
				eraseNChar(3);
				posCursor(2,7);
				printLCD("%d", temperature);
			}
	
	   
	   serviceIRQD();
	   
	   
	   
		
		//int tmp = radius + 1* getRotEnc();
		//if(tmp!=radius){
		//	radius=tmp;
		//	posCursor(2,9);
		//	eraseNChar(7);
		//	posCursor(2,9);
		//	printLCD("%d mm",radius);
		//}
		
		
		
	}
}

void EXTI1_IRQHandler(void)
{// with 
	if((EXTI->PR & EXTI_PR_PR1) == EXTI_PR_PR1)							// EXTI_Line0 interrupt pending?
	{
		
		if(reMode==SCROLL) reMode=ADJUST;
			else if(reMode==ADJUST) reMode=SCROLL;
		EXTI->PR = EXTI_PR_PR1;											// clear EXTI_Line0 interrupt flag
	}
}

void serviceIRQD(void)
{
	switch(g_gpiod_irq_state)
	{
		case(IRQ_IDLE):
		{
			break;
		}
		case(IRQ_DETECTED):
		{	
			g_gpiod_irq_state = (IRQ_WAIT4LOW); 
			break;
		}
		case(IRQ_WAIT4LOW):
		{
			if((GPIOD->IDR & 0x0002) == 0x0002)
			{
				g_gpiod_irq_state = (IRQ_DEBOUNCE);
				g_irq_timer = getSYSTIMER(); 
			}
			break;
		}
		case(IRQ_DEBOUNCE):
		{
			if(chk4TimeoutSYSTIMER(g_irq_timer, 50000) == (SYSTIMER_TIMEOUT))
			{
				g_gpiod_irq_state = (IRQ_IDLE); 
			}
		}
		default:
		{
			break;
		}
	}
}
