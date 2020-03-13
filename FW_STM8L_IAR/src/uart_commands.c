#include "uart_commands.h"

bool CommandFlag;

const uint8_t COMMANDLIST[]= {READALL,4, FREQTEST,5, SETFREQPARAMS,12, SETFREQOFFSET,10, SETSYNCWORD,12, SETCHANNEL,5, SETBITRATE,8, SETTXPARAMS,10, SETRXPARAMS,13, SETPACKETCONFIG, 6, SETADDITIONAL,9, SETTEMPOFFSET,5, READTEMP,4, RESETALL,8};

//functions
void handlecommand (uint8_t c);

void sendtuningresponse(uint8_t r);
void sendOK(void);
void sendERR(void);


void handlecommand (uint8_t c)

{
  //uint8_t i;
  switch (c)
  {
  case READALL: //checked
    //send all parameters


    sendtuningresponse(61); //compute lenght here
    break;
    
  case FREQTEST: //checked


    sendOK();
    break;
        
  case SETFREQPARAMS: //check!!!

    sendOK();
    break;
    
  case SETFREQOFFSET: //checked

    sendOK();
    break;
    
  case SETSYNCWORD: //check!!!
    //FLASH_Unlock(FLASH_MemType_Data);
    //for(i = 0; i < 8; i++) SyncWord[i] = RXbuffer[i+3];
    //FLASH_Lock(FLASH_MemType_Data);
    //RF69_init();
    //sendOK();
    break;
    
  case SETCHANNEL: //checked

    sendOK();
    break;
    
  case SETBITRATE: //check!!!

    sendOK();
    break;
    
  case SETTXPARAMS: //check!!!

    sendOK();
    break;
    
  case SETRXPARAMS: //check!!!

    break;
    
  case SETPACKETCONFIG: //check!!!
    FLASH_Unlock(FLASH_MemType_Data);

    FLASH_Lock(FLASH_MemType_Data);
    sendOK();
    break;
    
  case SETADDITIONAL: //check!!!

    sendOK();
    break;
    
  case SETTEMPOFFSET:

    sendOK();
    break;
    
  case READTEMP:

    sendtuningresponse(4);
    break;      
    
  case RESETALL: //check!!!

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


