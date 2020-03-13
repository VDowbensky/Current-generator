#ifndef _UART_INTERFACE_H_
#define _UART_INTERFACE_H_

#define BAUDRATE 115200UL
//#define BAUDRATE 9600UL

#define USART_TXBUFFERSIZE 128
#define USART_RXBUFFERSIZE 128

#include "stm8l15x.h"
#include "main.h"

extern void initUART(uint32_t b);
extern void USART_SendBlock(uint8_t bl);
extern void clearRXbuffer(void);
extern void cbUSART1_TXirq(void);
extern void cbUSART1_RXirq(void);

extern uint8_t TXbuffer[];
extern uint8_t RXbuffer[];
extern volatile uint8_t RxPointer;

#endif
