#include "stm32f10x.h"
#include "dht11.h"

 
#define DHT11_PIN GPIO_PIN_15
#define DHT11_GPIO_PORT GPIOA
 
 uint8_t dht11_temp, dht11_humi;
 
 void DHT11_Read_Data(void) 
 {
	 GPIO_InitTypeDef GPIO_InitStructure;
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	 
	 GPIO_InitStructure.GPIO_Pin = DHT11_PIN;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_Init(DHT11_GPIO_PORT, &GPIO_InitStructure);  
	 
	 GPIO_ResetBits(DHT11_GPIO_PORT, DHT11_PIN); 
	 Delay(20);  
	 
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	 GPIO_Init(DHT11_GPIO_PORT, &GPIO_InitStructure);

 
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

