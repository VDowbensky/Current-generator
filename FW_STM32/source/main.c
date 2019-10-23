#include "main.h"




uint8_t work_mode;
_Bool PacketFlag;
_Bool Periodic_Mode;
_Bool UARTtxflag;
volatile uint8_t PacketDelay;
uint16_t PacketNumber = 1;
volatile uint8_t RF69_RXflag = 0;
//char TESTstring[] = "010101.000,0000.0000,X,00000.0000,Y"; 
char TESTstring[] = "WLS-WL.v12,0000,0000,X,00000,0000,Y"; 
uint8_t c8[3] = {0,0,0};
int8_t Rssi;
uint8_t Crcok;

uint8_t RxLen; //packet length
int8_t packnum[5] = {0x30, 0x30, 0x30, 0x30, 0x30};

volatile uint16_t RF69_RXtimeout = 0;
volatile uint8_t Key;
int8_t Temperature;

//debug variables
int32_t DebugVar0;
int32_t DebugVar1;
int32_t DebugVar2;
int32_t DebugVar3;


void user_loop(void);
void sendtestpacket(void);
void sendanswerpacket(void);
void switch_to_tx (void);
void switch_to_rx (void);
void UART_senddata(void);
void convert(uint16_t v);
void convert8(uint8_t v);

void switch_to_tx (void)
{
  //disable interrupt from DIO0
	DIO0_disableIRQ();
  RF69_setopmode (RF_OPMODE_STANDBY);
  RF69_writereg(REG_DIOMAPPING1, DIOM1_TX);
}

void switch_to_rx (void)
{
  //enable interrupt from DIO0
	DIO0_enableIRQ();
  RF69_setopmode (RF_OPMODE_RECEIVER);
  RF69_writereg(REG_DIOMAPPING1, DIOM1_RX);
  work_mode = WORK_MODE_RX;
  RF69_RXflag = 0;
  Red_Off();
}

//convert number to string
void convert(uint16_t v)
{
  uint16_t tmp;
  tmp = v;
  packnum[0] = v/10000 + 0x30;
  tmp = v%10000;
  packnum[1] = tmp/1000 + 0x30;
  tmp = tmp%1000;
  packnum[2] = tmp/100 + 0x30;
  tmp = tmp%100;
  packnum[3] = tmp/10 + 0x30;
  packnum[4] = tmp%10 + 0x30;
  
}

void convert8(uint8_t v)
{
  uint8_t tmp;
  tmp = v;
  c8[0] = tmp/100 + 0x30;
  tmp = tmp%100;
  c8[1] = tmp/10 + 0x30;
  c8[2] = tmp%10 + 0x30;
}


void sendtestpacket(void)
{
  uint8_t i;
  switch_to_tx();
  Red_On();
  work_mode = WORK_MODE_TX;
  //RF69_setopmode (RF_OPMODE_TRANSMITTER);
  //wait for TX ready - ???
  //2,3,4,5,6
  convert(PacketNumber);
  for(i = 0; i < 5; i++) RF69_TXbuffer[i+2] = packnum[i];
  RF69_TXbuffer[7] = ',';
  RF69_TXbuffer[8] = 'T';
  RF69_TXbuffer[9] = ',';
  //7 and up; add 3 bytes to WORK_PACKET_LEN
  for(i  = 0; i < PkLen-2; i++) RF69_TXbuffer[i+10] = TESTstring[i]; //ABCD.......
  delay_ms(1);
  RF69_sendpacket(PkLen, NodeAddr); //32 bytes, address 0xFF will be changed
  RF69_setopmode (RF_OPMODE_STANDBY); //maybe receiver
  PacketNumber++;
  if((PkCount != 0) && (PacketNumber > PkCount)) Periodic_Mode = 0;
  switch_to_rx();
  Red_Off();
}

void sendanswerpacket(void)
{
  uint8_t i;
  switch_to_tx();
  Red_On();
  delay_ms(10);
  work_mode = WORK_MODE_TX;
  //RF69_setopmode (RF_OPMODE_TRANSMITTER);
  //wait for TX ready - ???
  //2,3,4,5,6
//packet number  - copy from RX  
  for(i = 0; i < 5; i++) RF69_TXbuffer[i+2] = RF69_RXbuffer[i+2];
  RF69_TXbuffer[7] = ',';
  RF69_TXbuffer[8] = 'R'; //reply, response
  RF69_TXbuffer[9] = ',';
  //7 and up; add 3 bytes to WORK_PACKET_LEN
  for(i  = 0; i < PkLen-2; i++) RF69_TXbuffer[i+10] = TESTstring[i]; //ABCD.......
  //RSSI
  convert8(Rssi);
  RF69_TXbuffer[39] = '-';
  RF69_TXbuffer[40] = c8[0];
  RF69_TXbuffer[41] = c8[1];
  RF69_TXbuffer[42] = c8[2]; // neeed to put in packet
  delay_ms(1);
  RF69_sendpacket(PkLen, NodeAddr); //32 bytes, address 0xFF will be changed
  RF69_setopmode (RF_OPMODE_STANDBY); //maybe receiver
  //PacketNumber++;
  //if(PkCount != 0)
  //{
  //  if (PacketNumber > PkCount) Periodic_Mode = FALSE;
  //}
  switch_to_rx();
  Red_Off();  
}


 void UART_senddata(void)
 {
      //send packet to UART 
      //fill UART buffer
      uint8_t i;
      UARTtxflag = 0;
      Green_On();
      convert8(RF69_RXbuffer[0]); //lenght
      TXbuffer[0] = c8[0];
      TXbuffer[1] = c8[1];
      TXbuffer[2] = c8[2];
      TXbuffer[3] = ',';
      convert8(RF69_RXbuffer[1]); //address
      TXbuffer[4] = c8[0];
      TXbuffer[5] = c8[1];
      TXbuffer[6] = c8[2];
      TXbuffer[7] = ',';
      convert8(Rssi);
      TXbuffer[8] = '-';
      TXbuffer[9] = c8[0];
      TXbuffer[10] = c8[1];
      TXbuffer[11] = c8[2];
      TXbuffer[12] = ',';
      //for (i = 0; i < tmp+1; i++) TXbuffer[i+1] = RF69_RXbuffer[i];
      for (i = 0; i < RxLen-1; i++) TXbuffer[i+13] = RF69_RXbuffer[i+2];
      TXbuffer[i+13] = ',';
      i++;
      if(Crcok) TXbuffer[i+13] = 'G'; //good packet - CRC ok
      else TXbuffer[i+13] = 'B'; //bad packet - CRC not match
      i++;
      TXbuffer[i+13] = 0x0D;
      i++;
      TXbuffer[i+13] = 0x0A;
      USART_SendBlock(RxLen+15); //set correct value
      delay_ms(10);
      Green_Off();
      
      
 }  

int main (void)
{
	RCC_DeInit();
	//FLASH_SetLatency(FLASH_Latency_1);
	RCC_HSICmd(ENABLE);
	//check for HSI ready
	while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);
	//RCC_AdjustHSICalibrationValue(16);
	RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	RCC_PCLK1Config(RCC_HCLK_Div1);
	RCC_PCLK2Config(RCC_HCLK_Div1);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	
	EEPROM_init();
	EEPROM_readparameters();
	
	initIO();
	Green_On();
	USART_init(115200);
	initSPI();
	//timer 6  for key scanning
	initTIM4();
	Green_Off();
  Red_On();
  delay_ms(200);
	//delay_ms(10);
  RF69_init();
  delay_ms(200);
  Red_Off();
  RF69_setchannel(Channel);
  PacketDelay = PkDelay;
  work_mode = WORK_MODE_RX;
	if(GPIO_ReadInputDataBit(KEYPORT, K0) == RESET) test_loop(); 
	else user_loop();

}

  /* Infinite loop */

void user_loop(void)
{
	TestMode = 0;
while (1)
  {

    switch (Key)
    {
    case KEY_LEFT:
      while (Key); //wait for release
			if(!Periodic_Mode)
			{
      //increment address on changing testing point
      NodeAddr++;
      if(NodeAddr > 254) NodeAddr = 0;
      RF69_setNodeAddr(NodeAddr);
		  switch_to_tx();
      Periodic_Mode = 1;
			PacketNumber = 1;
			}
			else{}
      break;
      
    case KEY_RIGHT:
      while (Key); //wait for release
      switch_to_rx();
      Periodic_Mode = 0;
      break;
      
    case KEY_BOTH:
      while (Key); //wait for release
      break;
      
    default:
      break; //nothing to do
      
    }
    
    if (PacketFlag == 1)
    {
      PacketFlag = 0;
      if (Periodic_Mode) sendtestpacket();
    }
    
    //check and decode RX packets here!!!
		if(RF69_RXflag)
    {
      uint8_t i;
      Rssi = RF69_getRSSI();
      //Crcok
      if(RF69_readreg(REG_IRQFLAGS2) & CRC_OK) Crcok = 1;
      else Crcok = 0;
      //read data length
      //read data length
      RxLen = RF69_readreg(REG_FIFO);
      //fill buffer
      RF69_RXbuffer[0] = RxLen;
      for (i = 1; i < RxLen+1; i++) RF69_RXbuffer[i] = RF69_readreg(REG_FIFO);
      RF69_clearFIFO();
      RF69_RXflag = 0;
      RF69_restartRX();
      //set flag for UART
      UARTtxflag = 1;
      //send answer packet if received test packet and CRC is OK, else send to UART only
      if((RF69_RXbuffer[8] == 'T') && Crcok)  
      {
        sendanswerpacket();
      }
			
		}
		
    //RX timeout - restart RX (separate function in RF69 driver)
    if ((work_mode == WORK_MODE_RX) && (RF69_RXtimeout >= RF69To)) //reset after extended timeout defined by user
    //if ((work_mode == WORK_MODE_RX) && checkDIO1()) //reset RX immediately on RF69 timeout
    {
      RF69_restartRX();
    }		
		
		if (UARTtxflag) UART_senddata();
		
  
  }
	
}
