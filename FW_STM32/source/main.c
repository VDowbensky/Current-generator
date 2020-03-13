#include "main.h"

_Bool UARTtxflag;

uint8_t c8[3] = {0,0,0};


int8_t packnum[5] = {0x30, 0x30, 0x30, 0x30, 0x30};


volatile uint8_t Key;


//debug variables
int32_t DebugVar0;
int32_t DebugVar1;
int32_t DebugVar2;
int32_t DebugVar3;


void user_loop(void);

void UART_senddata(void);
void convert(uint16_t v);
void convert8(uint8_t v);


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



 void UART_senddata(void)
 {
      //send packet to UART 


      //USART_SendBlock(RxLen+15); //set correct value
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
	initTIM7();
	Green_Off();
  Red_On();
  delay_ms(200);
	//delay_ms(10);
  //RF69_init();
  delay_ms(200);
  Red_Off();

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
			//if(!Periodic_Mode)
			//{
      //increment address on changing testing point
      //NodeAddr++;
      //if(NodeAddr > 254) NodeAddr = 0;
      //RF69_setNodeAddr(NodeAddr);
		  //switch_to_tx();
      //Periodic_Mode = 1;
			//PacketNumber = 1;
			//}
			//else{}
      break;
      
    case KEY_RIGHT:
      while (Key); //wait for release
      //switch_to_rx();
      //Periodic_Mode = 0;
      break;
      
    case KEY_BOTH:
      while (Key); //wait for release
      break;
      
    default:
      break; //nothing to do
      
    }
    

		
		if (UARTtxflag) UART_senddata();
		
  
  }
	
}
