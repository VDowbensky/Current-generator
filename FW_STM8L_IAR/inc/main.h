#ifndef _MAIN_H_
#define _MAIN_H_

//#define HIGH(x) (x>>24)
//#define HIGL(x) ((x>>16) & 0xFF)
//#define LOWH(x) ((x>>8) & 0xFF)
//#define LOWL(x) ((x) & 0xFF)

#define F_CPU 16000000UL

#include <string.h> 
#include <intrinsics.h>
#include "uart_interface.h"
#include "gpio_interface.h"
#include "spi_interface.h"
#include "eeprom.h"
#include "dac.h"
#include "macro.h"
#include "testmode.h"
#include "uart_commands.h"
#include "user_settings.h"


#if !defined(F_CPU)
#warning no F_CPU
#endif

#define KEYDELAY 100
#define KEY_LEFT 1
#define KEY_RIGHT 2
#define KEY_BOTH 3

#define WORK_MODE_STANDBY 0
#define WORK_MODE_RX 1
#define WORK_MODE_TX 2

extern void delay_ms (uint16_t ms);

extern void TimingDelay_Decrement(void);

extern __IO uint16_t TimingDelay;
extern volatile uint8_t Key; //key code


extern uint8_t work_mode;

//extern bool RxState;


extern int32_t DebugVar0;
extern int32_t DebugVar1;
extern int32_t DebugVar2;
extern int32_t DebugVar3;

#endif