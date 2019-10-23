#include "uart.h"
#include "main.h"

void USART_init(uint32_t br);
void USART_SendBlock(uint8_t bl);
void clearRXbuffer(void);

void cbUSART1_RXirq(void);

uint8_t TxCount;
uint8_t TxPointer;
//uint8_t TxBusy = 0;
volatile uint8_t RxPointer;

uint8_t TXbuffer[UART_TXBUFFERSIZE];
uint8_t RXbuffer[UART_RXBUFFERSIZE];  

void USART_init(uint32_t br)
{
		GPIO_InitTypeDef gpio; 
		USART_InitTypeDef	usart;
		NVIC_InitTypeDef NVIC_InitStructure;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
//		GPIO_PinAFConfig(UARTPORT, TXD_PINSOURCE, GPIO_AF_USART1); //TXD
//		GPIO_PinAFConfig(UARTPORT, RXD_PINSOURCE, GPIO_AF_USART1); //RXD
	
		GPIO_StructInit(&gpio);	
		gpio.GPIO_Pin = TXD_PIN;
		gpio.GPIO_Speed = GPIO_Speed_10MHz;
		gpio.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_Init(UARTPORT, &gpio);
	
		GPIO_StructInit(&gpio);	
		gpio.GPIO_Pin = RXD_PIN;
		gpio.GPIO_Speed = GPIO_Speed_10MHz;
		//gpio.GPIO_Mode = GPIO_Mode_AF_PP;
		gpio.GPIO_Mode = GPIO_Mode_IPU; 
		GPIO_Init(UARTPORT, &gpio);	
	
		USART_DeInit(USART2);
		
		usart.USART_BaudRate = br;
		usart.USART_WordLength = USART_WordLength_8b;
		usart.USART_Mode = (USART_Mode_Rx | USART_Mode_Tx); 
		usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		usart.USART_StopBits = USART_StopBits_1; 
		usart.USART_Parity = USART_Parity_No;
				
		USART_Init(USART2, &usart);
		USART_Cmd(USART2, ENABLE);
				
		//interrupt
		NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn; 
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
		NVIC_Init(&NVIC_InitStructure);
		
		//USART_ITConfig(USART1, USART_IT_TC, ENABLE);
		//USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
		USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
		
		NVIC_EnableIRQ(USART2_IRQn);
			

}



void USART_SendBlock(uint8_t bl)
{

  TxPointer = 0;
  TxCount = bl;
  //DE_set(1); //switch driver to transmit
	USART_SendData(USART2, (uint16_t)TXbuffer[0]);
	USART_ITConfig(USART2, USART_IT_TC, ENABLE);
  //TxBusy = 1;
}

void clearRXbuffer(void)
{
  //uint8_t i;
  //for(i=0; i<USART_RXBUFFERSIZE; i++) RXbuffer[i] = 0;
//  disableInterrupts();
  RXbuffer[0] = 0;
  RxPointer = 0;
//  enableInterrupts();
}


void cbUSART1_RXirq(void)
{
  //add byte to buffer and set rx flsg
    uint8_t tmp;
    //USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    tmp = USART_ReceiveData(USART2);
    RXbuffer[RxPointer] = tmp;
    RxPointer++;
    if (RxPointer >= UART_RXBUFFERSIZE) RxPointer = 0; // overrun ptotection - circle buffer
}

void USART2_IRQHandler(void)   //USART1 interrupt
{
	//TX
	if(USART_GetFlagStatus(USART2, USART_FLAG_TC) == SET)
	//if(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == SET)
		{
		USART_ClearITPendingBit(USART2, USART_FLAG_TC);
		//USART_ClearITPendingBit(USART1, USART_FLAG_TXE);	
		if (TxPointer < TxCount)  	// it's end?
			{
			TxPointer++;			// next byte
			USART_SendData(USART2, (uint16_t)TXbuffer[TxPointer]);
			}
		else 
		{
			USART_ITConfig(USART2, USART_IT_TC, DISABLE);
			TxCount=0;
			TxPointer=0;
		}
	}

			if(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == SET)
			USART_ClearITPendingBit(USART2, USART_FLAG_RXNE);
			if (TestMode == 0) cbUSART1_RXirq();
			else cbUSART1_RXtestirq();

		
}
	




