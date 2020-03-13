#ifndef _TIMERS_H_
#define _TIMERS_H_

#include <stdint.h>
#include "stm32f10x_tim.h"
#include "main.h"

extern void initTIM7(void);
extern void delay_ms (uint16_t ms);


#endif

