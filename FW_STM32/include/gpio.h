#ifndef _USER_INTERFACE_H_
#define _USER_INTERFACE_H_
#include <stdint.h>
#include "stm32f10x_gpio.h"
#include "main.h"


#define KEYDELAY 50
#define KEY_LEFT 1
#define KEY_RIGHT 2
#define KEY_BOTH 3

//hardware

#define UARTPORT GPIOA
#define TXD_PIN GPIO_Pin_2
#define RXD_PIN GPIO_Pin_3
#define TXD_PINSOURCE GPIO_PinSource2
#define RXD_PINSOURCE GPIO_PinSource3

#define LEDPORT GPIOB
#define RED GPIO_Pin_15
#define GREEN GPIO_Pin_15
#define BLUE GPIO_Pin_15


#define KEYPORT GPIOB
#define K1PORT GPIOB
//#define PRG_PIN GPIO_Pin_1
#define K0 GPIO_Pin_12 //IR_IN
#define K1 GPIO_Pin_7 //


#define RFPORT GPIOB
#define DIO0_PIN GPIO_Pin_0
#define DIO0_EXTI_PORTSOURCE GPIO_PortSourceGPIOB
#define DIO0_EXTI_PINSOURCE GPIO_PinSource0
#define DIO0_EXTI_LINE EXTI_Line0

#define DIO0_IRQn EXTI0_IRQn
#define DIO0_IRQhandler EXTI0_IRQHandler

#define RESET_PIN GPIO_Pin_13

extern void initIO(void);
extern void Green_On (void);
extern void Green_Off (void);
extern void Red_On (void);
extern void Red_Off (void);

extern void DIO0_enableIRQ(void);
extern void DIO0_disableIRQ(void);



#endif


