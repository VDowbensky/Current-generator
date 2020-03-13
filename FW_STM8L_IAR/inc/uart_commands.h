#ifndef _UART_COMMANDS_
#define _UART_COMMANDS_
#include "main.h"



#define TXPREFIX 0xC96C //"handset" ;)
#define RXPREFIX 0x236B //"base station" ;)
#define CRCPOLY        0x18
#define RESP_OK         0x00
#define RESP_ERR        0x01

#define READALL         0xB0
#define FREQTEST        0xB1
#define SETFREQPARAMS   0xB2 //base freq., channel step
#define SETFREQOFFSET   0xB3 //frequency offset and XCO temperature slope 
#define SETSYNCWORD     0xB4


#define SETCHANNEL      0xB5
#define SETBITRATE      0xB6 

#define SETTXPARAMS     0xB7  //mod. setting, deviation, TX power
#define SETRXPARAMS     0xB8  //BW, AFC, low beta offset, RSSI tr., DAGC, LNA gain, timeouts

#define SETPACKETCONFIG 0xB9 //packet config 1 & 2

#define SETADDITIONAL   0xBA  //packet delay, packet count, temperature calibration
#define SETTEMPOFFSET   0xBB //get ambient temp. and store parameters
#define READTEMP        0xBC

#define RESETALL        0xBF  //return to initial parameters

extern const uint8_t COMMANDLIST[];

extern bool CommandFlag;

extern void handlecommand (uint8_t c);

#endif
