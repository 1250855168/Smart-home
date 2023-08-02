#include"beep.h"
#include "stm32f10x.h"

void Init_Beep(){

		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef g1;
	g1.GPIO_Pin		= GPIO_Pin_1;
	g1.GPIO_Speed	= GPIO_Speed_50MHz;
	g1.GPIO_Mode 	= GPIO_Mode_Out_OD;

	
}