#ifndef _UART_INTERFACE_H_
#define _UART_INTERFACE_H_
#include <stdint.h>
#include "stm32f10x_usart.h"


#define UART_TXBUFFERSIZE 128
#define UART_RXBUFFERSIZE 128


extern void USART_init(uint32_t br);
extern void USART_SendBlock(uint8_t bl);
extern void clearRXbuffer(void);
extern void cbUART1_TXirq(void);
extern void cbUART1_RXirq(void);

extern uint8_t TXbuffer[];
extern uint8_t RXbuffer[];
extern volatile uint8_t RxPointer;

#endif

