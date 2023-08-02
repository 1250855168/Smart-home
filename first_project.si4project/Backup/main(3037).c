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

char temp_humi[16];
uint8_t temp = 0;
uint8_t humi = 0;


int main()
{
	Delay_Init();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	Usart1_Init(115200);
	Init_LED();
	Init_Beep();
	Init_Time();
	DHT11_Init(); //初始化DHT11
	
	
	char buf[128]={0};
	
	
	while (1)
		{
			
				DHT11_Read_Data(&temp,&humi); //调用函数读取温度和湿度

				sprintf(temp_humi,"Temp:%d,Humi:%d\n",temp,humi);

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




