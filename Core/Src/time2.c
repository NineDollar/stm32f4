//
// Created by NineDollar on 2022/5/10.
//

#include <stdio.h>
#include "time2.h"
#include "stm32f4xx.h"
#include "led.h"
void time2_init() {
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

  TIM_TimeBaseStructure.TIM_Period = 1000;
  TIM_TimeBaseStructure.TIM_Prescaler = 72;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  TIM_Cmd(TIM2, ENABLE);

  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

  //中断配置 初始化
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; //选择串口中断
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //抢占优先级
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //从优先级
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  //使能中断
  NVIC_Init(&NVIC_InitStructure);
}

/**
 *
 */
void TIM2_IRQHandler(void) {
  static u32 i = 0;
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET) {
    i++;
    if (i >= 1000) {
      led1_on
    }
    if (i >= 2000) {
      i = 0;
      led1_off
    }
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
  }
}