#include"led.h"
#include "stm32f10x.h"


void Init_LED()
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitTypeDef g;
	g.GPIO_Pin		= GPIO_Pin_0;
	g.GPIO_Speed	= GPIO_Speed_50MHz;
	g.GPIO_Mode 	= GPIO_Mode_Out_PP;

	GPIO_Init(GPIOB,&g);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_0);

}