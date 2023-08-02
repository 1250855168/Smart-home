#include "stm32f10x.h"
#include "SysTick.h"
#include"beep.h"
#include"exti.h"

int main()
{

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);

	Init_Beep();
	Init_Exti();


	while (1)
		{
		
		}

  
}



void EXTI9_5_IRQHandler(void){

	if (EXTI_GetFlagStatus(EXTI_Line6)==SET)
		{
			
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);
		
		EXTI_ClearFlag(EXTI_Line6);
		
		}

}

