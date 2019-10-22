#include "timers.h"
#include "dac.h"

void initTIM2(void);
void initTIM3(void);
void updateTIM3(void);

BYTE Key;

BYTE Tim2Counter;
//bit Tim2Flag;


void initTIM2(void)
{

			TIM2_PSCR = 8;//2 MHz
			TIM2_CNTRH = 0x9C;
			TIM2_CNTRL = 0x40;//50 Hz
			//TIM2_CNTRH = 0x0;
			//TIM2_CNTRL = 0x14;//100 kHz
			TIM2_ARRH = 0x9C;//0x0;
			TIM2_ARRL = 0x40;
			TIM2_IER = 0x01; //update interrupt enabled
			TIM2_CR1 = 0b10010001;//counter enable, countdown
		
}

void TIM2OVF_ISR() interrupt 19
{
		TIM2_SR1 &= 0xFE;
		Tim2Counter--;

}
void initTIM3(void)
{
	//set timer 3 to PWM mode using Vtune parameter
//			TIM3_CCMR1 = 0b01101100; //PWM mode 1
//			TIM3_PSCR = 0; //16 MHz
//			TIM3_CCMR1 = 0b01101100;
//			TIM3_CCER1 = 0x1; // enable ch1, normal polarity
			//TIM3_CCR1H = Vtune;
			//TIM3_CCR1L = 0;
//			TIM3_ARRH = 0;
//			TIM3_ARRL = 0xFF; //256 cycles
//			TIM3_CCR1H = 0;
//			TIM3_CCR1L = Vtune;
//			TIM3_BKR = 0b10000000;
//			TIM3_CR1 = 0b00000001;//counter enable, count-up
}

void updateTIM3(void)
{
			//TIM3_CCR1H = Vtune;
			//TIM3_CCR1L = 0;
//			TIM3_CCR1H = 0;
//			TIM3_CCR1L = Vtune;
}
