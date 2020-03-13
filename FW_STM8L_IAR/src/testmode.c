#include "testmode.h"

void test_loop(void);
void cbUSART1_RXtestirq(void);

void checkpacket (uint8_t packlen);
uint8_t compTxCRC (uint8_t c);
void comp_crc (uint8_t b);

void rec_headH(void);
void rec_headL(void);
void rec_command(void);
void rec_param(void);
void nocommand(void);

void clearRxBuff(void);




bool TestMode;
bool FreqTest;
uint8_t Command;
static uint8_t temp; //currently received byte
static uint8_t plen;
static uint8_t rxstatus;
static uint8_t rxcount;

uint8_t CRC;


  /* Test mode loop */
void test_loop(void)
{
  TestMode = TRUE; //for interrupt switching

  Red_On();
  while(1)
  {
    //Red_On();
    //RF69_setopmode (RF_OPMODE_TRANSMITTER);
    //delay_ms(5000);
    //RF69_setopmode (RF_OPMODE_STANDBY);
    //Red_Off();
    //RF69_calctemp();
    
    //delay_ms(500);
    
    if(rxstatus == 4) checkpacket (plen - 1);
    if(CommandFlag) 
    {
      handlecommand(Command);
      clearRxBuff();
    }

  }
}

void cbUSART1_RXtestirq(void)
{
  if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)
  {
    temp = USART_ReceiveData8(USART1);
    switch (rxstatus)
    {
    case 0://nothing received
    rec_headH();
    break;
			
    case 1://prefix received
    rec_headL();
    break;
			
    case 2://address received
    rec_command();
    break;
			
    case 3://command received
    rec_param();
    break;
			
    case 4://command not executed, nothing to do
    break;
			
    default:
    nocommand();
    break;
					
    } //switch
  } //if

}

////////////////////////////////////////////////////
//#define TXPREFIX 0xC96C //"handset" ;)
//#define RXPREFIX 0x236B //"base station" ;)

void rec_headH(void)
{
  if (temp == HI(RXPREFIX))
  {
    RXbuffer[RxPointer] = temp;
    RxPointer++;
    rxstatus = 1;
  }
  else nocommand();
}

void rec_headL(void)
{
  if (temp == LO (RXPREFIX))
  {
    RXbuffer[RxPointer] = temp;
    RxPointer++;
    rxstatus = 2;
  }
  else 
  {//check prefix
  if (temp == HI(RXPREFIX))
  {
    RxPointer = 0;
    RXbuffer[RxPointer] = temp;
    RxPointer++;
    rxstatus = 1;
   }
  else nocommand();
  }
	
}

void rec_command(void)
{
  uint8_t i = 0;
  while ((COMMANDLIST[i] != 0))
  {
    if (temp == COMMANDLIST[i])
    {
      plen = COMMANDLIST[i+1];
      rxcount = plen-3;
      RXbuffer[RxPointer] = temp;
      RxPointer++;
      rxstatus = 3;
      break;
    }
    else i += 2;
  } //while ((COMMANDLIST[i] != 0))
  
  if 	(rxstatus != 3) 
  {
  //plen = 0;
  rxcount = 0;
  clearRxBuff(); //command not found
  }
}

void rec_param(void)
{
  RXbuffer[RxPointer] = temp;
  RxPointer++;
  rxcount--;
  if (rxcount == 0) rxstatus = 4; 
}

void nocommand(void)
{
  CommandFlag = FALSE;
  rxcount = 0;
  clearRxBuff();
}

void clearRxBuff(void)

{
	RxPointer=0;
	RXbuffer[0]=0;
	CommandFlag=FALSE;
	rxstatus = 0;
}



void checkpacket (uint8_t packlen)
{
 	uint8_t i;
	CRC=0;
	for (i=0; i<packlen; i++)	
	{
	comp_crc (RXbuffer[i]);
	}
	if (CRC == RXbuffer[packlen]) 
	{
	CommandFlag = TRUE;
	Command = RXbuffer[2];
	}
	else clearRxBuff();
	
} 



uint8_t compTxCRC (uint8_t c)
{
  uint8_t i;
  CRC=0;
  for (i=0; i<c; i++) comp_crc(TXbuffer[i]);
  return CRC;
}//CompCRC


void comp_crc (uint8_t b)
{
  uint8_t j;
  for (j=8; j>0; j--)
    {
    if ( (b ^ CRC) & 0x01) CRC = ( (CRC ^ CRCPOLY) >> 1 ) | 0x80; 
    else CRC >>= 1;
    b >>= 1;
    }
}//comp_crc



