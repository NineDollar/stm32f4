#include "main.h"
#include <stdbool.h>
#include "stm32f4xx.h"
#include "led.h"
#include "delay.h"
#include "key.h"
#include "usart.h"
#include "time2.h"

int main(void) {
  led_init();     //LED��ʼ��
  delay_init();   //��ʱ������ʼ��
  usart_config(); //���ڳ�ʼ��
  time2_init();

  led1_off
  led2_off

  while (true) {

  }
}





