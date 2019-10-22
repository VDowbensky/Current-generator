#include "gpio.h"

void initIO(void);

void initIO(void)
{	//PA0, PA1 - inputs input w/pullup - SWIM
	//PA2, PA3 - ??? - oscillator
	//PA4...PA6 - push-pull
	PA_DDR = 0b01110000;
	PA_CR1 = 0b11110011;
	PA_CR2 = 0b00000000;
	//PA_ODR = 0;
		//configure PB6 as input without pullup
		PB_DDR = 0b10010000; //PB1 - PWM output
		PB_CR1 = 0b10010101;
		PB_CR2 = 0b10010000; //PB1 - 10 MHz
	//CCR|=0b00101000;
	
	//PB_ODR = 0;
	//PC0, PC1 - open dtain for I2C
	//PC2 - input w/pullup - RxD
	//PC3 - push-pull - TxD
	//PC4 - push-pull - maybe DE
	//PC5 - push-pull - maybe TxD1
	//PC6 - input w/pullup w/interrupt - maybe RxD1
	PC_DDR = 0b01111000;
	PC_CR1 = 0b11111111;
	PC_CR2 = 0b01111000;
	//PC_ODR = 0;
	//PD0...PD3 - inputs w/pullup
	//PD4///PD7 - push-pull
	PD_DDR = 0b11110000;
	PD_CR1 = 0b11111111;
	PD_CR2 = 0b00000000;
	//PD_ODR = 0;
}





