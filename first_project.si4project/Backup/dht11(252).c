#include "stm32f10x.h"
#include "dht11.h"

 
#define DHT11_PIN GPIO_PIN_15
#define DHT11_GPIO_PORT GPIOA
 
 uint8_t dht11_temp, dht11_humi;
 
 void DHT11_Read_Data(void) 
 {
	 GPIO_InitTypeDef GPIO_InitStruct;
	 GPIO_InitStruct.Pin = DHT11_PIN;
	 GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	 GPIO_InitStruct.Pull = GPIO_NOPULL;
	 GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	 HAL_GPIO_Init(DHT11_GPIO_PORT, &GPIO_InitStruct);	
 
	 HAL_GPIO_WritePin(DHT11_GPIO_PORT, DHT11_PIN, GPIO_PIN_RESET);
	 HDelay(20);  
 
	 GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	 GPIO_InitStruct.Pull = GPIO_PULLUP;
	 HAL_GPIO_Init(DHT11_GPIO_PORT, &GPIO_InitStruct);
 
	 if(HAL_GPIO_ReadPin(DHT11_GPIO_PORT, DHT11_PIN) == 0)	  
	 {
		 while(HAL_GPIO_ReadPin(DHT11_GPIO_PORT, DHT11_PIN) == 0); 
		 while(HAL_GPIO_ReadPin(DHT11_GPIO_PORT, DHT11_PIN) == 1);
	 }
	 dht11_humi = 0;
	 for(i = 0; i < 8; i++)  
	 {
		 while(HAL_GPIO_ReadPin(DHT11_GPIO_PORT, DHT11_PIN) == 0);
		 Delay_us(30);	
		 if(HAL_GPIO_ReadPin(DHT11_GPIO_PORT, DHT11_PIN) == 1)	 
			 dht11_humi = dht11_humi*2 + 1;
		 else  
			 dht11_humi = dht11_humi*2;
		 while(HAL_GPIO_ReadPin(DHT11_GPIO_PORT, DHT11_PIN) == 1);
	 }	
 
	 dht11_temp = 0; 
	 for(i = 0; i < 8; i++)  
	 {
		 while(HAL_GPIO_ReadPin(DHT11_GPIO_PORT, DHT11_PIN) == 0);
		 Delay_us(30);	
		 if(HAL_GPIO_ReadPin(DHT11_GPIO_PORT, DHT11_PIN) == 1)	 
			 dht11_temp = dht11_temp*2 + 1;
		 else  
			 dht11_temp = dht11_temp*2;
		 while(HAL_GPIO_ReadPin(DHT11_GPIO_PORT, DHT11_PIN) == 1);
	 }	
 }

