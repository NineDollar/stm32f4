/**
 *  1.初始化USART1的引脚 PA9/PA10，
 *  2.配置USART1工作在收发模式、数位8位、停止位1位、无校验、不使用硬件控制流控制，
 *    串口的波特率设置为115200，若需要更改波特率直接修改usart.h里的宏定义USART1_BaudRate。
*/

#include <stdbool.h>
#include "usart.h"

// printf重定义
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#define GETCHAR_PROTOTYPE int __io_getchar(void)

u8 USART1_RecData[USART1_RX_MAX];    // 定义串口接收数组
u8 USART1_RX_Flag = 0;     // 接收状态标志位
u16 USART1_RX_Size = 0;     // 接收的数据大小

// 函数：usart IO口初始化
//
void USART_GPIO_Config(void) {
  //立即输出，可以不加\r\n
  setvbuf(stdout, NULL, _IONBF, 0);

  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(USART1_TX_CLK | USART1_RX_CLK, ENABLE);    //IO口时钟配置

  //IO配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;     //复用模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;   //推挽
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;         //上拉
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; //速度等级

  //初始化 TX	引脚
  GPIO_InitStructure.GPIO_Pin = USART1_TX_PIN;
  GPIO_Init(USART1_TX_PORT, &GPIO_InitStructure);
  //初始化 RX 引脚
  GPIO_InitStructure.GPIO_Pin = USART1_RX_PIN;
  GPIO_Init(USART1_RX_PORT, &GPIO_InitStructure);

  //IO复用，复用到USART1
  GPIO_PinAFConfig(USART1_TX_PORT, USART1_TX_PinSource, GPIO_AF_USART1);
  GPIO_PinAFConfig(USART1_RX_PORT, USART1_RX_PinSource, GPIO_AF_USART1);
}

// 函数：串口中断优先级配置
//
void USART_NVIC_Config(void) {
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);    //设置中断分组2

  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; // 选择 USART1 通道
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; //抢占优先级设置为3
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; //响应优先级设置为1
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //开启中断
  NVIC_Init(&NVIC_InitStructure); //初始化配置
}

// 函数：USART 口初始化
void usart_config(void) {
  USART_InitTypeDef USART_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); //开启串口时钟

  USART_GPIO_Config();    // IO口初始化
  USART_NVIC_Config(); //	串口中断初始化

  USART_InitStructure.USART_BaudRate = USART1_BaudRate; //波特率
  USART_InitStructure.USART_WordLength = USART_WordLength_8b; //数据位8位
  USART_InitStructure.USART_StopBits = USART_StopBits_1; //停止位1位
  USART_InitStructure.USART_Parity = USART_Parity_No; //无校验
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //发送和接收模式
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 不使用硬件流控制

  USART_Init(USART1, &USART_InitStructure); //初始化串口1
  USART_Cmd(USART1, ENABLE);    //使能串口1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);    //使能串口中断接收

  printf("\r\n");
}

bool usart1_recv_bytr(u16 *rx_data) {
  while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET) {
    return 0;
  }
  *rx_data = USART_ReceiveData(USART1);
  return 1;
}

/**
 * USART1中断服务函数
 */
void USART1_IRQHandler() {
  u16 data;
  if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET) {
    if (usart1_recv_bytr(&data)) {
      USART_SendData(USART1, data);
      USART_ClearITPendingBit(USART1, USART_IT_TXE);
    }
  }
}

PUTCHAR_PROTOTYPE {
  USART_SendData(USART1, (uint8_t) ch);
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
  return ch;
};

GETCHAR_PROTOTYPE {
  while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
  return (int) USART_ReceiveData(USART1);
};


