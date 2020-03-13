#include "eeprom.h"
#pragma data_alignment=4
volatile __eeprom uint32_t F_Base = F_BASE; //4 - 0x00D90000
volatile __eeprom uint32_t F_Step = F_STEP; //8 - 0x000061A8
volatile __eeprom int32_t  F_Offset = F_OFFSET; //12

volatile __eeprom uint32_t BitRate = WORK_BITRATE; //16
volatile __eeprom uint32_t Deviation = WORK_DEVIATION; //20
volatile __eeprom uint32_t PkCount = PACKET_COUNT; //24

volatile __eeprom uint8_t Channel = WORK_CHANNEL; //33 - alignment - ??? 
//tx settings

volatile __eeprom uint8_t TxPower = WORK_TXPOWER; //35
//rx settings




volatile __eeprom int8_t  LbOffset = WORK_LBOFFSET; //41 //should be int8_t
volatile __eeprom uint8_t RssiTr = WORK_RSSITR; //42



volatile __eeprom uint8_t SyncWord[8] = {WORK_SYNC1, WORK_SYNC2, WORK_SYNC3, WORK_SYNC4, WORK_SYNC5, WORK_SYNC6, WORK_SYNC7, WORK_SYNC8}; //32



volatile __eeprom uint8_t NdAddr = 0; //47

volatile __eeprom uint8_t PkDelay = PACKET_DELAY; //48
volatile __eeprom uint8_t PkLen = WORK_PACKET_LEN; //49
//timeouts
volatile __eeprom uint8_t RxTo = WORK_RXTO; //50
volatile __eeprom uint8_t RssiTo = WORK_RSSITO; //51
volatile __eeprom uint16_t RF69To = RF69TIMEOUT; //52
volatile __eeprom uint8_t RxDelay = WORK_RXDELAY; //53 - inter-packet RX delay

//add temperature drift coeff. here!!!
volatile __eeprom int8_t Tcal = TCAL;
volatile __eeprom int8_t TcalValue = T_INIT;
volatile __eeprom int16_t Tslope = F_TSLOPE; 





//functions
/*
void writepar8(uint8_t d, uint8_t s);
void writepars8(int8_t d, int8_t s);
void writepar32(uint32_t d, uint32_t s);


void writepar8(uint8_t d, uint8_t s)
{
  FLASH_Unlock(FLASH_MemType_Data);
  FLASH_WaitForLastOperation(FLASH_MemType_Data);
  FLASH_EraseByte((uint32_t)&d);
  FLASH_ProgramByte((uint32_t)&d, s);
  FLASH_Lock(FLASH_MemType_Data);
}

void writepars8(int8_t d, int8_t s)
{
  FLASH_Unlock(FLASH_MemType_Data);
  //d = s;
  //FLASH_ProgramByte(d, s);
  FLASH_WaitForLastOperation(FLASH_MemType_Data);
  FLASH_Lock(FLASH_MemType_Data);
}

void writepar32(uint32_t d, uint32_t s)
{
  FLASH_Unlock(FLASH_MemType_Data);
  //d = s;
  //FLASH_ProgramWord(d, s);
  FLASH_WaitForLastOperation(FLASH_MemType_Data);
  FLASH_Lock(FLASH_MemType_Data);
}
*/



