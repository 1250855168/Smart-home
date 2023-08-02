
#include"exti.h"
#include "stm32f10x.h"


void Init_Exti(void)
{

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef g;

	g.GPIO_Mode 		= GPIO_Mode_IPU;
	g.GPIO_Pin			= GPIO_Pin_6;
	g.GPIO_Speed		= GPIO_Speed_50MHz;

	GPIO_Init(GPIOA, &g);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource6);


	EXTI_InitTypeDef t;

	t.EXTI_Line 		= EXTI_Line6;
	t.EXTI_LineCmd		= ENABLE;
	t.EXTI_Mode 		= EXTI_Mode_Interrupt;
	t.EXTI_Trigger		= EXTI_Trigger_Rising;

	EXTI_Init(&t);

	NVIC_InitTypeDef n;
	n.NVIC_IRQChannel= EXTI9_5_IRQn;
	n.NVIC_IRQChannelCmd=ENABLE;
	n.NVIC_IRQChannelPreemptionPriority=1;
	n.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&n);
	

	
}





