#include "stm32f10x.h"
#include "SysTick.h"

int main()
{

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef g;
	g.GPIO_Pin		= GPIO_Pin_0;
	g.GPIO_Speed	= GPIO_Speed_50MHz;
	g.GPIO_Mode 	= GPIO_Mode_Out_OD;
	
	GPIO_InitTypeDef g1;
	g.GPIO_Pin		= GPIO_Pin_1;
	g.GPIO_Speed	= GPIO_Speed_50MHz;
	g.GPIO_Mode 	= GPIO_Mode_Out_OD;

	
	GPIO_Init(GPIOB,&g);

	GPIO_Init(GPIOA,&g1);


	GPIO_WriteBit(GPIOB, GPIO_Pin_0,Bit_RESET);

	GPIO_WriteBit(GPIOA, GPIO_Pin_1,Bit_SET);


	while (1)
		{
		
		}

  
}
