#ifndef _EEPROM_H_
#define _EEPROM_H_
#include "main.h"

//#define START_EEPROM 0x08080000
//#define START_EEPROM 0x08007000 //last sector
#define START_EEPROM 0x0800FC00 //last page


extern 	uint32_t F_Base; //4 - 0x00D90000
extern  uint32_t F_Step; //8 - 0x000061A8
extern  int32_t  F_Offset; //12

extern  uint32_t BitRate; //16
extern  uint32_t Deviation; //20
extern  uint32_t PkCount; //24

extern  uint8_t Channel; //33 - alignment - ??? 
//tx settings
extern  uint8_t ModSetting; //34
extern  uint8_t TxPower; //35
//rx settings
extern  uint8_t RbwDcc; //36
extern  uint8_t Rbw; //37
extern  uint8_t AfcDcc; //38
extern  uint8_t Abw; //39
extern  uint8_t AfcSetting; //40
extern    int8_t  LbOffset; //41 //should be int8_t
extern    uint8_t RssiTr; //42
extern    uint8_t Dagc; //43
extern    uint8_t LnaSetting; //44 - add LNA booster bit
extern    uint8_t SyncWord[]; //32
extern    uint8_t PkConfig1; //45
extern    uint8_t PkConfig2; //46

extern    uint8_t NdAddr; //47

extern    uint8_t PkDelay; //48
extern    uint8_t PkLen; //49
//timeouts
extern    uint8_t RxTo; //50
extern    uint8_t RssiTo; //51
extern    uint16_t RF69To; //52
extern    uint8_t RxDelay; //53 - inter-packet RX delay

//add temperature drift coeff. here!!!
extern    int8_t Tcal;
extern    int8_t TcalValue;
extern    int16_t Tslope; 

#pragma pack (4) // - ???

typedef struct{
uint8_t f_write; //EEPROM virgin indicator

//#pragma data_alignment=4
uint32_t F_Base; // = F_BASE; //4 - 0x00D90000
uint32_t F_Step; // = F_STEP; //8 - 0x000061A8
int32_t  F_Offset; // = F_OFFSET; //12

uint32_t BitRate; // = WORK_BITRATE; //16
uint32_t Deviation; // = WORK_DEVIATION; //20
uint32_t PkCount; // = PACKET_COUNT; //24

uint16_t Channel; // = WORK_CHANNEL; //33 - alignment - ??? 
//tx settings
uint16_t ModSetting; // = WORK_MOD_SETTING; //34
uint16_t TxPower; // = WORK_TXPOWER; //35
//rx settings
uint16_t RbwDcc; // = WORK_RBW_DCC; //36
uint16_t Rbw; // = WORK_RBW_BW; //37
uint16_t AfcDcc; // = WORK_AFC_DCC; //38
uint16_t Abw; // = WORK_AFC_BW; //39
uint16_t AfcSetting; // = WORK_AFCSETTING; //40
int16_t  LbOffset; // = WORK_LBOFFSET; //41 //should be int8_t
uint16_t RssiTr; // = WORK_RSSITR; //42
uint16_t Dagc; // = WORK_TESTDAGC; //43
uint16_t LnaSetting; // = WORK_LNASET; //44 - add LNA booster bit
uint16_t SyncWord[8]; // = {WORK_SYNC1, WORK_SYNC2, WORK_SYNC3, WORK_SYNC4, WORK_SYNC5, WORK_SYNC6, WORK_SYNC7, WORK_SYNC8}; //32
uint16_t PkConfig1; // = WORK_PACKETCONFIG1; //45
uint16_t PkConfig2; // = WORK_PACKETCONFIG2; //46

uint16_t NdAddr; // = 1; //47

uint16_t PkDelay; // = PACKET_DELAY; //48
uint16_t PkLen; // = WORK_PACKET_LEN; //49
//timeouts
uint16_t RxTo; // = WORK_RXTO; //50
uint16_t RssiTo; // = WORK_RSSITO; //51
uint16_t RF69To; // = RF69TIMEOUT; //52
uint16_t RxDelay; // = WORK_RXDELAY; //53 - inter-packet RX delay

//add temperature drift coeff. here!!!
int16_t Tcal; // = TCAL;
int16_t TcalValue; // = T_INIT;
int16_t Tslope; // = F_TSLOPE;   

} eeprom;

extern eeprom* params;
extern void EEPROM_init(void);
extern void EEPROM_readparameters(void);
void EEPROM_writeparameters(void);
//extern void write_eeprom_word(uint32_t address, uint32_t data);
//extern void write_eeprom_halfw(uint32_t address, uint16_t data);
//extern void write_eeprom_byte(uint32_t address, uint8_t data);


#endif


