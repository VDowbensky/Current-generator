#ifndef _MACRO_H_
#define _MACRO_H_

#define HI(x) ((x)>>8)
#define LO(x) ((x)& 0xFF)

#define HIGH(x) ((x & 0xFF000000) >> 24)
#define HIGL(x) ((x & 0x00FF0000) >> 16)
#define LOWH(x) ((x & 0x0000FF00) >> 8)
#define LOWL(x)  (x & 0x000000FF)

#endif
