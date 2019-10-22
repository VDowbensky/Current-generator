
/* MAIN.C file
 * 
 * Copyright (c) 2002-2005 STMicroelectronics
 */
#include <STM8\STM8L151K6.h>
#include <intrins.h>
//#include <string.h>
#include "global.h"
#include "timers.h"
#include "gpio.h"
#include "ecma0896.h"
#include "dac.h"
//#include "usart.h"
//#include "ATcommands.h"

void handleKBD (void);

void main (void)
{	
	CLK_CKDIVR = 0;
	initIO();
	
	CLK_PCKENR1 = 0b10100011;//switch clock to DAC, USART, timer 2 & timer 3
	CLK_PCKENR2 = 0;

//	readparameters();
//	initUART();
	initTIM2();
//	initPWM();
	#ifdef _LCD
	initLCD();
	#endif
	delay(50);
//	LED=1;
	_rim_ ();

	cls();
	lcdprintstr ("PWM CG v1.00", 1);
	lcdprintstr ("Press start!", 2);
	lcdprintstr ("C.meas: 0.00", 3);
	lcdprintstr ("V.meas: 0.00", 4);

	//for debug only
//	putstr ("Hello, Lamer! Let's fuck chinese pirates!");
//	initADC();
	initDAC();
	//LED=0;
	//main loop. Here are performed following procedures:
	//checking command from RS232;
	//checking keyboard code;
	//updating actual current value if needed;
	//reading ADC & convert it's data to actual outputs and cuttent voltage;
	//checking output current, setting overcurrent or undercurrent flag if needed;
	//updating DAC if needed;
	//updating LED's if needed;
	//updating LCD if needed;
	while (1)
		{
//				if (F_Comm) handlecommand();
				if (Key) handleKBD();
//				if (F_Curr) updateDAC();
//				if (F_ADC) readADC();
//				if (F_Under) undercurrentalarm();
//				if (F_Over) overcurrentalarm();
				
		}

}

void handleKBD (void)
{
		switch(Key)
		{
			case KEY_UP:
			break;
			
			case KEY_DOWN:
			break;
			
			case KEY_LEFT:
			break;
			
			case KEY_RIGHT:
			break;
			
			case KEY_ENTER:
			break;
			
			default:
			break;
			
		}
		Key = 0;
}






void delay(WORD msec)	
{
  WORD del = 0;
  while(msec)									// delay till msec is 0
  {
    for(del = 0; del < 1000; del++);		// 1 msec delay, m.b. corrected according to FCPU!
    msec--;										// decrement msec
  }
}
