
#include"time.h"
#include "SysTick.h"


void Init_Time()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_TimeBaseInitTypeDef T;
	
	T.TIM_ClockDivision = 0;
	T.TIM_CounterMode = TIM_CounterMode_Up;
	T.TIM_Period =  9999;   //指定自动重装载值寄存器的值(N值)-->决定了我们计数的次数
	T.TIM_Prescaler = 7199; //指定预分频值，是一个整数[0,65535]-->决定了计数器的计数频率
	T.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIM2, &T);

	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);

	NVIC_InitTypeDef N;

	N.NVIC_IRQChannel = TIM2_IRQn;
	N.NVIC_IRQChannelCmd = ENABLE;
	N.NVIC_IRQChannelPreemptionPriority = 2;
	N.NVIC_IRQChannelSubPriority = 2;

	NVIC_Init(&N);

	TIM_Cmd(TIM2,ENABLE);
	
	NVIC_SetPriority(TIM2_IRQn,3);
}


