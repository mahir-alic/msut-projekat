#ifndef __USART2_H_
#define __USART2_H_

#include <stdio.h>
#include <stdarg.h>
#include "stm32f4xx.h"
#include "misc.h"

/* #define USART_ECHO */


#define USART2_BUFFER_SIZE			512
#define USART3_BUFFER_SIZE			1000

#define USART2_BAUDRATE_921600		0x0000002D
#define USART2_BAUDRATE_460800		0x0000005B
#define USART2_BAUDRATE_115200		0x0000016C
#define USART2_BAUDRATE_9600		0x00001117

#define USART3_BAUDRATE_921600		0x0000002D
#define USART3_BAUDRATE_460800		0x0000005B
#define USART3_BAUDRATE_115200		0x0000016C
#define USART3_BAUDRATE_9600		0x00001117

void initUSART2(uint32_t baudrate);
void putcharUSART2(uint8_t data);
void printUSART2(char * str, ... );
void sprintUSART2(uint8_t * str);
uint8_t getcharUSART2(void);

void chkRxBuffUSART2(void);
uint8_t chk4Cmd(void);

void enIrqUSART2(void);

void initUSART3(uint32_t baudrate);
void putcharUSART3(uint8_t data);
void printUSART3(char * str, ... );
void sprintUSART3(uint8_t * str);
uint8_t getcharUSART3(void);

void chkRxBuffUSART3(void);



void putTxBuffUSART3(uint8_t);
#endif 
