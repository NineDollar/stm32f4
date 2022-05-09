#include <stdio.h>
#include "main.h"
#include "stm32f4xx_it.h"
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void) {
  printf("NMI_Handler\r\n");
  while (1) {

  }
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void) {
  printf("HardFault_Handler\r\n");
  while (1) {
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void) {
  printf("MemManage_Handler\r\n");
  while (1) {
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void) {
  printf("BusFault_Handler\r\n");
  while (1) {
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void) {
  printf("UsageFault_Handler\r\n");
  while (1) {
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void) {
  printf("SVC_Handler\r\n");
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void) {
  printf("DebugMon_Handler\r\n");
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void) {
  printf("PendSV_Handler\r\n");
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void) {
}