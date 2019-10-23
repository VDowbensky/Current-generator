#ifndef _MYSETTINGS_H_
#define _MYSETTINGS_H_

#include "rfm69.h"

#define BAUDRATE 115200UL

//test packet configuration
#define TEST_PREAMBLESIZE 16
#define TEST_SYNCCONFIG
#define TEST_SYNC_CONFIG (SYNCON | FIFO_FILL_ADDR | (SYNC_SIZE << 3) | SYNC_TOL)
#define TEST_PACKETCONFIG1 (PACKET_LEN_FIXED | DC_FREE_NONE | CRC_ON | CRC_AUTOCLR_ON | ADDR_FILT_ADDR_BC)
#define TEST_PACKETCONFIG2      (0x40 |  AUTORESTART_OFF | AES_OFF)
#define TEST_PAYLOADLENGTH      0x20 //32 bytes
#define TEST_NODEADDR           1
#define TEST_BRADDR             0xFF
#define TEST_AUTOMODES          0

#define TEST_RBW_DCC            DCC2
#define TEST_RBW_BW             BW_83K3
#define TEST_AFC_DCC            DCC2
#define TEST_AFC_BW             BW_125K


#endif
