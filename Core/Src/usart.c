/***
	************************************************************************************
	*	@file  	usart.c
	*	@version V1.0.0	
	*	@brief   usart 接口相关函数
   ************************************************************************************
   *  @description
	*
	*  1.初始化USART1的引脚 PA9/PA10，
	*  2.配置USART1工作在收发模式、数位8位、停止位1位、无校验、不使用硬件控制流控制，
	*    串口的波特率设置为115200，若需要更改波特率直接修改usart.h里的宏定义USART1_BaudRate。
	*  3.重定义fputc函数,用以支持使用printf函数打印数据
	*
	************************************************************************************
***/

#include "usart.h"

#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#define GETCHAR_PROTOTYPE int __io_getchar(int ch)

// 函数：usart IO口初始化
void USART_GPIO_Config(void) {

  // 立即输出,printf可以不加\n
  setvbuf(stdout, NULL, _IONBF, 0);

  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(USART1_TX_CLK | USART1_RX_CLK, ENABLE);    //IO口时钟配置

  //IO配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;     //复用模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;   //推挽
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;     //上拉
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

// 函数：USART 口初始化
//
void Usart_Config(void) {
  USART_InitTypeDef USART_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

  // IO口初始化
  USART_GPIO_Config();

  // 配置串口各项参数
  USART_InitStructure.USART_BaudRate = USART1_BaudRate; //波特率
  USART_InitStructure.USART_WordLength = USART_WordLength_8b; //数据位8位
  USART_InitStructure.USART_StopBits = USART_StopBits_1; //停止位1位
  USART_InitStructure.USART_Parity = USART_Parity_No; //无校验
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //发送和接收模式
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 不使用硬件流控制

  USART_Init(USART1, &USART_InitStructure); //初始化串口1
  USART_Cmd(USART1, ENABLE);    //使能串口1
}

PUTCHAR_PROTOTYPE {
  USART_SendData(USART1, (uint8_t) ch);
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {

  }
  return ch;
};

GETCHAR_PROTOTYPE {
  while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET) {

  }
  return (int) USART_ReceiveData(USART1);
};


