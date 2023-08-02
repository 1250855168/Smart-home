#ifndef DHT11_H
#define DHT11_H

#include "stm32f10x.h"
 
#define DHT11_PIN GPIO_Pin_15
#define DHT11_PORT GPIOA
#define DHT11_RCC RCC_APB2Periph_GPIOA
 

 
 void TIM2_Init(void);
 void Delay_us(__IO uint32_t nCount);
 void DHT11_Start(void);
 uint8_t DHT11_Check(void);
 uint8_t DHT11_Read_Bit(void);
 uint8_t DHT11_Read_Byte(void);
 void DHT11_Read_Data1(uint8_t *temp, uint8_t *humi);

 #endif