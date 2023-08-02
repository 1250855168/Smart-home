#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "stm32f10x.h"

/*
    利用固件库控制SysTick定时器实现的微秒级别的延时函数
*/
void udelay(int nms);

/*
    利用固件库控制SysTick定时器实现的毫秒级别的延时函数
*/
void mdelay(int nms);

#endif 
