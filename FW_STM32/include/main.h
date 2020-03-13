#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdint.h>
//#include "stm32f1xx_conf.h"
#include "macro.h"
#include "gpio.h"
#include "timers.h"
#include "spi.h"
#include "uart.h"

#include "eeprom.h"

#include "mysettings.h"
#include "user_settings.h"
#include "testmode.h"
#include "uart_commands.h"



extern volatile uint8_t Key; //key code


extern int32_t DebugVar0;
extern int32_t DebugVar1;
extern int32_t DebugVar2;
extern int32_t DebugVar3;


#endif
