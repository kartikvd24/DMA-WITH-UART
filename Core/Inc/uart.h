/*
 * uart.h
 *
 *  Created on: Jul 29, 2025
 *      Author: desai
 */
#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include "stm32f4xx.h"

void UART2_RXTX_INIT(void);
void UART2_RXTX_Interrupt_INIT(void);
#define CR1_RXNE (1U<<5)
#define TCIF6 (1U<<21)
#define HIFCR_CTCIF6 (1U<<21)
void uart2_write(int ch);
int __io_putchar(int ch); // Needed only if you want to redirect printf output
void dma1_stream6_init(uint32_t src, uint32_t dst, uint32_t len);

#endif /* UART_H_ */
