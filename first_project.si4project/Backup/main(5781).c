#include "stm32f10x.h"
#include "SysTick.h"
#include"beep.h"
#include"exti.h"
#include"time.h"
#include"led.h"

int main()
{

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);

	Init_LED();
	Init_Beep();
	Init_Exti();
	Init_Time();


	while (1)
		{
		
		}

  
}



void TIM2_IRQHandler(void){

if (TIM_GetFlagStatus(TIM2,TIM_FLAG_Update)==SET)
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);

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

