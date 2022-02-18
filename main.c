#include "stm32f4xx.h"
//#include "lcd-sim.h"
#include "lcd16x2.h"
#include "usart.h"
#include "delay.h"
#include "rot-enc.h"
#include "i2c.h"
#include "speed.h"
#include "adc.h"
#include "dht11.h"
#include "blinker.h"

#define SCROLL 0
#define ADJUST 1
#define CHANGED 1
#define NO_CHANGE 0

#define IRQ_IDLE			0
#define IRQ_DETECTED		1
#define IRQ_WAIT4HIGH		2
#define IRQ_DEBOUNCE		3
#define IRQ_CNT


#define OFF 0
//#define BLINK_F 1  // fast blink
#define BLINK 1  // slow blink
#define ON 2


#define LIGHT_MODE_OFF 0
#define LIGHT_MODE_ON 1
#define LIGHT_MODE_AUTO 2

#define LIGHT_HYST 100   //light sensor hysteresis
uint16_t light_ref_on=3000;  // ref value on 
uint16_t light_ref_blink=2000; //ref value blink
uint8_t brake=0;

uint8_t brake_state=OFF;
uint8_t brake_cng=NO_CHANGE;

volatile uint32_t g_irq_cnt = 0;
volatile uint8_t g_gpiod_irq_state = (IRQ_IDLE);
volatile uint32_t g_irq_timer = 0;

uint32_t debounce_r =0;
uint32_t debounce_l =0;
uint32_t debounce_b_r =0;
uint32_t debounce_b_l = 0;

uint8_t reMode=SCROLL;
uint8_t getNumLenght(int);
void printNumLCD(int line,int pos,int x);

uint8_t status_r=0;
uint8_t status_l=0;


int main(void){
	
	
	//######## LCD simulation #####################
		
	initI2C2();
	initLCD();
	
			
	//#############################################
	
	//######## USART3 Init ########################
	
	initUSART3(USART3_BAUDRATE_115200); //RX->PD9 TX->PD8
	
	//#############################################
	
	//######## ROTARY ENCODER #####################
	
	initRotEnc();
	
	//#############################################
	
	//######### PBTN CONFIG - ROT-ENC ######################            //PD1
    
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    GPIOD->PUPDR |= GPIO_PUPDR_PUPDR1_0;
    
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;								// enable clock on SYSCFG register
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI1_PD;						// select PD 1 as interrupt source p259
	EXTI->IMR |= EXTI_IMR_MR1;											// enable interrupt on EXTI_Line1
	EXTI->EMR &= ~EXTI_EMR_MR1;											// disable event on EXTI_Line1
	EXTI->FTSR |= EXTI_FTSR_TR1;	
	EXTI->RTSR &= ~EXTI_RTSR_TR1;	
	
	NVIC_EnableIRQ(EXTI1_IRQn);
	
	//######################################################
	
	initBlink();
	//########### PBTN CONFIG - LEFT BLINK ################             //PD2
	
    GPIOD->PUPDR |= GPIO_PUPDR_PUPDR2_1;                                 //Pull-down
    
    //RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;								// enable clock on SYSCFG register
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI2_PD;						// select PD 2 as interrupt source p259
	EXTI->IMR |= EXTI_IMR_MR2;											// enable interrupt on EXTI_Line2
	EXTI->EMR &= ~EXTI_EMR_MR2;											// disable event on EXTI_Line2
	EXTI->RTSR |= EXTI_RTSR_TR2;	
	EXTI->FTSR &= ~EXTI_FTSR_TR2;	
	
	NVIC_EnableIRQ(EXTI2_IRQn);
	//######################################################
	
	//########### PBTN CONFIG - RIGHT BLINK ################             //PD0
	
    GPIOD->PUPDR |= GPIO_PUPDR_PUPDR0_1;                                 //Pull-down
    
    //RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;								// enable clock on SYSCFG register
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PD;						// select PD 0 as interrupt source p259
	EXTI->IMR |= EXTI_IMR_MR0;											// enable interrupt on EXTI_Line0
	EXTI->EMR &= ~EXTI_EMR_MR0;											// disable event on EXTI_Line0
	EXTI->RTSR |= EXTI_RTSR_TR0;	
	EXTI->FTSR &= ~EXTI_FTSR_TR0;	
	
	NVIC_EnableIRQ(EXTI0_IRQn);
	//######################################################
	
	//################## PBTN CONFIG - RIGHT BRAKE  ########             //PD3
	
	GPIOD->PUPDR |= GPIO_PUPDR_PUPDR3_1;                                 //Pull down
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI3_PD;
	EXTI->IMR |= EXTI_IMR_MR3;											// enable interrupt on EXTI_Line0
	EXTI->EMR &= ~EXTI_EMR_MR3;											// disable event on EXTI_Line0
	EXTI->RTSR |= EXTI_RTSR_TR3;	
	EXTI->FTSR |= EXTI_FTSR_TR3;
	
	NVIC_EnableIRQ(EXTI3_IRQn);
	//######################################################
	
	//################## PBTN CONFIG - LEFT BRAKE  ########             //PD4
	
	GPIOD->PUPDR |= GPIO_PUPDR_PUPDR4_1;                                 //Pull down
	SYSCFG->EXTICR[1] |= SYSCFG_EXTICR2_EXTI4_PD;
	EXTI->IMR |= EXTI_IMR_MR4;											// enable interrupt on EXTI_Line0
	EXTI->EMR &= ~EXTI_EMR_MR4;											// disable event on EXTI_Line0
	EXTI->RTSR |= EXTI_RTSR_TR4;	
	EXTI->FTSR |= EXTI_FTSR_TR4;
	
	NVIC_EnableIRQ(EXTI4_IRQn);
	//######################################################
	
	//######### SPEED SENSOR INIT #################
	initSPEED();
	//#############################################
	
	
	uint32_t led_timer;
	initSYSTIMER();

    
    //#############################################
    
    //########## HEADLIGHT CONFIG #################
    initADC1(); //light senzor
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;                                /** GPIOD Periph clock enable */
    GPIOC->MODER &= ~GPIO_MODER_MODER4; 								
	GPIOC->MODER |= GPIO_MODER_MODER4_0;  								/** Set output mode on pin 15 */
	GPIOC->OTYPER |= GPIO_OTYPER_OT_4;                                   //Open drain
	GPIOC->ODR |= 0x0010;
	//GPIOD->OSPEEDR &= ~GPIO_OSPEEDR_OSPEEDR; 								/** No pullup or pulldown */
    
   //#############################################
   
   //######### dht11 Temperature sensor init #####
   
   dht11Config();
   
   struct dht11Data temp=dht11Read();
   
   //#############################################
	

	
	
	uint8_t state=0;
	uint8_t chg=0;
	//uint8_t speed=17;
	//uint32_t distance=12000;
	int temperature=0;
	uint32_t temp_time=getSYSTIMER();
	//uint16_t radius=0;
	uint32_t light=0;
	uint8_t adc_cnt=0;
	uint8_t light_state=0;
	uint8_t light_mode=OFF;
	int max_speed=0;
	clearLCD();
	delay_ms(100);
	
	posCursor(1,5);
	printLCD("WELLCOME");
	delay_ms(3000);
	
	
	
	debounce_r = getSYSTIMER();
	debounce_l = getSYSTIMER();
	debounce_b_l = getSYSTIMER();
	debounce_b_r = getSYSTIMER();
	
	putcharUSART3('0');
	
	while(1){
		
		
		//################# PBTN RIGHT DEBOUNCE ########################
	
		if(chk4TimeoutSYSTIMER(debounce_r,300)==SYSTIMER_TIMEOUT){
				EXTI->IMR |= EXTI_IMR_MR0;
		}

		//##############################################################
		
		//################# PBTN LEFT DEBOUNCE ########################
	
		if(chk4TimeoutSYSTIMER(debounce_l,300)==SYSTIMER_TIMEOUT){
			EXTI->IMR |= EXTI_IMR_MR2;
		}

		//##############################################################
		
		
			if(brake_state==ON && brake_cng==CHANGED){
			putcharUSART3('B');
			brake_cng=NO_CHANGE;
		}else if (brake_state==OFF && brake_cng==CHANGED){
				putcharUSART3('0');
				delay_ms(10);
				if(l_state==LEFT_BLINKING)
					putcharUSART3('L');
				else if(r_state==RIGHT_BLINKING) putcharUSART3('R');
				brake_cng=NO_CHANGE;
		}	
		
		
		//################# BRAKE RIGHT DEBOUNCE ########################
	
		//if(chk4TimeoutSYSTIMER(debounce_b_r,50)==SYSTIMER_TIMEOUT){
			//if(((GPIOD->IDR & 0x0008)== 0x0000) || (GPIOD->IDR & 0x0008)==0x0000)
			//{
				//if(brake_state != ON){
					
					//brake_state = ON;
					//brake_cng=CHANGED;
				//}
			//} else if((GPIOD->IDR & 0x0008)== 0x0008){
				//if(brake_state != OFF){
				//brake_state = OFF;
				//brake_cng=CHANGED;
				//}
			//}
				
			//EXTI->IMR |= EXTI_IMR_MR3;
		//}

		//##############################################################
		
		//################# BRAKE LEFT DEBOUNCE ########################
	
		if(chk4TimeoutSYSTIMER(debounce_b_l,50)==SYSTIMER_TIMEOUT && chk4TimeoutSYSTIMER(debounce_b_r,50)==SYSTIMER_TIMEOUT ){
			if(((GPIOD->IDR & 0x0010)== 0x0000) || ((GPIOD->IDR & 0x0008)==0x0000))
			{
				if(brake_state != ON){
					
					brake_state = ON;
					brake_cng=CHANGED;
				}
			} else if(((GPIOD->IDR & 0x0010)== 0x0010) && ((GPIOD->IDR & 0x0008)==0x0008)){
				if(brake_state != OFF){
				brake_state = OFF;
				brake_cng=CHANGED;
				}
			}
			EXTI->IMR |= EXTI_IMR_MR3;
			EXTI->IMR |= EXTI_IMR_MR4;
		}
         
		//##############################################################		
		
	
			
			if(reMode==SCROLL){
				int tmp=state;
					state+=getRotEnc();
				if(state>=10) state=9;
				else if(state<=0) state=1;
				if(state!=tmp){
					chg=CHANGED;
			}
			}
	    
		
		//nazivi parametara
		
		if(chg==CHANGED){
			if(state==1){
				posCursor(1,1);
				eraseNChar(16);
				posCursor(2,1);
				eraseNChar(16);
				posCursor(1,6);
				printLCD("RADIUS");
				printNumLCD(2,4,radius/10);
				posCursor(2,2);
				printLCD("[");
				posCursor(2,5);
				printLCD("]");
				posCursor(2,6);
				printLCD("cm");
				printNumLCD(2,12,radius%10);
				posCursor(2,14);
				printLCD("mm");
				posCursor(2,9);
			}else if(state==2){
				posCursor(1,1);
				eraseNChar(16);
				posCursor(2,1);
				eraseNChar(16);
				posCursor(1,6);
				printLCD("RADIUS");
				printNumLCD(2,4,radius/10);
				posCursor(2,11);
				printLCD("[");
				posCursor(2,13);
				printLCD("]");
				posCursor(2,6);
				printLCD("cm");
				printNumLCD(2,12,radius%10);
				posCursor(2,14);
				printLCD("mm");
			
				
			}
			else if(state==3){
				posCursor(1,1);
				eraseNChar(16);
				posCursor(2,1);
				eraseNChar(16);
				posCursor(1,5);
				printLCD("MAX:");
				printNumLCD(1,12,max_speed);
				posCursor(2,1);
				printLCD("SPEED:");
				posCursor(2,12);
				printLCD("kph");
				
				
			}else if(state==4){
				posCursor(1,1);
				eraseNChar(16);
				posCursor(2,1);
				eraseNChar(16);
				posCursor(1,4);
				printLCD("D:");
				printNumLCD(1,11,distance);
				posCursor(1,13);
				printLCD("m");
				posCursor(2,1);
				printLCD("SPEED:");
				posCursor(2,12);
				printLCD("kph");
				
				
			}
			else if(state==5){
				posCursor(1,1);
				eraseNChar(16);
				posCursor(2,1);
				eraseNChar(16);
				posCursor(1,4);
				printLCD("TEMP:");
				if(temperature>0){
					posCursor(1,11-getNumLenght(temperature));
					printLCD("+");	
					printNumLCD(1,11,temperature);
				}
				else if(temperature<=0){
					printNumLCD(1,11,temperature);
				}
				
				posCursor(1,13);
				printLCD("C");
				posCursor(2,1);
				printLCD("SPEED:");
				posCursor(2,12);
				printLCD("kph");
			}else if(state==6){ //ovdje dodat
				posCursor(1,1);
				eraseNChar(16);
				posCursor(2,1);
				eraseNChar(16);
				posCursor(1,4);
				printLCD("LIGHT MODE");
				if(light_mode==LIGHT_MODE_OFF){
							//posCursor(2,1);
							//eraseNChar(16);
							posCursor(2,7);
							printLCD("OFF");
						}
						if(light_mode==LIGHT_MODE_ON){
							//posCursor(2,1);
							//eraseNChar(16);
							posCursor(2,8);
							printLCD("ON");
						}
						if(light_mode==LIGHT_MODE_AUTO){
							//posCursor(2,1);
							//eraseNChar(16);
							posCursor(2,7);
							printLCD("AUTO");
						}
				
				
			}else if(state==7){
				posCursor(1,1);
				eraseNChar(16);
				posCursor(2,1);
				eraseNChar(16);
				posCursor(1,1);
				printLCD("LIGHT SENS.REF.");
				posCursor(2,1);
				printLCD("BLINK:");
				printNumLCD(2,11,light_ref_blink);
			}else if(state==8){
				posCursor(1,1);
				eraseNChar(16);
				posCursor(2,1);
				eraseNChar(16);
				posCursor(1,1);
				printLCD("LIGHT SENS.REF.");
				posCursor(2,1);
				printLCD("ON:");
				printNumLCD(2,8,light_ref_on);
			}else if(state==9){
				posCursor(1,1);
				eraseNChar(16);
				posCursor(1,6);
				printLCD("RESET:");
				posCursor(2,1);
				eraseNChar(16);
				posCursor(2,1);
				printLCD("PUSH and ROTATE");		
			}
		
		    chg=NO_CHANGE;
		
	   }
	   
	   //vrijednosti parametara -------------------------------------------------
	   
			if(state==1){
				if(reMode==ADJUST){
					int tmp = radius + 10* getRotEnc();
					if(tmp<=0) tmp=0;
				    if(tmp>=999) tmp=999;
					if(tmp!=radius){
						radius=tmp;
						posCursor(2,3);
						eraseNChar(2);
						getNumLenght(radius);
						printNumLCD(2,4,radius/10);
						posCursor(2,12);
						eraseNChar(1);
						printNumLCD(2,12,radius%10);
						setNCirc(radius);
		            }
				}
			}	else if(state==2){
				if(reMode==ADJUST){
					int tmp = radius + 1* getRotEnc();
					if(tmp<=0) tmp=0;
				    if(tmp>=999) tmp=999;
					if(tmp!=radius){
						radius=tmp;
						posCursor(2,3);
						eraseNChar(2);
						getNumLenght(radius);
						printNumLCD(2,4,radius/10);
						posCursor(2,12);
						eraseNChar(1);
						printNumLCD(2,12,radius%10);
						setNCirc(radius);
		            }
				}
			}
			else if(state==3){
				posCursor(2,7);
				eraseNChar(4);
				if(chk4TimeoutSYSTIMER(speedTimeOut,3000)==SYSTIMER_TIMEOUT) {
					speed=0;
					TIM4->CNT = 0;
					speedTimeOut=getSYSTIMER();
				}
				printNumLCD(2,10,speed);
				if(max_speed<speed) max_speed=speed;
				printNumLCD(1,12,max_speed);
				int tmp=right_status();
				if(tmp!=status_r){
					status_r=tmp;
					if(tmp==1){
						posCursor(1,15);
						eraseNChar(2);
						posCursor(1,15);
						printLCD("->");
						posCursor(1,15);
						printLCD("  ");
						posCursor(1,15);
						printLCD("->");
					}else if(tmp==0){
					posCursor(1,15);
					printLCD("  ");
					}
				}
				tmp=left_status();
				if(tmp!=status_l){
					status_l=tmp;
					if(left_status()==1){
						posCursor(1,1);
						eraseNChar(2);
						posCursor(1,1);
						printLCD("<-");
						posCursor(1,1);
						printLCD("  ");
						posCursor(1,1);
						printLCD("<-");
					}else if(tmp==0){
						posCursor(1,1);
						printLCD("  ");
					}
			    }
				
			}else if(state==4){
				posCursor(1,7);
				eraseNChar(5);
				printNumLCD(1,11,(int)distance);
				posCursor(2,7);
				eraseNChar(4);
				if(chk4TimeoutSYSTIMER(speedTimeOut,3000)==SYSTIMER_TIMEOUT) {
					speed=0;
					TIM4->CNT = 0;
					speedTimeOut=getSYSTIMER();
				}
				printNumLCD(2,10,speed);
				if(max_speed<speed) max_speed=speed;
				
				int tmp=right_status();
				if(tmp!=status_r){
					status_r=tmp;
					if(tmp==1){
						posCursor(1,15);
						eraseNChar(2);
						posCursor(1,15);
						printLCD("->");
						posCursor(1,15);
						printLCD("  ");
						posCursor(1,15);
						printLCD("->");
					}else if(tmp==0){
					posCursor(1,15);
					printLCD("  ");
					}
				}
				tmp=left_status();
				if(tmp!=status_l){
					status_l=tmp;
					if(left_status()==1){
						posCursor(1,1);
						eraseNChar(2);
						posCursor(1,1);
						printLCD("<-");
						posCursor(1,1);
						printLCD("  ");
						posCursor(1,1);
						printLCD("<-");
					}else if(tmp==0){
						posCursor(1,1);
						printLCD("  ");
					}
			    }
				
			}else if(state==5){
				posCursor(1,9);
				eraseNChar(3);
				if(temperature>0){
					posCursor(1,11-getNumLenght(temperature));
					printLCD("+");	
					printNumLCD(1,11,temperature);
				}
				else if(temperature<=0){
					printNumLCD(1,11,temperature);
				}
				posCursor(2,7);
				eraseNChar(4);
				if(chk4TimeoutSYSTIMER(speedTimeOut,3000)==SYSTIMER_TIMEOUT) {
					speed=0;
					TIM4->CNT = 0;
					speedTimeOut=getSYSTIMER();
				}
				printNumLCD(2,10,speed);
				if(max_speed<speed) max_speed=speed;
				
				int tmp=right_status();
				if(tmp!=status_r){
					status_r=tmp;
					if(tmp==1){
						posCursor(1,15);
						eraseNChar(2);
						posCursor(1,15);
						printLCD("->");
						posCursor(1,15);
						printLCD("  ");
						posCursor(1,15);
						printLCD("->");
					}else if(tmp==0){
					posCursor(1,15);
					printLCD("  ");
					}
				}
				tmp=left_status();
				if(tmp!=status_l){
					status_l=tmp;
					if(left_status()==1){
						posCursor(1,1);
						eraseNChar(2);
						posCursor(1,1);
						printLCD("<-");
						posCursor(1,1);
						printLCD("  ");
						posCursor(1,1);
						printLCD("<-");
					}else if(tmp==0){
						posCursor(1,1);
						printLCD("  ");
					}
			    }
			}else if(state==6){
				if(reMode==ADJUST){
					int tmp =light_mode + getRotEnc();
					if(tmp<=0) tmp=0;
				    if(tmp>=2) tmp=2;
					if(tmp!=light_mode){
						light_mode=tmp;
						if(light_mode==LIGHT_MODE_OFF){
							posCursor(2,1);
							eraseNChar(16);
							posCursor(2,7);
							printLCD("OFF");
						}
						if(light_mode==LIGHT_MODE_ON){
							posCursor(2,1);
							eraseNChar(16);
							posCursor(2,8);
							printLCD("ON");
						}
						if(light_mode==LIGHT_MODE_AUTO){
							posCursor(2,1);
							eraseNChar(16);
							posCursor(2,7);
							printLCD("AUTO");
						}
					}
				}
				int tmp=right_status();
				if(tmp!=status_r){
					status_r=tmp;
					if(tmp==1){
						posCursor(1,15);
						eraseNChar(2);
						posCursor(1,15);
						printLCD("->");
						posCursor(1,15);
						printLCD("  ");
						posCursor(1,15);
						printLCD("->");
					}else if(tmp==0){
					posCursor(1,15);
					printLCD("  ");
					}
				}
				tmp=left_status();
				if(tmp!=status_l){
					status_l=tmp;
					if(left_status()==1){
						posCursor(1,1);
						eraseNChar(2);
						posCursor(1,1);
						printLCD("<-");
						posCursor(1,1);
						printLCD("  ");
						posCursor(1,1);
						printLCD("<-");
					}else if(tmp==0){
						posCursor(1,1);
						printLCD("  ");
					}
			    }
			}else if(state==7){
				if(reMode==ADJUST){
					int tmp = light_ref_blink + 10* getRotEnc();
					if(tmp<=0) tmp=0;
				    if(tmp>=3500) tmp=3500;
					if(tmp!=light_ref_blink){
						light_ref_blink=tmp;
						posCursor(2,7);
						eraseNChar(5);
						printNumLCD(2,11,light_ref_blink);
						if((light_ref_on-light_ref_blink)<500)
						{
							light_ref_on=light_ref_blink+500;
						}
					}
			    }
		    }else if(state==8){
				if(reMode==ADJUST){
					int tmp = light_ref_on + 10* getRotEnc();
					if(tmp<=500) tmp=500;
				    if(tmp>=4096) tmp=4096;
					if(tmp!=light_ref_on){
						light_ref_on=tmp;
						posCursor(2,4);
						eraseNChar(5);
						printNumLCD(2,8,light_ref_on);
						if((light_ref_on-light_ref_blink)<500)
						{
							light_ref_blink=light_ref_on-500;
						}
					}
			    }
		    }else if(state==9){
				if(reMode==ADJUST){
					if(getRotEnc()!=0){
						speed=0;
						max_speed=0;
						distance=0;
						light_ref_on=3000;  
						light_ref_blink=2000; 
						state=3;
						reMode=SCROLL;
						
						
						posCursor(2,1);
						eraseNChar(16);
						posCursor(2,4);
						
						printLCD("RESET DONE!");
						delay_ms(2000);
						
						posCursor(1,1);
						eraseNChar(16);
						posCursor(2,1);
						eraseNChar(16);
						posCursor(1,5);
						printLCD("MAX:");
						printNumLCD(1,12,max_speed);
						posCursor(2,1);
						printLCD("SPEED:");
						posCursor(2,12);
						printLCD("kph");
					}
				}
			}
	
	
		if(chk4TimeoutSYSTIMER(temp_time,1000)==SYSTIMER_TIMEOUT){
			temp=dht11Read();
			temperature=temp.T_integral;
			temp_time=getSYSTIMER();
		}
	 
	   
		serviceIRQD();
		
		//######################## LIHGT ################################
		
	if(light_mode==LIGHT_MODE_AUTO){
		light+=getADC1();
		//delay_ms(1000);
		adc_cnt++;
		if(adc_cnt>=10){
			adc_cnt=0;
			light=light/10;
			if((light_state==OFF) && (light>=light_ref_blink+LIGHT_HYST) && (light<light_ref_on+LIGHT_HYST)){
				light_state=BLINK;
				light_blink();
			}if((light_state==BLINK) && (light>=light_ref_on+LIGHT_HYST) && (light<4096)){
				light_state=ON;
				light_on();
			}if((light_state==ON) && (light>=light_ref_blink-LIGHT_HYST) && (light<light_ref_on-LIGHT_HYST)){
				light_state=BLINK;
				light_blink();
			}if((light_state==BLINK) && (light<=light_ref_blink-LIGHT_HYST)){
				light_state=OFF;
				light_off();
			}if((light_state==OFF) && (light>=light_ref_on+LIGHT_HYST) && (light<4096)){
				light_state=ON;
				light_on();
			}if((light_state==ON) && (light<light_ref_blink-LIGHT_HYST)){
				light_state=OFF;
				light_off();
			}
			light=0;
		}
	}
	else if((light_mode==LIGHT_MODE_ON)){
		light_state=ON;
		light_on();
	}
	else if((light_mode==LIGHT_MODE_OFF)){
		light_state=OFF;
		light_off();
	}
	  
	  //###############################################################
		
	} //while end
}// main end

void EXTI1_IRQHandler(void)
{// with 
	if((EXTI->PR & EXTI_PR_PR1) == EXTI_PR_PR1)							// EXTI_Line1 interrupt pending?
	{
		
		if
		(reMode==SCROLL) reMode=ADJUST;
			else if(reMode==ADJUST) reMode=SCROLL;
		g_gpiod_irq_state=IRQ_DETECTED;
		EXTI->PR = EXTI_PR_PR1;											// clear EXTI_Line1 interrupt flag
	}
}

void EXTI0_IRQHandler(void)
{// with sudo 
	if((EXTI->PR & EXTI_PR_PR0) == EXTI_PR_PR0)							// EXTI_Line0 interrupt pending?
	{
		EXTI->IMR &= ~EXTI_IMR_MR0;
			right_blinker();
			brake_cng=CHANGED;
		debounce_r = getSYSTIMER();
		EXTI->PR |= EXTI_PR_PR0;											// clear EXTI_Line0 interrupt flag
	}
}

void EXTI2_IRQHandler(void)
{// with sudo 
	if((EXTI->PR & EXTI_PR_PR2) == EXTI_PR_PR2)							// EXTI_Line2 interrupt pending?
	{	
		EXTI->IMR &= ~EXTI_IMR_MR2;
			left_blinker();
			brake_cng=CHANGED;
		debounce_l = getSYSTIMER();
		EXTI->PR = EXTI_PR_PR2;											// clear EXTI_Line2 interrupt flag
	}
}

void EXTI3_IRQHandler(void)
{// with sudo 
	if((EXTI->PR & EXTI_PR_PR3) == EXTI_PR_PR3)							// EXTI_Line3 interrupt pending?
	{	
		EXTI->IMR &= ~EXTI_IMR_MR3;
		debounce_b_r = getSYSTIMER();
		EXTI->PR = EXTI_PR_PR3;											// clear EXTI_Line3 interrupt flag
	}
}
void EXTI4_IRQHandler(void)
{// with sudo 
	if((EXTI->PR & EXTI_PR_PR4) == EXTI_PR_PR4)							// EXTI_Line4 interrupt pending?
	{	
		EXTI->IMR &= ~EXTI_IMR_MR4;
		debounce_b_l = getSYSTIMER();
		EXTI->PR = EXTI_PR_PR4;											// clear EXTI_Line4 interrupt flag
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
			g_gpiod_irq_state = (IRQ_WAIT4HIGH); 
			break;
		}
		case(IRQ_WAIT4HIGH):
		{
			if(((GPIOD->IDR & 0x0002) == 0x0002))
			{
				g_gpiod_irq_state = (IRQ_DEBOUNCE);
				g_irq_timer = getSYSTIMER(); 
			}
			break;
		}
		case(IRQ_DEBOUNCE):
		{
			if(chk4TimeoutSYSTIMER(g_irq_timer, 500) == (SYSTIMER_TIMEOUT)) 
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

uint8_t getNumLenght(int y){
	int x=abs(y);
	if(x>=0 && x<=9) return 1;
	if(x>=10 && x<=99) return 2;
	if(x>=100 && x<=999) return 3;
	if(x>=1000 && x<=9999) return 4;
	if(x>=10000 && x<=99999) return 5;
}
void printNumLCD(int line,int pos,int x){
	if(x>=0){
		posCursor(line,(pos+1-getNumLenght(x)));
	}
	else if(x<0){
		posCursor(line,(pos-getNumLenght(x)));	
	}
	printLCD("%d",x);
}
	

