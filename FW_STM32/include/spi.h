#ifndef _RF69_INTERFACE_H_
#define _RF69_INTERFACE_H_

#include <stdint.h>
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"



#define NSSPORT	GPIOA
#define NSS_PIN GPIO_Pin_4

#define SPIPORT GPIOA
#define SCK_PIN GPIO_Pin_5
#define MOSI_PIN GPIO_Pin_7
#define MISO_PIN GPIO_Pin_6

#define SCK_PINSOURCE GPIO_PinSource5
#define MOSI_PINSOURCE GPIO_PinSource7
#define MISO_PINSOURCE GPIO_PinSource6


extern void initSPI(void);
extern void RF69_select(void);
extern void RF69_deselect(void);
extern uint8_t spi_transfer(uint8_t b);
extern void checkDIO0(void);

#endif

