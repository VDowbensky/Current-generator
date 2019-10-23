#include "eeprom.h"

const uint8_t SYNC_INIT[8] = {WORK_SYNC1, WORK_SYNC2, WORK_SYNC3, WORK_SYNC4, WORK_SYNC5, WORK_SYNC6, WORK_SYNC7, WORK_SYNC8}; //32
//#pragma data_alignment=4

  uint32_t F_Base; //4 - 0x00D90000
  uint32_t F_Step; //8 - 0x000061A8
  int32_t  F_Offset; //12

  uint32_t BitRate; //16
  uint32_t Deviation; //20
  uint32_t PkCount; //24

  uint8_t Channel; //33 - alignment - ??? 
//tx settings
  uint8_t ModSetting; //34
  uint8_t TxPower;//35
//rx settings
  uint8_t RbwDcc; //36
  uint8_t Rbw; //37
  uint8_t AfcDcc; //38
  uint8_t Abw;//39
  uint8_t AfcSetting; //40
  int8_t  LbOffset; //41 //should be int8_t
  uint8_t RssiTr; //42
  uint8_t Dagc; //43
  uint8_t LnaSetting; //44 - add LNA booster bit
  uint8_t SyncWord[8]; //32
  uint8_t PkConfig1; //45
  uint8_t PkConfig2; //46

  uint8_t NdAddr; //47

  uint8_t PkDelay; //48
  uint8_t PkLen; //49
//timeouts
  uint8_t RxTo; //50
  uint8_t RssiTo; //51
  uint16_t RF69To; //52
  uint8_t RxDelay; //53 - inter-packet RX delay

//add temperature drift coeff. here!!!
  int8_t Tcal;
  int8_t TcalValue;
  int16_t Tslope;




//EEPROM write routines

eeprom* params;

void EEPROM_init(void);
void EEPROM_readparameters(void);
void write_eeprom_word(uint32_t address, uint32_t data);
void write_eeprom_halfw(uint32_t address, uint16_t data);
void write_eeprom_byte(uint32_t address, uint8_t data);


void write_eeprom_word(uint32_t address, uint32_t data)
{
    FLASH_Status status;
    status = FLASH_ProgramWord(address, data);
    if(status == FLASH_COMPLETE)
		{} 
		else {}

}

void write_eeprom_halfw(uint32_t address, uint16_t data)
{
    FLASH_Status status;
    status = FLASH_ProgramHalfWord(address, data);
    if(status == FLASH_COMPLETE)
			{} 
		else {}


}



//EEPROM init

void EEPROM_init(void)
{

params = (eeprom*)START_EEPROM;
uint8_t i;
    
    if(params->f_write != 1)
    {
	//unlock flash
		FLASH_Unlock();
	//erase last page
		FLASH_ErasePage(START_EEPROM);
	//write new values
			write_eeprom_word((uint32_t)(&(params->F_Base)), F_BASE);
			write_eeprom_word((uint32_t)(&(params->F_Step)), F_STEP);
			write_eeprom_word((uint32_t)(&(params->F_Offset)), (uint32_t)F_OFFSET);

			write_eeprom_word((uint32_t)(&(params->BitRate)), WORK_BITRATE);
			write_eeprom_word((uint32_t)(&(params->Deviation)), WORK_DEVIATION);
			write_eeprom_word((uint32_t)(&(params->PkCount)), PACKET_COUNT);

			write_eeprom_halfw((uint32_t)(&(params->Channel)), WORK_CHANNEL);
			write_eeprom_halfw((uint32_t)(&(params->ModSetting)), WORK_MOD_SETTING);
			write_eeprom_halfw((uint32_t)(&(params->TxPower)), WORK_TXPOWER);

		write_eeprom_halfw((uint32_t)(&(params->RbwDcc)), WORK_RBW_DCC);
		write_eeprom_halfw((uint32_t)(&(params->Rbw)), WORK_RBW_BW);
		write_eeprom_halfw((uint32_t)(&(params->AfcDcc)), WORK_AFC_DCC);
		write_eeprom_halfw((uint32_t)(&(params->Abw)), WORK_AFC_BW);

		write_eeprom_halfw((uint32_t)(&(params->AfcSetting)), WORK_AFCSETTING);
		write_eeprom_halfw((uint32_t)(&(params->LbOffset)), WORK_LBOFFSET);
		write_eeprom_halfw((uint32_t)(&(params->RssiTr)), WORK_RSSITR);
		write_eeprom_halfw((uint32_t)(&(params->Dagc)), WORK_TESTDAGC);
		write_eeprom_halfw((uint32_t)(&(params->LnaSetting)), WORK_LNASET);
		
		for (i=0; i<8; i++) write_eeprom_halfw((uint32_t)(&(params->SyncWord[i])), SYNC_INIT[i]);
		
		write_eeprom_halfw((uint32_t)(&(params->PkConfig1)), WORK_PACKETCONFIG1);
		write_eeprom_halfw((uint32_t)(&(params->PkConfig2)), WORK_PACKETCONFIG2);
		
 // uint8_t NdAddr; // = 1; //47
		write_eeprom_halfw((uint32_t)(&(params->NdAddr)), 1);

		write_eeprom_halfw((uint32_t)(&(params->PkDelay)), PACKET_DELAY);
		write_eeprom_halfw((uint32_t)(&(params->PkLen)), WORK_PACKET_LEN);

		write_eeprom_halfw((uint32_t)(&(params->RxTo)), WORK_RXTO);
		write_eeprom_halfw((uint32_t)(&(params->RssiTo)), WORK_RSSITO);
		write_eeprom_halfw((uint32_t)(&(params->RF69To)), RF69TIMEOUT);
		write_eeprom_halfw((uint32_t)(&(params->RxDelay)), WORK_RXDELAY);

		write_eeprom_halfw((uint32_t)(&(params->Tcal)), 25);
		write_eeprom_halfw((uint32_t)(&(params->TcalValue)), (uint8_t)T_INIT);	
		write_eeprom_halfw((uint32_t)(&(params->Tslope)), (uint16_t)F_TSLOPE);
		
		write_eeprom_halfw((uint32_t)(&(params->f_write)), 1); //here maybe CRC
		//lock flash
		FLASH_Lock();

    }
} //EEPROM_init

void EEPROM_writeparameters(void)
{
params = (eeprom*)START_EEPROM;	      
uint8_t i;
	
	//unlock flash
		FLASH_Unlock();
	//erase last page
		FLASH_ErasePage(START_EEPROM);
	//write new values

		write_eeprom_word((uint32_t)(&(params->F_Base)), F_Base);
		write_eeprom_word((uint32_t)(&(params->F_Step)), F_Step);
		write_eeprom_word((uint32_t)(&(params->F_Offset)), (uint32_t)F_Offset);

		write_eeprom_word((uint32_t)(&(params->BitRate)), BitRate);
		write_eeprom_word((uint32_t)(&(params->Deviation)), Deviation);
		write_eeprom_word((uint32_t)(&(params->PkCount)), PkCount);
		write_eeprom_halfw((uint32_t)(&(params->Channel)), Channel);
		write_eeprom_halfw((uint32_t)(&(params->ModSetting)), ModSetting);
		write_eeprom_halfw((uint32_t)(&(params->TxPower)), TxPower);

		write_eeprom_halfw((uint32_t)(&(params->RbwDcc)), RbwDcc);
		write_eeprom_halfw((uint32_t)(&(params->Rbw)), Rbw);
		write_eeprom_halfw((uint32_t)(&(params->AfcDcc)), AfcDcc);
		write_eeprom_halfw((uint32_t)(&(params->Abw)), Abw);

		write_eeprom_halfw((uint32_t)(&(params->AfcSetting)), AfcSetting);
		write_eeprom_halfw((uint32_t)(&(params->LbOffset)), LbOffset);
		write_eeprom_halfw((uint32_t)(&(params->RssiTr)), RssiTr);
		write_eeprom_halfw((uint32_t)(&(params->Dagc)), Dagc);
		write_eeprom_halfw((uint32_t)(&(params->LnaSetting)), LnaSetting);
		
		for (i=0; i<8; i++) write_eeprom_halfw((uint32_t)(&(params->SyncWord[i])), SyncWord[i]);
		
		write_eeprom_halfw((uint32_t)(&(params->PkConfig1)), PkConfig1);
		write_eeprom_halfw((uint32_t)(&(params->PkConfig2)), PkConfig2);

		write_eeprom_halfw((uint32_t)(&(params->NdAddr)), NdAddr);

		write_eeprom_halfw((uint32_t)(&(params->PkDelay)), PkDelay);
		write_eeprom_halfw((uint32_t)(&(params->PkLen)), PkLen);

		write_eeprom_halfw((uint32_t)(&(params->RxTo)), RxTo);
		write_eeprom_halfw((uint32_t)(&(params->RssiTo)), RssiTo);
		write_eeprom_halfw((uint32_t)(&(params->RF69To)), RF69To);
		write_eeprom_halfw((uint32_t)(&(params->RxDelay)), RxDelay);


		write_eeprom_halfw((uint32_t)(&(params->Tcal)), Tcal);
		write_eeprom_halfw((uint32_t)(&(params->TcalValue)), (uint16_t)TcalValue);	
		write_eeprom_halfw((uint32_t)(&(params->Tslope)), (uint16_t)Tslope);
		
		write_eeprom_halfw((uint32_t)(&(params->f_write)), 1); //here maybe CRC
		
		//lock flash
		FLASH_Lock();
}

void EEPROM_readparameters(void)
{
	
params = (eeprom*)START_EEPROM;
uint8_t i;
	
	F_Base = params->F_Base;
	F_Step = params->F_Step;
	F_Offset = (int32_t)(params->F_Offset);
	BitRate = params->BitRate;
	Deviation = params->Deviation;
	PkCount = params->PkCount;
	Channel = params->Channel;
	ModSetting = params->ModSetting;
	TxPower = params->TxPower;
	RbwDcc = params->RbwDcc;
	Rbw = params->Rbw;
	AfcDcc = params->AfcDcc;
	Abw = params->Abw;
	AfcSetting = params->AfcSetting;
	LbOffset = params->LbOffset;
	RssiTr = params->RssiTr;
	Dagc = params->Dagc;
	LnaSetting = params->LnaSetting;
	for (i=0; i<8; i++) SyncWord[i] = params->SyncWord[i];
	PkConfig1 = params->PkConfig1;
	PkConfig2 = params->PkConfig2;
	NdAddr = params->NdAddr;
	PkDelay = params->PkDelay;
	PkLen = params->PkLen;
	RxTo = params->RxTo;
	RssiTo = params->RssiTo;
	RF69To = params->RF69To;
	RxDelay = params->RxDelay;
	Tcal = (int8_t)(params->Tcal);
	TcalValue = (int8_t)(params->TcalValue);
	Tslope = (int16_t)(params->Tslope);

}









