#include "stm32f4xx.h"
#include "led.h"
#include "delay.h"
#include "key.h"
#include "usart.h"

int main(void) {
  u16 a = 128;   //���Ա���
  double b = 9.12; //���Ա���

  LED_Init();     //LED��ʼ��
  Delay_Init();   //��ʱ������ʼ��
  Usart_Config(); //���ڳ�ʼ��

  LED1_OFF;
  LED2_OFF;

  printf("STM32F429����ʵ��\n");
  printf("ʹ��printf������������\n");

  while (1) {
    LED1_ON;
    Delay_ms(200);
    LED1_OFF;

    printf("ʮ���Ƹ�ʽ��  %d\n", a);
    printf("ʮ�����Ƹ�ʽ: %x\n", a);
    printf("С����ʽ��    %0.2f\n", b);
    Delay_ms(1000);
  }
}





