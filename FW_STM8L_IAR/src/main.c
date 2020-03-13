/**
  ******************************************************************************
  * @file    Project/STM8L15x_StdPeriph_Template/main.c
  * @author  MCD Application Team
  * @version V1.6.1
  * @date    30-September-2014
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm8l15x.h"
#include "main.h"
#include "user_settings.h"

/** @addtogroup STM8L15x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint16_t TimingDelay = 0;
volatile uint8_t Key;
uint8_t work_mode;


/* Private function prototypes -----------------------------------------------*/
void initCLK(void);

void initTIM4(void);
void delay_ms (uint16_t ms);
void initRTC(void);

void user_loop(void);


void TimingDelay_Decrement(void);

void convert(uint16_t v);
void convert8(uint8_t v);


uint8_t c8[3] = {0,0,0};

int8_t packnum[5] = {0x30, 0x30, 0x30, 0x30, 0x30};

//debug variables
int32_t DebugVar0;
int32_t DebugVar1;
int32_t DebugVar2;
int32_t DebugVar3;


/* Private functions ---------------------------------------------------------*/

void initCLK(void)
{
  CLK_DeInit();
  //CLK_HSEConfig(CLK_HSE_ON);
  //CLK_HSEConfig(CLK_HSI_ON);
  CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);
  //CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSE);
  //CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI);
  //CLK_SYSCLKSourceSwitchCmd(ENABLE);
  
  //enable peripheral clocks
  //CLK_PeripheralClockConfig(CLK_Peripheral_TIM1, ENABLE);
  //CLK_PeripheralClockConfig(CLK_Peripheral_TIM2, ENABLE);
  //CLK_PeripheralClockConfig(CLK_Peripheral_TIM3, ENABLE);
  CLK_PeripheralClockConfig(CLK_Peripheral_TIM4, ENABLE);
  CLK_PeripheralClockConfig(CLK_Peripheral_SPI1, ENABLE);
  CLK_PeripheralClockConfig(CLK_Peripheral_USART1, ENABLE);
  
  //CLK_LSEConfig(CLK_LSE_ON);
  CLK_LSICmd(ENABLE);
  //CLK_RTCClockConfig(CLK_RTCCLKSource_LSE, CLK_RTCCLKDiv_1);
  CLK_RTCClockConfig(CLK_RTCCLKSource_LSI, CLK_RTCCLKDiv_1);
  CLK_PeripheralClockConfig(CLK_Peripheral_RTC, ENABLE);
  
  
}



  

void initTIM4(void)
{
  TIM4_DeInit();
  TIM4_TimeBaseInit(TIM4_Prescaler_64, (F_CPU/64)/1000); //1 ms
  TIM4_ClearFlag(TIM4_FLAG_Update);
  TIM4_ITConfig(TIM4_IT_Update, ENABLE);
  TIM4_Cmd(ENABLE);
}

void delay_ms (uint16_t ms)
{
 
  TimingDelay = ms;
  while (TimingDelay != 0);

}

void TimingDelay_Decrement(void)
{
  TimingDelay--;
}
    

void initRTC(void)
{
  //RTC_DeInit(); //maybe removed
  RTC_WakeUpClockConfig(RTC_WakeUpClock_RTCCLK_Div16);
  RTC_ITConfig(RTC_IT_WUT, ENABLE);
  //set 1 s wkup period
 // RTC_SetWakeUpCounter(2375);
  RTC_SetWakeUpCounter(238); //~100 ms
//  RTC_SetWakeUpCounter(600);
  RTC_WakeUpCmd(ENABLE);
    
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


/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void main(void)
{
  //init clock - HSE 16 MHz
   initCLK();
  //IO config
  initIO();
  initSPI();
  initUART(BAUDRATE);
  initTIM4();
  initRTC();
  enableInterrupts();
  Green_On();
  Red_On();
  delay_ms(200);
  delay_ms(200);
  Red_Off();

  Green_Off();
  //check keypress
  delay_ms(100);
  //if(Key == KEY_LEFT) test_mode(); 
  if(GPIO_ReadInputDataBit(KEYPORT, K0) == RESET) test_loop(); 
  else user_loop();
}//main
  
  
  /* Work mode loop */
void user_loop(void)
{
  TestMode = FALSE; //for interrupt switching
  while (1)
  {
    
    switch (Key)
    {
    case KEY_LEFT:
      while (Key); //wait for release

      break;
      
    case KEY_RIGHT:
      while (Key); //wait for release

      break;
      
    case KEY_BOTH:
      while (Key); //wait for release
      break;
      
    default:
      break; //nothing to do
      
    }
    
        
    
    
   }//while(1)
}//work_mode()

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


  
  

  

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
