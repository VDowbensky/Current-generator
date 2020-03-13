#include "eeprom.h"

//#pragma data_alignment=4


  //int8_t Tcal;
  //int8_t TcalValue;
  //int16_t Tslope;




//EEPROM write routines

eeprom* params;

void EEPROM_init(void);
void EEPROM_readparameters(void);
void write_eeprom_word(uint32_t address, uint32_t data);
void write_eeprom_halfw(uint32_t address, uint16_t data);
void write_eeprom_byte(uint32_t address, uint8_t data);


void write_eeprom_word(uint32_t address, uint32_t data)
{
    FLASH_Status status;
    status = FLASH_ProgramWord(address, data);
    if(status == FLASH_COMPLETE)
		{} 
		else {}

}

void write_eeprom_halfw(uint32_t address, uint16_t data)
{
    FLASH_Status status;
    status = FLASH_ProgramHalfWord(address, data);
    if(status == FLASH_COMPLETE)
			{} 
		else {}


}



//EEPROM init

void EEPROM_init(void)
{

params = (eeprom*)START_EEPROM;

    if(params->f_write != 1)
    {
	//unlock flash
		FLASH_Unlock();
	//erase last page
		FLASH_ErasePage(START_EEPROM);
	//write new values


		//write_eeprom_halfw((uint32_t)(&(params->Tcal)), 25);
		//write_eeprom_halfw((uint32_t)(&(params->TcalValue)), (uint8_t)T_INIT);	
		//write_eeprom_halfw((uint32_t)(&(params->Tslope)), (uint16_t)F_TSLOPE);
		
		//write_eeprom_halfw((uint32_t)(&(params->f_write)), 1); //here maybe CRC
		//lock flash
		FLASH_Lock();

    }
} //EEPROM_init

void EEPROM_writeparameters(void)
{
params = (eeprom*)START_EEPROM;	      

	//unlock flash
		FLASH_Unlock();
	//erase last page
		FLASH_ErasePage(START_EEPROM);
	//write new values

		//write_eeprom_halfw((uint32_t)(&(params->Tcal)), Tcal);
		//write_eeprom_halfw((uint32_t)(&(params->TcalValue)), (uint16_t)TcalValue);	
		//write_eeprom_halfw((uint32_t)(&(params->Tslope)), (uint16_t)Tslope);
		
		//write_eeprom_halfw((uint32_t)(&(params->f_write)), 1); //here maybe CRC
		
		//lock flash
		FLASH_Lock();
}

void EEPROM_readparameters(void)
{
	
params = (eeprom*)START_EEPROM;
	

	//Tcal = (int8_t)(params->Tcal);
	//TcalValue = (int8_t)(params->TcalValue);
	//Tslope = (int16_t)(params->Tslope);

}









