#include "dac.h"
//#ifdef _LCD
//#include "ecma0896.h"
//#endif
#include "timers.h"

void initDAC(void);
void updateDAC (void);

WORD DACvalue;
//BYTE Offset12;
//BYTE Gain;
//BYTE Vtune;

void initDAC(void)
{
		//enable DAC clock
		//CLK_PCKENR1 |=0x80; //PCKEN17
		//enable comparator clock (FUCK!!! It's needed for RI registers access!!!)
		CLK_PCKENR2 |=0x20;
		//map DAC to PB6
		RI_ASCR1 |= 0b00010000;
		RI_IOSR1 |= 0b00010000;
		//RI_IOSR2 |= 0b00010000;
		//RI_IOSR3 |= 0b00010000;
		//CLK_PCKENR1 |=0x80; //PCKEN17
		//CLK_PCKENR2 |=0x20;
		DAC_CR1 = 0x03;//enable DAC, output buffer off
		DACvalue = 2048; //1.5 V at 3.00 V reference
		DAC_RDHR = 0;
		
				
		
}

void updateDAC (void)
{
		DAC_RDHR = DACvalue;
//		#ifdef _LCD
//		lcdprintstr ("            ",4);
//		lcdprintstr ("Level: ", 4);
		//tmp = DACvalue;
//		tmp1 = tmp/1000;
//		lcdprint (tmp1+0x30); //1000
//		tmp = tmp%1000;
//		tmp1 = tmp/100;
//		lcdprint (tmp1 + 0x30); //100
//		tmp = tmp%100;
//		tmp1 = tmp/10;
//		lcdprint (tmp1 + 0x30); //10
//		lcdprint (tmp%10 + 0x30);
//		#endif
}

