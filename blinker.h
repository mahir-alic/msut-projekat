#include "stm32f4xx.h"

#define LEFT_BLINKING 1
#define LEFT_NOT_BLINKING 2
#define RIGHT_BLINKING 3
#define RIGHT_NOT_BLINKING 4


extern uint8_t l_state;
extern uint8_t r_state;


void initBlink(void);
void right_blinker(void);
void left_blinker(void);
void light_on(void);
void light_off(void);
void light_blink(void);
int right_status(void);
int right_status(void);
