#ifndef _RF69_H_
#define _RF69_H_


#include "macro.h"
#include "main.h"
#include "user_settings.h"
#include "spi.h"



#define RF69BUFFERSIZE 66
//hardware definitions (oscillator etc.)

#define FOSC 32000000L
#define FULL_DIV 524288L
#define PREDIV 2048L
#define F_PREDIV (FOSC/PREDIV)
#define F_MUL (FULL_DIV/PREDIV)


//#define NBASE (F_BASE/F_PREDIV)*F_MUL + ((F_BASE%F_PREDIV)*F_MUL)/F_PREDIV //divider for channel 0 (initial frequency)


//registers and bit fields
#define REG_FIFO       		 0x00

// RegOpMode
#define REG_OPMODE       	 0x01
#define RF_OPMODE_SEQUENCER_OFF       0x80
#define RF_OPMODE_SEQUENCER_ON        0x00  // Default
#define RF_OPMODE_LISTEN_ON           0x40
#define RF_OPMODE_LISTEN_OFF          0x00  // Default
#define RF_OPMODE_LISTENABORT         0x20
#define RF_OPMODE_SLEEP               0x00
#define RF_OPMODE_STANDBY             0x04  // Default
#define RF_OPMODE_SYNTHESIZER         0x08
#define RF_OPMODE_TRANSMITTER         0x0C
#define RF_OPMODE_RECEIVER            0x10

//modulation
#define REG_DATAMODUL    	 0x02
//modulation settings definitions (rarely used settings)
#define DATA_MODE_PACKET 			 0x00
#define DATA_MODE_RESERVED			 0x40
#define DATA_MODE_BITSYNC			 0x80
#define DATA_MODE_NOBITSYNC			 0xC0
#define MOD_TYPE_FSK				 0x00
#define MOD_TYPE_OOK				 0x08
//for FSK
#define MOD_SHAPING_NONE			 0x00
#define MOD_SHAPING_G10				 0x01
#define MOD_SHAPING_G05				 0x02
#define MOD_SHAPING_G03				 0x03
//for OOK
#define MOD_SHAPING_FBR				 0x01
#define MOD_SHAPING_F2BR			 0x02
#define MOD_SHAPING_RSVD			 0x03

//bit rate
#define REG_BITRATEMSB    	0x03
#define REG_BITRATELSB    	0x04

//deviation
#define REG_FDEVMSB       	0x05
#define REG_FDEVLSB       	0x06

//operating RF frequency
#define REG_FRFMSB        	0x07
#define REG_FRFMID        	0x08
#define REG_FRFLSB        	0x09

//RC oscillator
#define REG_OSC1          	0x0A

//AFC low beta
#define REG_AFCCTRL       	0x0B
#define AFC_LOWBETA_STANDARD		0
#define AFC_LOWBETA_IMPROVED		0x20

//battery control
#define REG_LOWBAT          0x0C //reserved in RF69
//listen mode reg 1
#define REG_LISTEN1         0x0D
#define LISTEN_RESOL_IDLE_RSVD		0
#define LISTEN_RESOL_IDLE_64us		0x40
#define LISTEN_RESOL_IDLE_4100us	0x80
#define LISTEN_RESOL_IDLE_262ms		0xC0
#define LISTEN_RESOL_RX_RSVD		0
#define LISTEN_RESOL_RX_64us		0x10
#define LISTEN_RESOL_RX_4100us		0x20
#define LISTEN_RESOL_RX_262ms		0x30
#define LISTEN_CRIT_NOSYNC			0
#define LISTEN_CRIT_SYNC			0x08
#define LISTEN_END_RX				0
#define LISTEN_END_MODE				0x02
#define LISTEN_END_IDLE				0x04
#define LISTEN_END_RSVD				0x06

//listen mode reg 2
#define REG_LISTEN2         0x0E
#define LISTEN_COEFF_IDLE			0xF5

#define REG_LISTEN3    		0x0F
//listen mode reg 3
#define LISTEN_COEFF_RX				0x20

//chip version
#define REG_VERSION         0x10

//power amp. level
#define REG_PALEVEL         0x11
#define TXPA0								0x80
#define TXPA1								0x40
#define TXPA2								0x20
//#define PA_DEFAULT (TXPA1 | TXPA2)
//#define PWR_DEFAULT 10

//PA RAMP setting in us
#define REG_PARAMP          0x12
#define RA_RAMP_3400				0
#define PA_RAMP_2000				0x01
#define PA_RAMP_1000				0x02
#define PA_RAMP_500					0x03
#define PA_RAMP_250					0x04
#define PA_RAMP_125					0x05
#define PA_RAMP_100					0x06
#define PA_RAMP_62					0x07
#define PA_RAMP_50					0x08
#define PA_RAMP_40					0x09
#define PA_RAMP_31					0x0A
#define PA_RAMP_25					0x0B
#define PA_RAMP_20					0x0C
#define PA_RAMP_15					0x0D
#define PA_RAMP_12					0x0E
#define PA_RAMP_10					0x0F

#define REG_OCP           0x13
#define REG_AGCREF        0x14  // not present on RFM69/SX1231
#define REG_AGCTHRESH1    0x15  // not present on RFM69/SX1231
#define REG_AGCTHRESH2    0x16  // not present on RFM69/SX1231
#define REG_AGCTHRESH3    0x17  // not present on RFM69/SX1231

//LNA
#define REG_LNA           0x18
#define LNA_50						0
#define LNA_200						0x80
//bits 5...3 - current gain (read)
//bits 2...0 - gain setting
#define G_AUTO						0
#define	G1								0x01
#define	G2								0x02
#define G3								0x03
#define G4								0x04
#define G5								0x05
#define G6								0x06
#define G_RES							0x07

#define LNABOOST 0x40 //should be resetted when loading REG_LNA

//RX bandwidth
#define REG_RXBW          0x19
//AFC bandwidth
#define REG_AFCBW         0x1A 
//DCC freq.
#define DCC7                0xE0
#define DCC6                0xC0
#define DCC5                0xA0
#define DCC4                0x80
#define DCC3                0x60
#define DCC2                0x40
#define DCC1                0x20
#define DCC0                0
//BW
#define BW_500K               0
#define BW_400K               0x08
#define BW_333K               0x10
#define BW_250K               0x01
#define BW_200K               0x09
#define BW_166K               0x11
#define BW_125K               0x02
#define BW_100K               0x0A
#define BW_83K3               0x12
#define BW_62K5               0x03
#define BW_50K                0x0B
#define BW_41K7               0x13
#define BW_31K2               0x04
#define BW_25K                0x0C
#define BW_20K8               0x14
#define BW_15K6               0x05
#define BW_12K5               0x0D
#define BW_10K4               0x15
#define BW_7K8                0x06
#define BW_6K25               0x0E
#define BW_5K2                0x16
#define BW_3K9                0x07
#define BW_3K12               0x0F
#define BW_2K6                0x17

#define REG_OOKPEAK       0x1B //TODO

#define REG_OOKAVG        0x1C //TODO

#define REG_OOKFIX        0x1D //TODO

//AFC_FEI
#define REG_AFCFEI        0x1E
#define AFC_FEI_DONE	  			0x40
#define AFC_FEI_START     			0x20
#define AFC_DONE		  			0x10
#define AFC_AUTOCLEAR	  			0x08
#define AFC_AUTO_ON		  			0x04
#define AFC_CLEAR		  			0x02
#define AFC_START		  			0x01

//AFC value (read only)
#define REG_AFCMSB        0x1F
#define REG_AFCLSB        0x20

//FEI value (read only)
#define REG_FEIMSB        0x21
#define REG_FEILSB        0x22

#define REG_RSSICONFIG    0x23 
#define RSSI_DONE               0x02 //bit 1 is set if RSSI ready
#define RSSI_START              0x01

#define REG_RSSIVALUE     0x24

#define REG_DIOMAPPING1   0x25

#define DIO0_PKSENT_CRCOK       0
#define DIO0_TXREADY_PLREADY    0x40
#define DIO0_RSV_SYNCADDR       0x80
#define DIO0_PLLLOCK_RSSI       0xC0

#define DIO1_FLEVEL             0
#define DIO1_FFULL              0x10
#define DIO1_FNE                0x20
#define DIO1_PLLLOCK_TIMEOUT    0x30

#define DIO2_FNE                0
#define DIO2_DATA               0x04
#define DIO2_RSV                0x08
#define DIO2_AUTO               0x0C

#define DIO3_FFULL              0
#define DIO3_TXREADY_RSSI       0x01
#define DIO3_RSV_SYNCADDR       0x02
#define DIO3_PLLLOCK            0x03


#define REG_DIOMAPPING2   0x26

#define DIO4_MDREADY_TIMEOUT    0
#define DIO4_TXREADY_RSSI       0x40
#define DIO4_RSV_RXREADY        0x80
#define DIO4_PLLLOCK            0xC0

#define DIO5_CLKOUT             0
#define DIO5_DATA               0x10
#define DIO5_RSV                0x20
#define DIO5_MODEREADY          0x30

#define CLK_FXOSC               0
#define CLK_FXOSC2              1
#define CLK_FXOSC4              2
#define CLK_FXOSC8              3
#define CLK_FXOSC16             4
#define CLK_FXOSC32             5
#define CLK_RC                  6
#define CLK_OFF                 7
  

#define REG_IRQFLAGS1     0x27
#define MODE_READY              0x80
#define RX_READY                0x40
#define TX_READY                0x20
#define PLL_LOCK                0x10
#define RSSI_TR                 0x08
#define RX_TO                   0x04
#define AUTO_MODE               0x02
#define SYNCADDR_MATCH          0x01

#define REG_IRQFLAGS2     0x28
#define FIFO_FULL               0x80
#define FIFO_NE                 0x40
#define FIFO_LVL                0x20
#define FIFO_OVR                0x10
#define PACKET_SENT             0x08
#define PL_READY                0x04
#define CRC_OK                  0x02
//bit 0 unused.

#define REG_RSSITHRESH    0x29

#define REG_RXTIMEOUT1    0x2A
#define REG_RXTIMEOUT2    0x2B

#define REG_PREAMBLEMSB   0x2C
#define REG_PREAMBLELSB   0x2D

#define REG_SYNCCONFIG    0x2E
#define SYNCON                  0x80
#define FIFO_FILL_ADDR          0
#define FIFO_FILL_COND          0x40

#define REG_SYNCVALUE1    0x2F
#define REG_SYNCVALUE2    0x30
#define REG_SYNCVALUE3    0x31
#define REG_SYNCVALUE4    0x32
#define REG_SYNCVALUE5    0x33
#define REG_SYNCVALUE6    0x34
#define REG_SYNCVALUE7    0x35
#define REG_SYNCVALUE8    0x36

#define REG_PACKETCONFIG1 0x37
#define PACKET_LEN_FIXED        0
#define PACKET_LEN_VARIABLE     0x80
#define DC_FREE_NONE            0
#define DC_FREE_MANCHESTER      0x20
#define DC_FREE_WHITENING       0x40
#define DC_FREE_RESERVED        0x60
#define CRC_ON                  0x10
#define CRC_OFF                 0
#define CRC_AUTOCLR_OFF         0x08
#define CRC_AUTOCLR_ON          0
#define ADDR_FILT_NONE          0
#define ADDR_FILT_ADDR          0x02
#define ADDR_FILT_ADDR_BC       0x04
#define ADDR_FILT_RESERVED      0x06

#define REG_PAYLOADLENGTH 0x38

#define REG_NODEADRS      0x39

#define REG_BROADCASTADRS 0x3A

#define REG_AUTOMODES     0x3B
//enter conditions
#define ENTER_NONE                    0
#define ENTER_RE_FNE                0x20
#define ENTER_RE_FL                 0x40
#define ENTER_RE_CRC                0x60
#define ENTER_RE_PL                 0x80
#define ENTER_RE_SA                 0xA0
#define ENTER_RE_PS                 0xC0
#define ENTER_FE_FNE                0xE0
//exit conditions
#define EXIT_NONE                   0
#define EXIT_FE_FNE                 0x04
#define EXIT_RE_FL                  0x08
#define EXIT_RE_CRC                 0x0C
#define EXIT_RE_PL                  0x10
#define EXIT_RE_SA                  0x14
#define EXIT_RE_PS                  0x18
#define EXIT_RE_TO                  0x1C
//modes
#define IM_SLEEP                    0
#define IM_STANDBY                  0x01
#define IM_RX                       0x02
#define IM_TX                       0x03

#define REG_FIFOTHRESH    0x3C
#define TX_START_FIFOLEVEL      0
#define TX_START_FIFONE         0x80
//other bits - FIFO threshold

#define REG_PACKETCONFIG2 0x3D
//bits 7...4 rx delay
#define RESTARTRX               0x04 //triggers restart
#define AUTORESTART_OFF         0
#define AUTORESTART_ON          0x02
#define AES_ON                  0x01
#define AES_OFF                 0
//writeRegister(0x3D, (readRegister(0x3D) & 0xFB) | 0x20); - WTF???
#define REG_AESKEY1       0x3E
#define REG_AESKEY2       0x3F
#define REG_AESKEY3       0x40
#define REG_AESKEY4       0x41
#define REG_AESKEY5       0x42
#define REG_AESKEY6       0x43
#define REG_AESKEY7       0x44
#define REG_AESKEY8       0x45
#define REG_AESKEY9       0x46
#define REG_AESKEY10      0x47
#define REG_AESKEY11      0x48
#define REG_AESKEY12      0x49
#define REG_AESKEY13      0x4A
#define REG_AESKEY14      0x4B
#define REG_AESKEY15      0x4C
#define REG_AESKEY16      0x4D

#define REG_TEMP1         0x4E
#define T_MEASSTART             0x08
#define T_MEASRUN               0x04

#define REG_TEMP2         0x4F //temp. value

#define REG_TESTLNA       0x58
#define LNA_NORM                0x1B
#define LNA_HIGH                0x2D

#define REG_TESTPA1       0x5A  // only present on RFM69HW/SX1231H
#define PA1_NORMAL              0x55
#define PA1_BOOST               0x5D

#define REG_TESTPA2       0x5C  // only present on RFM69HW/SX1231H
#define PA2_NORMAL              0x70
#define PA2_BOOST               0x7C

#define REG_TESTDAGC      0x6F
#define DAGC_NORMAL             0
#define DAGC_LB1                0x20
#define DAGC_LB0                0x30

#define REG_TESTAFC       0x71 //low beta AFC value


extern uint8_t RF69_TXbuffer[];
extern uint8_t RF69_RXbuffer[];

//extern uint8_t Channel;
//extern uint32_t Bitrate;

//extern uint8_t Txpower;
//extern uint8_t RF69_SyncValue[];

extern uint8_t NodeAddr;


void RF69_writereg (uint8_t reg, uint8_t v);
//read register
//reg - reg number, returns reg value
uint8_t RF69_readreg (uint8_t reg);

//initial procedure
extern void RF69_HWreset (void);
extern void RF69_init(void);
extern uint8_t RF69_getversion(void);

//set global parameters: bitrate, modulation
extern void RF69_setmodulation (uint8_t m);
extern void RF69_setdeviation(uint32_t d);
void RF69_setbitrate(uint32_t br);
//RC osc. calibration - check and perform if needed
extern void RF69_startRCcal(void);
extern uint8_t RF69_checkRCcal(void);
//listen mode settings
extern void RF69_setListenMode(uint8_t m1, uint8_t m2, uint8_t m3);
//batt. management settings

//TX parameters settings: PA select, PA ramp, PAbooster, current trimming
extern void RF69_setpower(uint8_t pwr); //TODO
extern void RF69_setPAramp(uint8_t p);

//RX parameters: BW, DCC freq., AFC, OOK, RSSI, LNA, DAGC etc.
extern void setAFClowbeta(uint8_t a);
extern void RF69_setLNAgain (uint8_t g);
extern uint8_t RF69_getLNAgain(void);
void RF69_setRXBW(uint8_t d, uint8_t w);
void RF69_setAFCBW(uint8_t d, uint8_t w);
void RF69_setAFC(uint8_t a);
extern int16_t RF69_getAFC(void);
extern int16_t RF69_getFEI(void); //TODO
extern void RF69_startRSSI(void);
extern uint8_t RF69_checkRSSI(void);
//IRQ and IO mapping
extern void RF69_setDIOmapping(uint8_t m1, uint8_t m2); 
extern uint16_t RF69_getIRQflags(void);
extern void RF69_setRSSItr (uint8_t t); //TODO

extern void RF69_setRXtimeouts(uint8_t t1, uint8_t t2);

extern int8_t RF69_tempmeas(void);
void RF69_calctemp(void);



//packet handler parameters
//***********************************************************************************************


//operative settings
//operating mode (sleep, standby, synth, rx, tx)

extern void RF69_setopmode (uint8_t mode);
//channel
extern void RF69_setchannel(uint8_t ch); //uint8_t ch
extern void RF69_setRXchannel(uint8_t ch);
//tx power
extern void RF69_setpower(uint8_t pwr);
//get RSSI
extern int8_t RF69_getRSSI(void); //propably maybe dependent on channel 
//get status (IRQ flags)
uint16_t RF69_getIRQflags(void);
extern void RF69_setRSSItr (uint8_t t); //TODO;
extern int8_t RF69_getRSSItr (void);
extern void RF69_setRXstartTO (uint8_t t); //TODO
extern void RF69_setRSSITO (uint8_t t); //TODO
extern void RF69_setPreambleSize (uint16_t s);
extern void RF69_setSyncConfig(uint8_t c);  //TODO
extern void RF69_setSyncValue (void); //8 bytes. TODO
extern void RF69_setPacketConfig1(uint8_t c);
extern void RF69_setPacketConfig2(uint8_t c);
extern void RF69_setPayLen (uint8_t l);
extern void RF69_setNodeAddr(uint8_t a);
extern void RF69_setBrAddr(uint8_t a);
extern void RF69_setAutoModes(uint8_t a);
//AES key
extern void RF69_setAESkey(void);

extern void RF69_setFIFOtr (uint8_t c, uint8_t tr);
extern void RF69_clearFIFO (void);

extern void RF69_sendpacket(uint8_t packet_size, uint8_t address);

extern void RF69_restartRX(void);


#endif
