#include "i2c.h"
#include "delay.h"

// Alternate function - AF4
//PB6 -> SCL
//PB7 -> SDA

void initI2C2(void){
	
	
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
		//I2C2 SCL-> PB10
		//I2C2 SDA-> PB11
		GPIOB->MODER &=~0x00F00000;
		GPIOB->MODER |= 0x00A00000; //PB10 and PB11 alternate function pins
		GPIOB->OTYPER |= GPIO_OTYPER_OT_10 | GPIO_OTYPER_OT_11; //open drain configuration
		GPIOB->AFR[1] &= ~(0x0000FF00); 
		GPIOB->AFR[1] |= 0x00004400;
		
		delay_ms(10);
		RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
		
		delay_ms(10);
	
		I2C2->CR2 |= 0x002A;
		I2C2->CCR |=0x00D2;
		I2C2->TRISE = 0x002B;
		I2C2->CR1 |= I2C_CR1_PE;
		I2C2->CR1 &= ~I2C_CR1_START;
	
}

void txI2C2(uint8_t addr,uint8_t byte){
	
	I2C2->CR1 |= I2C_CR1_PE;	
	I2C2->CR1 |= I2C_CR1_START; //generate START condition
	//master waits for a read of the SR1 register
	//followed by a write in the DR register with the Slave address
	while((I2C2->SR1 & I2C_SR1_SB) != I2C_SR1_SB);
	I2C2 ->DR = addr; //write address	
	while((I2C2->SR1 & I2C_SR1_ADDR)!= I2C_SR1_ADDR);
	uint32_t x= I2C2->SR2; //clear ADDR flag
	I2C2->DR = byte; 
	I2C2->CR1 |= I2C_CR1_STOP; //generate STOP condition
			
}


