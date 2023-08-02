#include "stm32f10x.h"
#include "SysTick.h"

int main()
{

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);



	while (1)
		{
		
		}

  
}
