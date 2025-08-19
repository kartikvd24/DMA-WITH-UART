#include "stm32f4xx.h"
#include<stdint.h>
#include<stdio.h>
#include "uart.h"


#define GPIOAEN (1U<<0)
#define GPIOA_5 (1U<<5)
#define LED_PIN GPIOA_5
#define SR_RXNE (1U<<5)
static void uart_callback(void);
char key;
int main(){
	char message [32]="HEllo from Stm32 DMA interface\n\r";
	RCC->AHB1ENR|=GPIOAEN;

	GPIOA->MODER|=(1U<<10);
	GPIOA->MODER&=~(1U<<11);

	UART2_RXTX_INIT();
	dma1_stream6_init((uint32_t) message, (uint32_t) &USART2->DR, 32);

	while(1){



}
}

static void uart_callback(void)
{
GPIOA->ODR |=LED_PIN;

		}

void DMA1_Stream6_IRQHandler(void){
	//check for transfer complete
	if(DMA1->HISR & TCIF6)
	{
		DMA1->HIFCR|=HIFCR_CTCIF6;
		uart_callback();
	}
}



