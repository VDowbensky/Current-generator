#include "uart_commands.h"

_Bool CommandFlag;

const uint8_t COMMANDLIST[]= {READALL,4, FREQTEST,5, SETFREQPARAMS,12, SETFREQOFFSET,10, SETSYNCWORD,12, SETCHANNEL,5, SETBITRATE,8, SETTXPARAMS,10, SETRXPARAMS,13, SETPACKETCONFIG, 6, SETADDITIONAL,9, SETTEMPOFFSET,5, READTEMP,4, RESETALL,8};

//functions
void handlecommand (uint8_t c);

void sendtuningresponse(uint8_t r);
void sendOK(void);
void sendERR(void);


void handlecommand (uint8_t c)

{
  uint8_t i;
  switch (c)
  {
  case READALL: //checked
		
    TXbuffer[3] = RF69_getversion();
    //frequency
    TXbuffer[4] = HIGH(F_Base);
    TXbuffer[5] = HIGL(F_Base);
    TXbuffer[6] = LOWH(F_Base);
    TXbuffer[7] = LOWL(F_Base);
    
    TXbuffer[8] = HIGH(F_Step);
    TXbuffer[9] = HIGL(F_Step);
    TXbuffer[10] = LOWH(F_Step);
    TXbuffer[11] = LOWL(F_Step);
    
    TXbuffer[12] = HIGH(F_Offset);
    TXbuffer[13] = HIGL(F_Offset);
    TXbuffer[14] = LOWH(F_Offset);
    TXbuffer[15] = LOWL(F_Offset);
    
    TXbuffer[16] = HIGH(BitRate);
    TXbuffer[17] = HIGL(BitRate);
    TXbuffer[18] = LOWH(BitRate);
    TXbuffer[19] = LOWL(BitRate);
    
    TXbuffer[20] = HIGH(Deviation);
    TXbuffer[21] = HIGL(Deviation);
    TXbuffer[22] = LOWH(Deviation);
    TXbuffer[23] = LOWL(Deviation);
    
    TXbuffer[24] = ModSetting;
    TXbuffer[25] = TxPower;
    
    TXbuffer[26] = Channel;
    
    TXbuffer[27] = RbwDcc;
    TXbuffer[28] = Rbw;
    TXbuffer[29] = AfcDcc;
    TXbuffer[30] = Abw;
    
    TXbuffer[31] = AfcSetting;
    TXbuffer[32] = (uint8_t)LbOffset;
    TXbuffer[33] = RssiTr;
    TXbuffer[34] = Dagc;
    TXbuffer[35] = LnaSetting;
    
    for(i = 0; i<8; i++) TXbuffer[i+36] = SyncWord[i];//43
    TXbuffer[44] = PkConfig1;
    TXbuffer[45] = PkConfig2;
    TXbuffer[46] = NdAddr;
    
    TXbuffer[47] = RxTo;
    TXbuffer[48] = RssiTo;
    TXbuffer[49] = HI(RF69To);
    TXbuffer[50] = LO(RF69To);
    TXbuffer[51] = RxDelay;
    
    TXbuffer[52] = (uint8_t)Tcal;
    TXbuffer[53] = (uint8_t)TcalValue;
    TXbuffer[54] = HI(Tslope);
    TXbuffer[55] = LO(Tslope);
    
    TXbuffer[56] = HIGH(PkCount);
    TXbuffer[57] = HIGL(PkCount);
    TXbuffer[58] = LOWH(PkCount);
    TXbuffer[59] = LOWL(PkCount);

    TXbuffer[60] = PkDelay;

    sendtuningresponse(61); //compute lenght here
    break;
    
  case FREQTEST: //checked
    //if 1 - switch to OOK mode, TX on for frequency measuring
    if((RXbuffer[3] & 0x01) != 0)
    {
      //save RF69 state if necessary
      FreqTest = 1;
      RF69_setopmode (RF_OPMODE_STANDBY);
      //switch to OOK mode and set 1
      RF69_setmodulation(DATA_MODE_NOBITSYNC | MOD_TYPE_OOK | MOD_SHAPING_NONE);
      RF69_setopmode (RF_OPMODE_TRANSMITTER);
      
    }
    //if 0 - TX off, restore all settings
    else //zero
    {
      RF69_init();
      FreqTest = 0;
      //restore RF69 state if necessary
    }
    sendOK();
    break;
        
  case SETFREQPARAMS: //check!!!
    //set frequency and channel step - from RXbuffer[3]
	  F_Base = 16777216*RXbuffer[3] + 65536*RXbuffer[4] + 256*RXbuffer[5]+RXbuffer[6];
		F_Step = 16777216*RXbuffer[7] + 65536*RXbuffer[8] + 256*RXbuffer[9]+RXbuffer[10];
		EEPROM_writeparameters();
    //reload RF69 here
    RF69_setchannel(Channel);
    sendOK();
    break;
    
  case SETFREQOFFSET: //checked
    //set initial freq. offset and temperature drift parameters
    //frequency offset
		F_Offset = 16777216*RXbuffer[3] + 65536*RXbuffer[4] + 256*RXbuffer[5]+RXbuffer[6];
		Tslope = 256*RXbuffer[7]+RXbuffer[8];
		EEPROM_writeparameters();
    //reload RF69 here
    RF69_setchannel(Channel);
    sendOK();
    break;
    
  case SETSYNCWORD: //check!!!
    //for(i = 0; i < 8; i++) SyncWord[i] = RXbuffer[i+3];
    //RF69_init();
    //sendOK();
    break;
    
  case SETCHANNEL: //checked
    Channel = RXbuffer[3];
		EEPROM_writeparameters();
    RF69_setchannel(Channel);
    sendOK();
    break;
    
  case SETBITRATE: //check!!!
		BitRate = 16777216*RXbuffer[3] + 65536*RXbuffer[4] + 256*RXbuffer[5]+RXbuffer[6];
		EEPROM_writeparameters();
    //RF69_init(); //it's not correct. Change bit rate register only
    sendOK();
    break;
    
  case SETTXPARAMS: //check!!!
    //FLASH_Unlock(FLASH_MemType_Data);
    //deviation
		Deviation = 16777216*RXbuffer[3] + 65536*RXbuffer[4] + 256*RXbuffer[5]+RXbuffer[6];
    //mod. setting
    ModSetting = RXbuffer[7];
    //TX power
    TxPower = RXbuffer[8];
		EEPROM_writeparameters();
    //RF69_init(); //it's not correct. Change modulation and TX power registers only
    RF69_setpower(TxPower);
    sendOK();
    break;
    
  case SETRXPARAMS: //check!!!
    //FLASH_Unlock(FLASH_MemType_Data);
    RbwDcc = RXbuffer[3];
    Rbw = RXbuffer[4];
    AfcDcc = RXbuffer[5];
    Abw = RXbuffer[6];
    AfcSetting = RXbuffer[7];
    LbOffset = RXbuffer[8];
    RssiTr = RXbuffer[9];
    Dagc = RXbuffer[10];
    LnaSetting = RXbuffer[11];
		EEPROM_writeparameters();
    //RF69_init();//it's not correct. Change RX registers only
    sendOK();
    break;
    
  case SETPACKETCONFIG: //check!!!
    //FLASH_Unlock(FLASH_MemType_Data);
    PkConfig1 = RXbuffer[3];
    PkConfig2 = RXbuffer[4];
    EEPROM_writeparameters();
    sendOK();
    break;
    
  case SETADDITIONAL: //check!!!

		PkCount = 16777216*RXbuffer[3] + 65536*RXbuffer[4] + 256*RXbuffer[5]+RXbuffer[6];
    //packet delay
    PkDelay = RXbuffer[7];
    //RX initial timeout
   //RxTo = RXbuffer[8];
    //RSSI timeout
    //RssiTo = RXbuffer[9];
    //RF69 reload timeout
    //RF69To = *(uint16_t*)(&RXbuffer[10]); 
    //inter-packet RX delay
    //RxDelay = RXbuffer[12];
		EEPROM_writeparameters();
    RF69_init();
    sendOK();
    break;

  case SETTEMPOFFSET:
    RF69_setopmode (RF_OPMODE_STANDBY);
    Tcal = RXbuffer[3];
    //read temp. value
    TcalValue = RF69_tempmeas();
		EEPROM_writeparameters();
    if(FreqTest == 1) RF69_setopmode (RF_OPMODE_TRANSMITTER);
    sendOK();
    break;
    
  case READTEMP:
    TXbuffer[3] = Temperature;
    sendtuningresponse(4);
    break;      
    
  case RESETALL: //check!!!
    //check password - not implemented
    //restore initial parameters
    
    //init RF69
    //RF69_init();
    sendOK();
    break;

  default: //nothing to do
    break;
  }
  //clear RX buffer here if necessary 
}

void sendtuningresponse(uint8_t r)
{
  //TX buffer
  TXbuffer[0] = HI(TXPREFIX);
  TXbuffer[1] = LO(TXPREFIX);
  TXbuffer[2] = Command;
  TXbuffer[r] = compTxCRC(r);
  USART_SendBlock(r);
  
}

void sendOK(void)
{
  TXbuffer[3] = RESP_OK;
  sendtuningresponse(4);
}

void sendERR(void)
{
  TXbuffer[3] = RESP_ERR;
  sendtuningresponse(4);
}


