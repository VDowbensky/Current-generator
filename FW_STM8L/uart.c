#include "uart.h"
#include "uart_reg.h"
#include "commands.h"
#include "gpio.h"

BYTE temp;

void initUART(void);
void putstr (const char *Addr);
void putpack (BYTE c);
void clearRxBuff(void);
void rec_pref(void);
void checktuneprefix (void);
void rec_addr(void);
void rec_ident(void);
void rec_command(void);
void checktunetable(void);
void rec_param(void);
void nocommand(void);

BYTE data RxBuffer[RXBUFFERSIZE];
BYTE data TxBuffer[TXBUFFERSIZE];
BYTE Comm_Len;
BYTE RxStatus;
BYTE RxCount;
BYTE plen;
BYTE data TxCount;
BYTE data TxPointer;
BYTE data RxPointer;
bit TxBusy;

void initUART(void)
{	
	//DE = 0;
	SYSCFG_RMPCR1 &= 0b11011111;
	
	//set baud rate 115200 bps at FCPU=16 MHz
	USART1_BRR2 = 0x1; //0x0 ;
	USART1_BRR1 = 0x34;// 0x24;
	USART1_CR1 = 0;
	USART1_CR2 = 0b01101100;
	USART1_CR3 = 0b00000000;
	USART1_CR4 = 0;
	USART1_CR5 = 0;
	RxPointer = 0;
	TxPointer=0;
}

/*void switch_to485(void)
{
	//remap USART to PC5, PC6
	DE = 0;
	SYSCFG_RMPCR1 |= 0b00100000;
	
	//set baud rate 19200 bps at FCPU=16 MHz
	USART1_BRR2 = 0x1;//0xB;
	USART1_BRR1 = 0x34;//0x8;
	//USART1_CR1 = 0;
	//USART1_CR2 = 0b01101100;
	//USART1_CR3 = 0b00000000;
	//USART1_CR4 = 0;
	//USART1_CR5 = 0;
	clearRxBuff();
	TxPointer=0;	
}

void switch_to232(void)
{
	SYSCFG_RMPCR1 &= 0b11011111;
	USART1_BRR2 = 0xB;
	USART1_BRR1 = 0x8;
	clearRx2Buff();
	Tx2Pointer=0;
}
*/
void putstr (const char *Addr)
{
	BYTE i=0;
	while (*Addr !=0)
		{
		TxBuffer[i]=*Addr;
		i++;
		Addr++;
		}
					
	//i++;
	TxBuffer[i]=0x0D;
	i++;
	TxBuffer[i]=0x0A;
	putpack(i);
}


void putpack (BYTE c)
{	while (TxBusy);
	TxPointer = 0;
	TxCount = c;
//	DE = 1; //switch driver to transmit
	USART1_DR = TxBuffer[0];
	TxBusy = 1;
}



//void clearRxBuff(void)

//{
//	RxPointer=0;
//	RxBuffer[0]=0;
//	F_Comm=0;
//	RxStatus = 0;
//}

//USART interrupts
void USART1_TX_Interrupt() interrupt 27		

	{
	 if (TC)
	 {TC=0;
	 if (TxPointer < TxCount)  	// it's end?
 		{
		TxPointer++;			// next byte
		USART1_DR = TxBuffer[TxPointer];	// put next byte from buffer
		}
	 else 
	 {
		TxCount=0;
		TxPointer=0;
//		DE = 0;
		TxBusy=0;//transmitter free
	 }
 }

	}
void USART1_RX_Interrupt() interrupt 28	
{
	
		if (RXNE)
		{
		RXNE=0;
		RxBuffer[RxPointer] = USART1_DR;
		RxPointer++;
		if (RxPointer == RXBUFFERSIZE) RxPointer = 0;
		}
}
			
		


