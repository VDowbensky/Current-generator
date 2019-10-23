#include "timers.h"

void initTIM16(void);
void delay_ms (uint16_t ms);
void check_keys(void);

volatile uint16_t TimingDelay;

void initTIM4(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	TIM_DeInit(TIM4);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //Clock enable
	
	TIM_TimeBaseStructure.TIM_Period = 1000;
	TIM_TimeBaseStructure.TIM_Prescaler = 7; //1 MHz
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM up counting mode
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 
	
  TIM_ClearFlag(TIM4,TIM_FLAG_Update);
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); //Enable TIM6 interrupt, allow update interrupt

	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);

	TIM_Cmd(TIM4, ENABLE);  
	
}


void TIM4_IRQHandler(void)   //TIM6 interrupt
{
static uint16_t pktimer = 0; 
	
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)  //Check if the TIM6 update interrupt occurs or not
    {
      TIM_ClearITPendingBit(TIM4, TIM_IT_Update);  //Clear TIMx update interrupt flag 
      TimingDelay--;
			RF69_RXtimeout++;
			check_keys();
			pktimer++;
			DebugVar1 = pktimer;
			if(pktimer >= (PkDelay*100))
			{
				pktimer = 0;
				PacketFlag = 1;
			}
			
    }
}


void check_keys(void)
{
		static int8_t K0cnt = 0;
  static int8_t K1cnt = 0;
  static uint8_t Tim4cnt = 0;
  static uint8_t k0, k1;
	
	if(GPIO_ReadInputDataBit(KEYPORT, K0) == RESET)
   {
     K0cnt++;
   }
   else
   {
     K0cnt--;
     if(K0cnt <= 0) K0cnt = 0;
   }
   
   if(GPIO_ReadInputDataBit(K1PORT, K1) == RESET)
   {
     K1cnt++;
   }
   else
   {
     K1cnt--;
     if(K1cnt <= 0) K1cnt = 0;
   }
   
   Tim4cnt++;
   if(Tim4cnt == KEYDELAY)
   {
     Tim4cnt = 0;
     if (K0cnt >= KEYDELAY/2) k0 = 1;
     else k0 = 0;
     if (K1cnt >= KEYDELAY/2) k1 = 1;
     else k1 = 0;
     Key = (k1 << 1) + k0;
   }
}


void delay_ms (uint16_t ms)
{
 
  TimingDelay = ms+1;
	while (TimingDelay > 0);
}



