#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <STM8\STM8L151K6.h>
#include <intrins.h>

typedef unsigned long DWORD;
typedef unsigned short WORD;
typedef unsigned char BYTE;


#define KEY_UP 		1
#define KEY_DOWN 	2
#define KEY_LEFT	3
#define KEY_RIGHT 4
#define KEY_ENTER 5



#define HI(x) ((x)>>8)
#define LO(x) ((x)& 0xFF)

extern void delay(WORD msec);

#endif

