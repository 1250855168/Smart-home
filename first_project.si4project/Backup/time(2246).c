
#include"time.h"
#include "SysTick.h"


void Init_Time()
{

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //给时钟使能

	TIM_InternalClockConfig(TIM2);					//使用这个内部时钟

	TIM_TimeBaseInitTypeDef t;

	t.TIM_ClockDivision = TIM_CKD_DIV1;
	t.TIM_CounterMode	= TIM_CounterMode_Up;
	t.TIM_Period		= 10000 - 1;
	t.TIM_Prescaler 	= 7200 - 1;
	t.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIM2, &t);					//初始化时钟
	
	TIM_ClearFlag(TIM2,  TIM_FLAG_Update);//让它不立即进入中断
	
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);		//开启中断到nvic的通路


	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//初始化NVIC的优先级 整个工程只需要一次

	NVIC_InitTypeDef n;

	n.NVIC_IRQChannel	= EXTI2_IRQn;
	n.NVIC_IRQChannelCmd = ENABLE;
	n.NVIC_IRQChannelPreemptionPriority = 1;
	n.NVIC_IRQChannelSubPriority = 0;

	NVIC_Init(&n);//初始化NVIC

	TIM_Cmd(TIM2,ENABLE);
}

