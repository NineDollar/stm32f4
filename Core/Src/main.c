#include "stm32f4xx.h"
#include "led.h"
#include "delay.h"
#include "key.h"
#include "usart.h"

int main(void) {
  u16 a = 128;   //测试变量
  double b = 9.12; //测试变量

  LED_Init();     //LED初始化
  Delay_Init();   //延时函数初始化
  Usart_Config(); //串口初始化

  LED1_OFF;
  LED2_OFF;

  printf("STM32F429串口实验\n");
  printf("使用printf函数发送数据\n");

  while (1) {
    LED1_ON;
    Delay_ms(200);
    LED1_OFF;

    printf("十进制格式：  %d\n", a);
    printf("十六进制格式: %x\n", a);
    printf("小数格式：    %0.2f\n", b);
    Delay_ms(1000);
  }
}





