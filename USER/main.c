#include "stm32f10x.h"
#include "SysTick.h"
#include"beep.h"
#include"led.h"
#include"usart.h"
#include"delay.h"
#include"dht11.h"
#include"esp8266.h"
#include"onenet.h"
#include<stdio.h>


int main()
{
	
	
	unsigned short timeCount = 0;	
	
	unsigned char *dataPtr = NULL;
	uint8_t temperature, humidity;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);

	Init_LED();
	Init_Beep();
	TIM2_Init();
	Usart2_Init(115200);
	
	Usart1_Init(115200);
	Delay_Init();
	
	ESP8266_Init();	
		
	while(OneNet_DevLink())			
	Delay_us(1000); 

	char buf[128];
	
	const char *topics[1]= {"home/sub"};
	
	OneNet_Subscribe(topics,1);
	
	while (1)
		{		
				DHT11_Start(); 
			
        if(DHT11_Check()) 
        {
            DHT11_Read_Data1(&temperature, &humidity);
						sprintf(buf,"{\"Temp\":%d,\"Humi\":%d}",temperature, humidity);
						UsartPrintf(USART1,buf);
        }
				
						
		if(++timeCount >= 500)	
		{
			UsartPrintf(USART_DEBUG, "OneNet_Publish\r\n");
			
			OneNet_Publish("home/pub", buf);
			
			timeCount = 0;
			ESP8266_Clear();
		}
		
		dataPtr = ESP8266_GetIPD(0);
		if(dataPtr != NULL)
			OneNet_RevPro(dataPtr);
		
				DelayXms(10);
								
        Delay_us(3000); 

		}

  
}






