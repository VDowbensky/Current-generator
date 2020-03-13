#ifndef _SPI_INTERFACE_H_
#define _SPI_INTERFACE_H_

#include "stm8l15x.h"

extern uint8_t spi_transfer(uint8_t b);
extern void initSPI(void);

#endif