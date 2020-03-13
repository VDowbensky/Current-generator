#ifndef FLASH_EEPROM_H
#define FLASH_EEPROM_H

//#include "main.h"

#include <stdint.h>

#define FLASH_RASS_KEY1    ((uint8_t)0x56)        // First RASS key
#define FLASH_RASS_KEY2    ((uint8_t)0xAE)        // Second RASS key

//Unlock EEPROM for write
inline void EEPROM_Unlock(void)
{
  FLASH_DUKR = FLASH_RASS_KEY2;
  FLASH_DUKR = FLASH_RASS_KEY1;
}

//Lock EEPROM
inline void EEPROM_Lock(void)
{
  FLASH_IAPSR_bit.DUL=0;
}

#endif //FLASH_EEPROM_H