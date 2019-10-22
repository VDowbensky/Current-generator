#ifndef _ECMA_0896_
#define _ECMA_0896_

#include "global.h"

#define CONTRAST 10

extern void initLCD(void);
//extern void writebyte (char  ch);
//extern void commandLCD(char comLCD);
extern void lcdprint(char symbol);
extern void lcdprintstr(char  LCDSTRING[], BYTE row);
extern void cls (void);
extern void updateLCD(void);

#endif