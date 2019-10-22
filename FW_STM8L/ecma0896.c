#include "ecma0896.h"
#include "gpio.h"

void updateLCD(void);
void initLCD(void);
void cls (void);
void commandLCD (char comLCD);
void lcdprint(char symbol);
void lcdprintstr (char  LCDSTRING[], BYTE row);
void writebyte (char  ch);

hbit A0 = PA_ODR^6;
hbit CS = PA_ODR^5;
hbit SDATA = PA_ODR^4;
hbit SCLK = PD_ODR^4;
hbit RESETLCD = PD_ODR^5;

void updateLCD(void)
{
//first line - 1st ES4 data
//second line - 2nd ES4 data
//3rd line - summary data (in liters)
//if ES not found, write "Not present"
}

void initLCD(void)
{
	RESETLCD = 0;
	delay(200);//reset LCD
	RESETLCD = 1;
	commandLCD(0x68); //(0b01101000);//system setup
	commandLCD(0x20); //(0b00100000);//static control
	commandLCD(0x31); //(0b00110001);//cursor off, display on
	commandLCD(0x70); //(0b01110000);//volume register=0
	commandLCD(0x42); //(0b01000010);//power save register
	lcdprint(0x20);//dummy space print for init
	delay(20);
	commandLCD(0x57); //(0b01010111);//power control register
	commandLCD(0x72+CONTRAST); //(0b01110010+Contrast);//set contrast
	delay(50);
	cls();
}

void cls (void)
{
	BYTE j;
	for (j=1; j<5; j++)	lcdprintstr ("            ", j);
}//cls

void commandLCD (char comLCD)
{	
	A0 = 0;
	writebyte(comLCD);
}
void lcdprint(char symbol)
{
	A0 = 1;
	writebyte(symbol);
}
void lcdprintstr (char  LCDSTRING[], BYTE row)
{	BYTE cursor;
	BYTE c;
	switch (row)
	{
	case 1:
		commandLCD(0xB0);
		break;
	case 2:
		commandLCD(0xC0);
		break;
	case 3:
		commandLCD(0xD0);
		break;
	case 4:
		commandLCD(0xE0);
		break;
	default:
		commandLCD(0xB0);
		break;
	}//switch
		
	
	for (cursor=0; cursor<12; cursor++)
		{
		c=LCDSTRING[cursor];
		if (c==0) return;
		else
		lcdprint (c);
		}
}//lcdprintstr

void writebyte (char  ch)
{
	BYTE mask;
	CS = 0;
	SCLK = 0;
	
	for (mask=0x80; mask>0; mask>>=1)
		{
		if (ch & mask) SDATA=1;
		else SDATA = 0;
			SCLK = 1;
			_nop_();
			_nop_();
			SCLK = 0;
			_nop_();
			_nop_();
		}
	CS = 1;
}//writebyte
