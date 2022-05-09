#ifndef __USART_H
#define __USART_H

#include "stdio.h"
#include "stm32f4xx.h"
/*----------------------*/

#define    USART1_RX_MAX    1024    //串口最大接收长度

extern u8 USART1_RecData[USART1_RX_MAX];    // 定义串口接收数组
extern u8 USART1_RX_Flag;  // 接收状态标志位
extern u16 USART1_RX_Size;  // 接收的数据大小

/*----------------------USART配置宏 ------------------------*/

#define  USART1_BaudRate  115200

#define  USART1_TX_PIN          GPIO_Pin_9           // TX 引脚
#define  USART1_TX_PORT         GPIOA                // TX 引脚端口
#define  USART1_TX_CLK          RCC_AHB1Periph_GPIOA // TX 引脚时钟
#define  USART1_TX_PinSource    GPIO_PinSource9      // 引脚源

#define  USART1_RX_PIN          GPIO_Pin_10          // RX 引脚
#define  USART1_RX_PORT         GPIOA                // RX 引脚端口
#define  USART1_RX_CLK          RCC_AHB1Periph_GPIOA // RX 引脚时钟
#define  USART1_RX_PinSource    GPIO_PinSource10     // 引脚源

/*---------------------- 函数声明 ----------------------------*/

void usart_config(void);    // USART初始化函数
#endif //__USART_H

