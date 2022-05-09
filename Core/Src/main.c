#include "main.h"
#include <stdbool.h>
#include "stm32f4xx.h"
#include "led.h"
#include "delay.h"
#include "key.h"
#include "usart.h"
#include "time2.h"

int main(void) {
  led_init();     //LED初始化
  delay_init();   //延时函数初始化
  usart_config(); //串口初始化
  time2_init();

  led1_off
  led2_off

  while (true) {

  }
}





