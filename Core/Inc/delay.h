#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f4xx.h"

void delay_init(void);				//延时函数初始化
void delay_ms(u32 nTime);	//毫秒延时函数

#endif //__DELAY_H

