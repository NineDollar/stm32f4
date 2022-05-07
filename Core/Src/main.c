#include "stm32f4xx.h"
#include "led.h"
#include "delay.h"
#include "key.h"

int main(void) {
  u8 key_flag = 0;
  LED_Init();        //LED初始化
  Delay_Init();    //延时函数初始化
  KEY_Init();

  while (1) {
/*//    点亮LED1和LED2
    LED1_ON;
    LED2_ON;
    Delay_ms(200);

//    关闭LED1和LED2
    LED1_OFF;
    LED2_OFF;
    Delay_ms(200);*/

    if (KEY_Scan() == KEY_ON) {
      key_flag = ~key_flag;
    }
    if (key_flag == 0) {
      LED1_ON
      LED2_ON
    } else {
      LED1_OFF
      LED2_OFF
    }
  }
}





