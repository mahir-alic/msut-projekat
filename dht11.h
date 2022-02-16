#ifndef _DHT11_H
#define pin 7 // define dht11 data pin here

#include "stm32f4xx.h"
#include "delay.h"

struct dht11Data{
	uint8_t RH_integral,RH_decimal,T_integral,T_decimal;
};

void dht11Config();

struct dht11Data dht11Read();

#endif
