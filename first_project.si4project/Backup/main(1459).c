#include "stm32f10x.h"
#include "SysTick.h"
#include"beep.h"
#include"exti.h"
#include"time.h"
#include"led.h"
#include"usart.h"
#include "delay.h"
#include"dht11.h"
#include<stdio.h>

extern  uint8_t dht11_temp, dht11_humi;


int main()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	Usart1_Init(115200);
	Init_LED();
	Init_Beep();
	Init_Time();
	
	
	while (1)
		{
			
				DHT11_Read_Data();

				sprintf(temp_humi,"Temp:%d,Humi:%d\n",dht11_temp,dht11_humi);

				Usart_SendString(USART1,temp_humi, 16);

			
				DelayXms(1000);

		}

  
}



void TIM2_IRQHandler(void){

if (TIM_GetFlagStatus(TIM2,TIM_FLAG_Update)==SET)
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_0);

		TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	}


}




