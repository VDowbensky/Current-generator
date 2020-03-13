#include "gpio_interface.h"

void initIO(void);

void Green_On (void);
void Green_Off (void);
void Red_On (void);
void Red_Off (void);



void initIO(void)
{
  //port A 
  //PA3 - TXD, PA4 - RXD
  GPIO_Init(UARTPORT, TXD_PIN, GPIO_Mode_Out_PP_High_Fast);
  GPIO_Init(UARTPORT, RXD_PIN, GPIO_Mode_In_PU_No_IT);
  //port B
  //PB0, PB1 - LED's, PB4 - NSS, PB5 - SCK, PB6 - MOSI, PB7 - MISO 
  GPIO_Init(LEDPORT, RED, GPIO_Mode_Out_OD_HiZ_Slow);
  GPIO_Init(LEDPORT, GREEN, GPIO_Mode_Out_OD_HiZ_Slow);
  GPIO_Init(SPIPORT, NSS_PIN, GPIO_Mode_Out_PP_High_Fast);
  GPIO_Init(SPIPORT, SCK_PIN, GPIO_Mode_Out_PP_Low_Fast);
  GPIO_Init(SPIPORT, MOSI_PIN, GPIO_Mode_Out_PP_Low_Fast);
  GPIO_Init(SPIPORT, MISO_PIN, GPIO_Mode_In_FL_No_IT);
  GPIO_WriteBit(SPIPORT, NSS_PIN, SET); 
  //port C
  //PC0 - IRQ, PC1 - RF reset, PC4 - PRG pin, PC5, PC6 - keys
  GPIO_Init(RFPORT, DIO0_PIN, GPIO_Mode_In_FL_No_IT);
  GPIO_Init(RFPORT, DIO1_PIN, GPIO_Mode_In_FL_No_IT);
  GPIO_Init(RFPORT, RESET_PIN, GPIO_Mode_In_FL_No_IT); 

  //GPIO_Init(KEYPORT, PRG_PIN, GPIO_Mode_In_PU_No_IT);

  GPIO_Init(KEYPORT, K0, GPIO_Mode_In_PU_No_IT);
  GPIO_Init(KEYPORT, K1, GPIO_Mode_In_PU_No_IT);
  //port D - not in use, no init
  
    //UART GPIO settings
  GPIO_Init(UARTPORT, TXD_PIN, GPIO_Mode_Out_PP_High_Fast);
  GPIO_Init(UARTPORT, RXD_PIN, GPIO_Mode_In_PU_No_IT);
  GPIO_Init(DE_PORT, DE, GPIO_Mode_Out_PP_High_Fast);  
  
  
  //external interrupt (DIO0/IRQ, DIO1)
  EXTI_DeInit();
  EXTI_SetPinSensitivity(DIO0_EXTI_PIN, EXTI_Trigger_Rising); 
  EXTI_SetPinSensitivity(DIO1_EXTI_PIN, EXTI_Trigger_Rising);
   
}



void Green_On (void)
{
  GPIO_WriteBit(LEDPORT, GREEN, RESET);
}
  
void Green_Off (void)
{
  GPIO_WriteBit(LEDPORT, GREEN, SET);
}
  
void Red_On (void)
{
  GPIO_WriteBit(LEDPORT, RED, RESET);
}
  
void Red_Off (void)
{
  GPIO_WriteBit(LEDPORT, RED, SET);
}
  
void RF69_select(void)
{
  GPIO_WriteBit(SPIPORT, NSS_PIN, RESET);  
}

void RF69_deselect(void)
{
  GPIO_WriteBit(SPIPORT, NSS_PIN, SET); 
}

void checkDIO0(void)
{
  while(GPIO_ReadInputDataBit(RFPORT, DIO0_PIN) == RESET);
}

uint8_t checkDIO1(void)
{
  if (GPIO_ReadInputDataBit(RFPORT, DIO1_PIN) == RESET) return 0;
  else return 1;
}

//hardware reset
void RF69_HWreset (void)
{
    //set reset port as output
    GPIO_Init(RFPORT, RESET_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_WriteBit(RFPORT, RESET_PIN, SET);
	//delay 5...10 ms
    delay_ms(10);
    GPIO_WriteBit(RFPORT, RESET_PIN, RESET);
    //set reset port as HI-Z input
    GPIO_Init(RFPORT, RESET_PIN, GPIO_Mode_In_FL_No_IT);
    delay_ms(10);
    
	
}
