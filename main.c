#include "stm32f4xx.h"
//#include "lcd-sim.h"
#include "lcd16x2.h"
#include "usart.h"
#include "delay.h"
#include "rot-enc.h"
#include "i2c.h"
#include "speed.h"
#include "adc.h"

#define SCROLL 0
#define ADJUST 1
#define CHANGED 1
#define NO_CHANGE 0

#define IRQ_IDLE			0
#define IRQ_DETECTED		1
#define IRQ_WAIT4LOW		2
#define IRQ_DEBOUNCE		3
#define IRQ_CNT

#define LIGHT_REF 2048
#define OFF 0
#define BLINK_F 1  // fast blink
#define BLINK_S 2  // slow blink
#define ON 3

volatile uint32_t g_irq_cnt = 0;
volatile uint8_t g_gpioc_irq_state = (IRQ_IDLE);
volatile uint32_t g_irq_timer = 0;
uint8_t reMode=ADJUST;
uint8_t getNumLenght(int);
void printNumLCD(int line,int pos,int x);


int main(void){
	
	//######## LCD simulation #####################
		
	initI2C2();
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
	
	
	//######### SPEED SENSOR INIT #################
	initSPEED();
	//#############################################
	
	
	uint32_t led_timer;
	initSYSTIMER();

    
    //#############################################
    
    //########## HEADLIGHT CONFIG #################
    initADC1(); //light senzor
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;                                /** GPIOC Periph clock enable */
    GPIOC->MODER &= ~GPIO_MODER_MODER4; 								
	GPIOC->MODER |= GPIO_MODER_MODER4_0;  								/** Set output mode on pin 4 */
	GPIOC->OTYPER |= GPIO_OTYPER_OT_4;                                   //Open drain
	GPIOC->ODR |= 0x0010;
	//GPIOD->OSPEEDR &= ~GPIO_OSPEEDR_OSPEEDR; 								/** No pullup or pulldown */
    
   //#############################################
	
	uint8_t state=0;
	uint8_t chg=0;
	//uint8_t speed=17;
	//uint32_t distance=12000;
	int temperature=0;
	//uint16_t radius=0;
	uint32_t light=0;
	uint8_t adc_cnt=0;
	uint8_t light_state=OFF;
	clearLCD();
	
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
				printNumLCD(2,11,radius);
				posCursor(2,13);
				printLCD("mm");
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
				posCursor(2,7);
				eraseNChar(7);
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
				if(reMode==ADJUST){
					int tmp = radius + 10* getRotEnc();
					if(tmp<=0) tmp=0;
				    if(tmp>=999) tmp=999;
					if(tmp!=radius){
						radius=tmp;
						posCursor(2,9);
						eraseNChar(3);
						getNumLenght(radius);
						printNumLCD(2,11,radius);
						setNCirc(radius);
		            }
				}
			}else if(state==2){
				posCursor(2,7);
				eraseNChar(4);
				if(chk4TimeoutSYSTIMER(speedTimeOut,3000)==SYSTIMER_TIMEOUT) {
					speed=0;
					TIM4->CNT = 0;
					speedTimeOut=getSYSTIMER();
				}
				printNumLCD(2,10,speed);
			}else if(state==3){
				posCursor(2,7);
				eraseNChar(5);
				printNumLCD(2,11,(int)distance);
			}else if(state==4){
				posCursor(2,7);
				eraseNChar(3);
				posCursor(2,7);
				printLCD("%d", temperature);
			}
	
	 
	   
		serviceIRQD();
		
		//################ LIGHT ###################
		
		light+=getADC1();
		delay_ms(100);
		//delay_ms(1000);
		adc_cnt++;
		if(adc_cnt>=10){
			adc_cnt=0;
			light=light/10;
			
			if((light_state==OFF) && (light>=2048) && (light<3072)){
				light_state=BLINK_S;
				for(uint8_t i=0;i<2;++i){
					GPIOC->ODR &= ~0x0010;
					delay_ms(100);
					GPIOC->ODR |= 0x0010;
					delay_ms(100);
				}
				
			}if((light_state==BLINK_S) && (light>=3072) && (light<4096)){
				light_state=ON;
				GPIOC->ODR &= ~0x0010;
				delay_ms(100);
				GPIOC->ODR |= 0x0010;
				delay_ms(100);
			}if((light_state==ON) && (light>=2048) && (light<3072)){
				light_state=BLINK_S;
				for(uint8_t i=0;i<3;++i){
					GPIOC->ODR &= ~0x0010;
					delay_ms(100);
					GPIOC->ODR |= 0x0010;
					delay_ms(100);
				}
			}if((light_state==BLINK_S) && (light<=2048)){
				light_state=OFF;
				for(uint8_t i=0;i<2;++i){
					GPIOC->ODR &= ~0x0010;
					delay_ms(100);
					GPIOC->ODR |= 0x0010;
					delay_ms(100);
				}
			}if((light_state==OFF) && (light>=3072) && (light<4096)){
				light_state=ON;
				for(uint8_t i=0;i<3;++i){
					GPIOC->ODR &= ~0x0010;
					delay_ms(100);
					GPIOC->ODR |= 0x0010;
					delay_ms(100);
				}
			}if((light_state==ON) && (light<2048)){
				light_state=OFF;
				GPIOC->ODR &= ~0x0010;
				delay_ms(100);
				GPIOC->ODR |= 0x0010;
				delay_ms(100);
			}
			
			//---------------------------------------
			light=0;
		//###################################################
		}
	  
		
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
	switch(g_gpioc_irq_state)
	{
		case(IRQ_IDLE):
		{
			break;
		}
		case(IRQ_DETECTED):
		{	
			g_gpioc_irq_state = (IRQ_WAIT4LOW); 
			break;
		}
		case(IRQ_WAIT4LOW):
		{
			if((GPIOD->IDR & 0x0002) == 0x0002)
			{
				g_gpioc_irq_state = (IRQ_DEBOUNCE);
				g_irq_timer = getSYSTIMER(); 
			}
			break;
		}
		case(IRQ_DEBOUNCE):
		{
			if(chk4TimeoutSYSTIMER(g_irq_timer, 50000) == (SYSTIMER_TIMEOUT))
			{
				g_gpioc_irq_state = (IRQ_IDLE); 
			}
		}
		default:
		{
			break;
		}
	}
}

uint8_t getNumLenght(int x){
	if(x>=0 && x<=9) return 1;
	if(x>=10 && x<=99) return 2;
	if(x>=100 && x<=999) return 3;
	if(x>=1000 && x<=9999) return 4;
	if(x>=10000 && x<=99999) return 5;
}
void printNumLCD(int line,int pos,int x){
	posCursor(line,(pos+1-getNumLenght(x)));
	printLCD("%d",x);
}
