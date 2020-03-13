#ifndef _DAC_H_
#define _DAC_H_
#include "stm8l15x_dac.h"
#include "main.h"

extern void initDAC(void);
extern void setvoltage(uint16_t v);

#endif
