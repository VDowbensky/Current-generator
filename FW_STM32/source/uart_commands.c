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

  switch (c)
  {
  case READALL: //checked
		
    //TXbuffer[3] = RF69_getversion();
    //frequency
    //TXbuffer[4] = HIGH(F_Base);
    //TXbuffer[5] = HIGL(F_Base);
    //TXbuffer[6] = LOWH(F_Base);
    //TXbuffer[7] = LOWL(F_Base);


    sendtuningresponse(61); //compute lenght here
    break;
    
  case FREQTEST: //checked
    //if 1 - switch to OOK mode, TX on for frequency measuring
    if((RXbuffer[3] & 0x01) != 0)
    {

      
    }
    //if 0 - TX off, restore all settings
    else //zero
    {

    }
    sendOK();
    break;
        
  case SETFREQPARAMS: //check!!!

    sendOK();
    break;
    
  case SETFREQOFFSET: //checked

    sendOK();
    break;
    
  case SETSYNCWORD: //check!!!
    //for(i = 0; i < 8; i++) SyncWord[i] = RXbuffer[i+3];
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

    sendOK();
    break;
    
  case SETPACKETCONFIG: //check!!!

    sendOK();
    break;
    
  case SETADDITIONAL: //check!!!


    sendOK();
    break;

  case SETTEMPOFFSET:

    sendOK();
    break;
    
  case READTEMP:

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


