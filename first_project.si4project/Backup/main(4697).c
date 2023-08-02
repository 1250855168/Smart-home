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

extern unsigned int rec_data[4];

int main()
{
	Delay_Init();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	Usart1_Init(115200);
	Init_LED();
	Init_Beep();
	Init_Exti();
	Init_Time();
	
	
	char buf[128]={0};
	
	
	while (1)
		{
				DHT11_REC_Data();
			
				sprintf(buf,"T=%d.%d",rec_data[2],rec_data[3]);
			
				Usart_SendString(USART1,buf,10);
			
				sprintf(buf,"D=%d.%d",rec_data[0],rec_data[1]);
			
				Usart_SendString(USART1,buf,10);
			
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



void EXTI9_5_IRQHandler(void){

	if (EXTI_GetFlagStatus(EXTI_Line6)==SET)
		{
			
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);
		
		EXTI_ClearFlag(EXTI_Line6);
		
		}

}

