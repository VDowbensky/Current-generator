#ifndef _EEPROM_H_
#define _EEPROM_H_

#include "main.h"
#include  "stm8l15x_flash.h"

extern volatile __eeprom uint32_t F_Base;
extern volatile __eeprom uint32_t F_Step;
extern volatile __eeprom int32_t F_Offset;

#endif
