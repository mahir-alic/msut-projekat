#include "flash.h"

void unlockFlash(void){
    FLASH->KEYR = 0x45670123;
    FLASH->KEYR = 0xCDEF89AB;
    FLASH->CR |= FLASH_CR_PSIZE_1;
}
void lockFlash(void){

    while(FLASH->SR & FLASH_SR_BSY);
    FLASH->CR &= ~FLASH_CR_PG;
    FLASH->CR |= FLASH_CR_LOCK;
}
void eraseFlash(void){
  while(FLASH->SR & FLASH_SR_BSY);
    //FLASH->CR |= FLASH_CR_SER | FLASH_CR_SNB_0 | FLASH_CR_SNB_1 | FLASH_CR_SNB_3 ; //sector 11 erase
    FLASH->CR |= FLASH_CR_SER | FLASH_CR_SNB_0 | FLASH_CR_SNB_1; //sector 3 erase
    FLASH->CR |= FLASH_CR_STRT; //trigger sector erase start
    while(FLASH->SR & FLASH_SR_BSY);
}

void write2Flash(uint32_t* p, uint32_t value){

    while(FLASH->SR & FLASH_SR_BSY);
    FLASH->CR |= FLASH_CR_PG;

    *p=value;

    while(FLASH->SR & FLASH_SR_BSY);
    
}

uint32_t readFlash(uint32_t* p){
    while(FLASH->SR & FLASH_SR_BSY);
    return *p;
    while(FLASH->SR & FLASH_SR_BSY);
}
