#ifndef _TESTMODE_H_
#define _TESTMODE_H_
#include "main.h"

#define F_CORR_TIME 1000 //1 s

extern void test_loop(void);
extern void cbUSART1_RXtestirq(void);
extern uint8_t compTxCRC (uint8_t c);

extern _Bool TestMode;
extern _Bool FreqTest;
extern uint8_t Command;


#endif

