#include "commands.h"
#include "uart.h"
#include "timers.h"
#include "eeprom.h"
#include "gpio.h"
#include "dac.h"


void compCRC (BYTE crcCount);
void comp_crc (BYTE b);
void checkpacket (BYTE packlen);
void handlecommand(void);
bit checkEmptyID(void);
bit checkpassword(void);
void sendpacket(BYTE txcount);
void sendOKresponse(void);
void sendERRresponse(void);
void sendrequest(void);

BYTE CRC;
BYTE TxCRC;
BYTE RxCRC;
bit F_Comm;
BYTE Command;
bit TuneMode;
bit F_Comm;
bit Lister;

code const BYTE COMMANDLIST[] = {C_READONCE,9, C_READCONT,9, TC_ENTRY,4, 0,0};
code const BYTE TUNELIST[] = {TC_RD_SN,4, TC_RD_CONFIG,4, TC_WR_CONFIG,5, TC_RD_OFFSET,4, 
TC_WR_OFFSET,6, TC_RD_VTUNE,4, TC_WR_VTUNE,5, TC_WRDAC12,6, TC_WRDAC8,5, TC_RD_GAIN,4, TC_WR_GAIN,5, TC_WR_DEFAULT,
4, TC_WR_SN,10, TC_RESET_SN,8, TC_EXIT,4, 0, 0};



void compCRC (BYTE crcCount)
{  	
	BYTE i;
	CRC=0;
	for (i=0; i<(crcCount); i++)
	{
		comp_crc(TxBuffer[i]);
		TxCRC=CRC;
	}

}//CompCRC


void comp_crc (BYTE b)
{
	BYTE j;
	for (j=8; j>0; j--)
	{
		if ( (b ^ CRC) & 0x01) 
		{ 
      	CRC = ( (CRC ^ CRCPOLY) >> 1 ) | 0x80; 
    	} 
		else 
		{ 
      	CRC >>= 1; 
    	} 
    	b >>= 1;
	}
}//comp_crc

void checkpacket (BYTE packlen)
{
 	BYTE i;
	//RxCRC = 0;
	CRC=0;
	for (i=0; i<packlen; i++)	
	{
	comp_crc (RxBuffer[i]);
	RxCRC = CRC;
	}
	if (RxCRC == RxBuffer[packlen]) 
	{
	F_Comm = 1;
	Command = RxBuffer[2];
	}
	else clearRxBuff();
	
} 

void handlecommand(void)
{	 	
		F_Comm = 0;
		CommError = 0;
		RxStatus = 0;
		//Command=RxBuffer[2];
		switch (Command)
		{
		case C_READONCE:
		case C_READCONT:
		{
		DWORD tmp;
		ErrCounter = MAXERRCOUNT; //reset error counter
		CommError = 0;
		LED_set(1);
		tmp = RxBuffer[6]+(WORD)(256*RxBuffer[7]);
		tmp = (tmp*((Gain & ~0x80)+4))/4;
		DACvalue = (WORD)tmp/16;
		updateDAC();
		if (CheckERF) blink(1); //normal current mode
		else blink (3); //error - current loop open!
		break;
		}
		
		case TC_ENTRY:
		//tune mode entry
		TuneMode = 1;
		sendOKresponse();
		blink(5);
		break;
	

		case TC_RD_SN: //send date of manufacturing & serial number
		 	{
			BYTE i;
			for (i=0; i<8; i++) TxBuffer[i+3]=PARAMS[i];
			//TxBuffer[17]=NetAddr;
			//TxBuffer[13] = LO(DACvalue);
			//TxBuffer[14] = HI(DACvalue);
			//TxCount=21;
			sendpacket(11);
			}
			break;

		case TC_RD_CONFIG: //fake response, for compatibility
		TxBuffer[3] = 0; 
		sendpacket(4);
		break;
			
		case TC_WR_CONFIG: //fake response, for compatibility
		sendOKresponse();			
		break;
			
		case TC_RD_OFFSET:
		TxBuffer[3] = Offset12;
		TxBuffer[4] = 0; //offset8 not implemented
		sendpacket(5);
		break;
		
			
		case TC_WR_OFFSET:
		Offset12 = RxBuffer[3];
		ee_read();
		EEbuffer[9] = Offset12;
		ee_pgm();
		updateDAC();
		sendOKresponse();
		break;
			
		case TC_RD_VTUNE:
		TxBuffer[3] = Vtune;
		sendpacket(4);
		break;
			
			
		case TC_WR_VTUNE:
		Vtune = RxBuffer[3];
		ee_read();
		EEbuffer[8] = Vtune;
		ee_pgm();
		updateTIM3();
		updateDAC();
		sendOKresponse();
		break;
		
		case TC_WRDAC12:
		{
		DWORD tmp;
		ErrCounter = MAXERRCOUNT; //reset error counter
		CommError = 0;
		//LED = 0;
		tmp = RxBuffer[3]+(WORD)(256*RxBuffer[4]);
		tmp = (tmp*((Gain & ~0x80)+4))/4;
		DACvalue = (WORD)tmp;
		updateDAC();
		if (CheckERF) blink(1); //normal current mode
		else blink (3); //error - current loop open!
		break;
		}
		  
		case TC_WRDAC8:
		sendOKresponse();
		break;
		
		case TC_RD_GAIN://send 1 zero byte 
		TxBuffer[3] = Gain;
		sendpacket(4);
		break;

		case TC_WR_GAIN://send 2 dummy byte, maybe fake value of Vcc (about 3,3 V).
		Gain = RxBuffer[3];
		ee_read();
		EEbuffer[10] = Gain;
		ee_pgm();
		updateDAC();
		if (Gain & 0x80) Lister = 1;
		else Lister = 0;
		sendOKresponse();
		break;


		case TC_WR_DEFAULT:
		sendOKresponse();
	 	break;
		
		case TC_WR_SN:
		//check for zero serial number
		if (!checkEmptyID()) sendERRresponse();
			else 
		 	
		 		{
				BYTE i;
				ee_read();
				for (i=0; i<6; i++)	EEbuffer[i] = RxBuffer[i+3];
				ee_pgm();
		 		sendOKresponse();
				}
		 		break;
				
	
		case TC_RESET_SN:
		if (!checkpassword()) sendERRresponse();
		 else
		 	{
			BYTE i;
			ee_read();
			for (i=0; i<6; i++) EEbuffer[i] = 0;
			ee_pgm();
			sendOKresponse();
			}
		break;
		
		case TC_EXIT://update parameters, then blink 5 times and go to work mode
		sendOKresponse();
		blink(5);
		TuneMode = 0;
		readparameters();
		break;
		
		
		default:
		break;	//nothing to do

		}//switch (Command)
		clearRxBuff();
		//else
	} //void EDEhandle(void)
	
bit checkEmptyID(void)
{

	BYTE i;
	ee_read();
	for (i=0; i<6; i++)
	{
	if (EEbuffer[i] !=0) return 0;
	}
	return 1;
}

bit checkpassword(void)
{
	BYTE i;
	for (i=0; i<4; i++)
	{
	if (RxBuffer[i+3] != PASSWORD[i]) return 0;
	}
	return 1;
}

void sendpacket(BYTE txcount)
{
		if (!TuneMode) TxBuffer[0]=TXPREFIX;
		else TxBuffer[0]=TUNEPREFIX;
		if (!TuneMode) TxBuffer[1]=0xFF;
		else TxBuffer[1]=IDENT;
		TxBuffer[2]=Command;
		//other fields are filled in command handler
		compCRC(txcount);
		TxBuffer[txcount]=TxCRC;
		RxPointer=0;
		//delay(5);
		putpack(txcount);
		clearRxBuff();//RxFlag=0;//command executed

}
void sendOKresponse(void)
{		TxBuffer[3]=0;
		sendpacket(4);
		blink(2);
}

void sendERRresponse(void)
{		TxBuffer[3]=1;
		sendpacket(4);
		blink(3);
}

void sendrequest(void)
{
	if (Lister || TuneMode) 
	{
		
	}
	else
	{
		Command = C_READONCE;
		sendpacket(3);
	}
	Tim2Flag = 0;
}
