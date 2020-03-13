#ifndef _EEPROM_H_
#define _EEPROM_H_
#include "main.h"

//#define START_EEPROM 0x08080000
//#define START_EEPROM 0x08007000 //last sector
#define START_EEPROM 0x0800FC00 //last page



extern    int8_t Tcal;
extern    int8_t TcalValue;
extern    int16_t Tslope; 

#pragma pack (4) // - ???

typedef struct{
uint8_t f_write; //EEPROM virgin indicator


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


