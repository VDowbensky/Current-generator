#include "uart_interface.h"

void initUART(uint32_t b);

void USART_SendBlock(uint8_t bl);
void DE_On(void);
void DE_Off(void);
void clearRXbuffer(void);

void cbUSART1_TXirq(void);
void cbUSART1_RXirq(void);

uint8_t TXbuffer[USART_TXBUFFERSIZE];
uint8_t RXbuffer[USART_RXBUFFERSIZE];  

uint8_t TxCount;
uint8_t TxPointer;
//uint8_t TxBusy = 0;
volatile uint8_t RxPointer;
//uint8_t RxFlag;

void initUART(uint32_t b)
{
  DE_Off();
  SYSCFG_REMAPDeInit();
  SYSCFG_REMAPPinConfig(REMAP_Pin_USART1TxRxPortA, ENABLE);
  USART_DeInit(USART1);
  USART_Init(USART1, b, USART_WordLength_8b, USART_StopBits_1, USART_Parity_No, (USART_Mode_TypeDef)(USART_Mode_Rx | USART_Mode_Tx));
  //interrupt
  //USART_ITConfig(USART1, (USART_IT_TC | USART_IT_RXNE), ENABLE);
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
  USART_ITConfig(USART1, USART_IT_TC, ENABLE);
  USART_Cmd(USART1, ENABLE);
  
}

void USART_SendBlock(uint8_t bl)
{
  //while (TxBusy);
  //USART_ITConfig(USART1, (USART_IT_TC), ENABLE);
  TxPointer = 0;
  TxCount = bl;
  DE_On(); //switch driver to transmit
  USART_SendData8(USART1, TXbuffer[0]);
  //TxBusy = 1;
}

void clearRXbuffer(void)
{
  //uint8_t i;
  //for(i=0; i<USART_RXBUFFERSIZE; i++) RXbuffer[i] = 0;
  disableInterrupts();
  RXbuffer[0] = 0;
  RxPointer = 0;
  enableInterrupts();
}

void cbUSART1_TXirq(void)
{
  //check interrupt source	
  
 
   if(USART_GetFlagStatus(USART1, USART_FLAG_TC) == SET)
	 {
          USART_ClearITPendingBit(USART1, USART_IT_TC);
	 if (TxPointer < TxCount)  	// it's end?
 		{
		TxPointer++;			// next byte
		USART_SendData8(USART1, TXbuffer[TxPointer]);
		}
	 else 
	 {
		TxCount=0;
		TxPointer=0;
		DE_Off();
                //USART_ITConfig(USART1, (USART_IT_TC), DISABLE);
		//TxBusy=0;//transmitter free
	 }
 }
}
void cbUSART1_RXirq(void)
{
  //add byte to buffer and set rx flsg
  if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)
  {
    uint8_t tmp;
    //USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    tmp = USART_ReceiveData8(USART1);
    RXbuffer[RxPointer] = tmp;
   // if (tmp == 0x0A)
   // {
   //   GPSflag = 1;
   // }
   // else
    {
    RxPointer++;
    if (RxPointer == USART_RXBUFFERSIZE) RxPointer = 0; // overrun ptotection - circle buffer
    }
  }
}

void DE_On(void)
{
    GPIO_WriteBit(DE_PORT, DE, SET);
}

void DE_Off(void)
{
    GPIO_WriteBit(DE_PORT, DE, RESET);  
}

