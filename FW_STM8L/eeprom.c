#include "eeprom.h"
//#include "commands.h"
#include "dac.h"
#include "ecma0896.h"

BYTE eeprom  PARAMS[] = {0,0,0,0,0,0,01,0x20,0x92,0,0}; //place correct structure here!!!
BYTE EEbuffer[EEBUFFERSIZE];
code const BYTE PASSWORD[] ="eg20";

void ee_read(void);
void ee_pgm(void);
void readparameters(void);

//EEPROM routines
//unlock eeprom
void ee_read(void)
{
		BYTE j;
		for (j=0; j<EEBUFFERSIZE; j++) EEbuffer[j] = PARAMS[j];
				
}

void ee_pgm(void)
{		
		BYTE j;
		
		//unlock eeprom
		FLASH_DUKR = 0xAE;
		FLASH_DUKR = 0x56;
		//check DUL in FLASH_IAPSR here
		while (!(FLASH_IAPSR & 0x08));
		//erase eeprom parameters area
		for (j=0; j<EEBUFFERSIZE; j++) 
		{
			while (!(FLASH_IAPSR & 0x40)); //wait for HVOFF
			PARAMS[j] = 0;
		}
		//write parameters here
		for (j=0; j<EEBUFFERSIZE; j++) 
		{
			while (!(FLASH_IAPSR & 0x40)); //wait for HVOFF
			PARAMS[j] = EEbuffer[j];
		}		
		
		//lock eeprom - clear DUL
		FLASH_IAPSR &= ~0x08;
		
		
}

void readparameters(void)
{
//		Vtune = PARAMS[8];
//		Offset12 = PARAMS[9];
//		Gain = PARAMS[10];
//		if (Gain & 0x80) Lister = 1;
//		else Lister = 0;
}
