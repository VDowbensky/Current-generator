#ifndef _USER_SETTINGS_H_
#define _USER_SETTINGS_H_



//for autotest
#define PACKET_COUNT 50000
//#define PACKET_COUNT 50000

//not subject to operative change
//frequency band
#define F_BASE 868000000L
#define F_STEP 25000L //channel step

#define F_OFFSET -9000
#define F_TSLOPE -170 // Hz/C

#define TCAL 25
#define T_INIT -115

#define PREAMBLEMSB 0x00
#define PREAMBLELSB 40
#define MAX_PACKET_LEN           66
#define RFM69_BUFFER_SIZE        66


//propably optimal settings
//DCC set to 7 always
//BR = 9600, Fdev = 20000, gauss off, RXBW = 31250. AFCBW = 41667
//BR = 38400 FDEV = 40000, gauss off, RXBW = 62500. AFCBW = 83333
//deviation under 20 kHz needs AFC or exact frequency setting.

//subjects to operative change - must be stored in EEPROM
//working channel
#define WORK_CHANNEL 4 //868.100; to be parametrized
//modulation setting
//TX power
#define WORK_PA_SETTING			(TXPA1) 
//#define WORK_PA_SETTING			(TXPA0) //for test only.
//#define WORK_TXPOWER 27 //to be parametrized
//#define WORK_TXPOWER 18 //0 dbm

#define WORK_PA_RAMP PA_RAMP_500 //not subject to change but must found optimal value

//****************************************
//parameters for 9600 bps according to Freescale's AN4983. Uncomment following block if BR = 9600 and comment others
/*
#define WORK_BITRATE 9600 //to be parametrized
//deviation
#define WORK_DEVIATION 5000
//#define WORK_MOD_SETTING		(DATA_MODE_PACKET | MOD_TYPE_FSK | MOD_SHAPING_NONE) //to be parametrized (gauss filtering)
#define WORK_MOD_SETTING		(DATA_MODE_PACKET | MOD_TYPE_FSK | MOD_SHAPING_G10) //to be parametrized
//#define WORK_MOD_SETTING		(DATA_MODE_PACKET | MOD_TYPE_FSK | MOD_SHAPING_G05) //to be parametrized
//#define WORK_MOD_SETTING		(DATA_MODE_PACKET | MOD_TYPE_FSK | MOD_SHAPING_G03) //to be parametrized
#define WORK_TXPOWER 28 //10 dbm
//RX BW
#define WORK_RBW_DCC            DCC7 //to be parametrized
#define WORK_RBW_BW             BW_25K 
#define WORK_AFC_DCC            DCC7
#define WORK_AFC_BW             BW_25K 
#define WORK_AFCSETTING         (AFC_AUTOCLEAR | AFC_CLEAR)
#define WORK_LBOFFSET           0x01
#define WORK_RSSITR           230 //-115 dBm
#define WORK_TESTDAGC   DAGC_LB1 
#define WORK_LNASET (LNA_200 | G1)
//#define WORK_PACKETCONFIG1 (PACKET_LEN_VARIABLE | DC_FREE_MANCHESTER | CRC_ON | CRC_AUTOCLR_ON | ADDR_FILT_NONE)
#define WORK_PACKETCONFIG1 (PACKET_LEN_VARIABLE | DC_FREE_WHITENING | CRC_ON | CRC_AUTOCLR_ON | ADDR_FILT_NONE)
//#define WORK_PACKETCONFIG1 (PACKET_LEN_VARIABLE | DC_FREE_MANCHESTER | CRC_ON | CRC_AUTOCLR_ON | ADDR_FILT_ADDR_BC)
//#define WORK_PACKETCONFIG1 (PACKET_LEN_VARIABLE | DC_FREE_WHITENING | CRC_ON | CRC_AUTOCLR_ON | ADDR_FILT_ADDR_BC)
//#define WORK_PACKETCONFIG1 (PACKET_LEN_VARIABLE | DC_FREE_WHITENING | CRC_ON | CRC_AUTOCLR_OFF | ADDR_FILT_ADDR_BC)
*/
//*******end of 9600 bps block****************

//parameters for 19200 bps according to Freescale's AN4983. Uncomment following block if BR = 19200 and comment others
/*
#define WORK_BITRATE 19200 //to be parametrized
//deviation
#define WORK_DEVIATION 10000
//#define WORK_MOD_SETTING		(DATA_MODE_PACKET | MOD_TYPE_FSK | MOD_SHAPING_NONE) //to be parametrized (gauss filtering)
#define WORK_MOD_SETTING		(DATA_MODE_PACKET | MOD_TYPE_FSK | MOD_SHAPING_G10) //to be parametrized
//#define WORK_MOD_SETTING		(DATA_MODE_PACKET | MOD_TYPE_FSK | MOD_SHAPING_G05) //to be parametrized
//#define WORK_MOD_SETTING		(DATA_MODE_PACKET | MOD_TYPE_FSK | MOD_SHAPING_G03) //to be parametrized
#define WORK_TXPOWER 18 //10 dbm
//RX BW
#define WORK_RBW_DCC            DCC7 //to be parametrized
#define WORK_RBW_BW             BW_31K2 
#define WORK_AFC_DCC            DCC7
#define WORK_AFC_BW             BW_31K2
#define WORK_AFCSETTING         (AFC_AUTOCLEAR | AFC_CLEAR)
#define WORK_LBOFFSET           0x02
#define WORK_RSSITR           220 //-110 dBm
#define WORK_TESTDAGC   DAGC_LB1 
#define WORK_LNASET (LNA_200 | G1)
//#define WORK_PACKETCONFIG1 (PACKET_LEN_VARIABLE | DC_FREE_MANCHESTER | CRC_ON | CRC_AUTOCLR_ON | ADDR_FILT_NONE)
#define WORK_PACKETCONFIG1 (PACKET_LEN_VARIABLE | DC_FREE_WHITENING | CRC_ON | CRC_AUTOCLR_ON | ADDR_FILT_NONE)
//#define WORK_PACKETCONFIG1 (PACKET_LEN_VARIABLE | DC_FREE_MANCHESTER | CRC_ON | CRC_AUTOCLR_ON | ADDR_FILT_ADDR_BC)
//#define WORK_PACKETCONFIG1 (PACKET_LEN_VARIABLE | DC_FREE_WHITENING | CRC_ON | CRC_AUTOCLR_ON | ADDR_FILT_ADDR_BC)
//#define WORK_PACKETCONFIG1 (PACKET_LEN_VARIABLE | DC_FREE_WHITENING | CRC_ON | CRC_AUTOCLR_OFF | ADDR_FILT_ADDR_BC)
*/
//*******end of 19200 bps block****************

//parameters for 38400 bps (initial) Uncomment following block if BR = 38400 and comment others
/*
#define WORK_BITRATE 38400
//deviation
#define WORK_DEVIATION 40000
//#define WORK_MOD_SETTING		(DATA_MODE_PACKET | MOD_TYPE_FSK | MOD_SHAPING_NONE) //to be parametrized (gauss filtering)
#define WORK_MOD_SETTING		(DATA_MODE_PACKET | MOD_TYPE_FSK | MOD_SHAPING_G10) //to be parametrized
//#define WORK_MOD_SETTING		(DATA_MODE_PACKET | MOD_TYPE_FSK | MOD_SHAPING_G05) //to be parametrized
//#define WORK_MOD_SETTING		(DATA_MODE_PACKET | MOD_TYPE_FSK | MOD_SHAPING_G03) //to be parametrized
#define WORK_TXPOWER 18 //10 dbm
//RX BW
#define WORK_RBW_DCC            DCC7
#define WORK_RBW_BW             BW_83K3//to be parametrized
#define WORK_AFC_DCC            DCC7
#define WORK_AFC_BW             BW_83K3
#define WORK_AFCSETTING         (AFC_AUTOCLEAR | AFC_CLEAR)
#define WORK_LBOFFSET           0
#define WORK_RSSITR             200 //-100 dBm
//#define WORK_TESTDAGC   DAGC_NORMAL 
#define WORK_TESTDAGC   DAGC_LB0 
#define WORK_LNASET (LNA_200 | G1)
//#define WORK_PACKETCONFIG1 (PACKET_LEN_VARIABLE | DC_FREE_MANCHESTER | CRC_ON | CRC_AUTOCLR_ON | ADDR_FILT_NONE)
#define WORK_PACKETCONFIG1 (PACKET_LEN_VARIABLE | DC_FREE_WHITENING | CRC_ON | CRC_AUTOCLR_ON | ADDR_FILT_NONE)
//#define WORK_PACKETCONFIG1 (PACKET_LEN_VARIABLE | DC_FREE_MANCHESTER | CRC_ON | CRC_AUTOCLR_ON | ADDR_FILT_ADDR_BC)
//#define WORK_PACKETCONFIG1 (PACKET_LEN_VARIABLE | DC_FREE_WHITENING | CRC_ON | CRC_AUTOCLR_ON | ADDR_FILT_ADDR_BC)
//#define WORK_PACKETCONFIG1 (PACKET_LEN_VARIABLE | DC_FREE_WHITENING | CRC_ON | CRC_AUTOCLR_OFF | ADDR_FILT_ADDR_BC)
*/
//*******end of 38400 bps (initial) block****************

//parameters for 38400 bps according to Freescale's AN4983. Uncomment following block if BR = 38400 and comment others

#define WORK_BITRATE 38400
//deviation
#define WORK_DEVIATION 20000
//#define WORK_MOD_SETTING		(DATA_MODE_PACKET | MOD_TYPE_FSK | MOD_SHAPING_NONE) //to be parametrized (gauss filtering)
#define WORK_MOD_SETTING		(DATA_MODE_PACKET | MOD_TYPE_FSK | MOD_SHAPING_G10) //to be parametrized
//#define WORK_MOD_SETTING		(DATA_MODE_PACKET | MOD_TYPE_FSK | MOD_SHAPING_G05) //to be parametrized
//#define WORK_MOD_SETTING		(DATA_MODE_PACKET | MOD_TYPE_FSK | MOD_SHAPING_G03) //to be parametrized
#define WORK_TXPOWER 28 //10 dbm
//RX BW
#define WORK_RBW_DCC            DCC7
#define WORK_RBW_BW             BW_41K7 //to be parametrized
#define WORK_AFC_DCC            DCC7
#define WORK_AFC_BW             BW_41K7
#define WORK_AFCSETTING         (AFC_AUTOCLEAR | AFC_CLEAR)
#define WORK_LBOFFSET           0x00
#define WORK_RSSITR             220 //-110 dBm
#define WORK_TESTDAGC           DAGC_LB1 
//#define WORK_LNASET (LNA_200 | LNABOOST | G1)
#define WORK_LNASET (LNA_200 | G1)

//#define WORK_PACKETCONFIG1 (PACKET_LEN_VARIABLE | DC_FREE_MANCHESTER | CRC_ON | CRC_AUTOCLR_ON | ADDR_FILT_NONE)
#define WORK_PACKETCONFIG1 (PACKET_LEN_VARIABLE | DC_FREE_WHITENING | CRC_ON | CRC_AUTOCLR_ON | ADDR_FILT_NONE)
//#define WORK_PACKETCONFIG1 (PACKET_LEN_VARIABLE | DC_FREE_WHITENING | CRC_ON | CRC_AUTOCLR_OFF | ADDR_FILT_NONE)
//#define WORK_PACKETCONFIG1 (PACKET_LEN_VARIABLE | DC_FREE_MANCHESTER | CRC_ON | CRC_AUTOCLR_ON | ADDR_FILT_ADDR_BC)
//#define WORK_PACKETCONFIG1 (PACKET_LEN_VARIABLE | DC_FREE_WHITENING | CRC_ON | CRC_AUTOCLR_ON | ADDR_FILT_ADDR_BC)
//#define WORK_PACKETCONFIG1 (PACKET_LEN_VARIABLE | DC_FREE_WHITENING | CRC_ON | CRC_AUTOCLR_OFF | ADDR_FILT_ADDR_BC)

///*******end of 38400 bps block****************

//packet parameters
//sync value ("Senao" nostalgie :) )
#define WORK_SYNC1 0x23
#define WORK_SYNC2 0x6B
#define WORK_SYNC3 0xC9
#define WORK_SYNC4 0x6C
#define WORK_SYNC5 0x6B
#define WORK_SYNC6 0x23
#define WORK_SYNC7 0x6C
#define WORK_SYNC8 0xC9


#define WORK_NODEADDR   0x58
#define WORK_BRADDR     0xFF

#define SYNC_SIZE               3 //means 8
#define SYNC_TOL                0
#define PACKET_DELAY 2
#define WORK_PACKET_LEN 43

//test packet configuration
#define WORK_PREAMBLESIZE 32 //4 bytes

//timeouts settings
#define WORK_RXTO 0 
#define WORK_RSSITO 0
//#define WORK_RSSITO 64 //double packet length; maybe shorted

#define RF69TIMEOUT 10000 //1000 ms
//#define RF69TIMEOUT PACKET_DELAY*100

#define WORK_RXDELAY  0x0A //inter-packet RX delay

#define WORK_SYNC_CONFIG (SYNCON | FIFO_FILL_ADDR | (SYNC_SIZE << 3) | SYNC_TOL)

//#define WORK_PACKETCONFIG2      ((WORK_RXDELAY <<4) |  AUTORESTART_OFF | RESTARTRX | AES_OFF)
#define WORK_PACKETCONFIG2      ((WORK_RXDELAY <<4) |  AUTORESTART_ON | RESTARTRX | AES_OFF)
//#define WORK_PACKETCONFIG2      ((WORK_RXDELAY <<4) |  AUTORESTART_ON |  AES_OFF)
//#define RX_RESTART ((WORK_RXDELAY <<4) |  RESTARTRX |  AES_OFF)
#define WORK_FIFOTRESH          0xA0 //32 //default threshold - 0x8F

#define DIOM1_TX (DIO0_PKSENT_CRCOK | DIO1_FLEVEL | DIO2_FNE | DIO3_FFULL )
//#define DIOM1_RXWAIT (DIO0_PLLLOCK_RSSI | DIO1_PLLLOCK_TIMEOUT | DIO2_FNE | DIO3_FFULL )
#define DIOM1_RX (DIO0_TXREADY_PLREADY | DIO1_PLLLOCK_TIMEOUT | DIO2_FNE | DIO3_FFULL )
#define DIOM2_DEFAULT (DIO4_TXREADY_RSSI | DIO5_DATA | CLK_OFF)




#define COMMAS_COUNT 6 //for GPS parsing

#endif
