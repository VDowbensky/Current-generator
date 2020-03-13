#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_

#include "stm8l15x.h"
#include "main.h"

//LED's
#define LEDPORT GPIOB
#define RED GPIO_Pin_1
#define GREEN GPIO_Pin_2

//Keys
#define KEYPORT GPIOC
//#define PRG_PIN GPIO_Pin_1 //pin 19 must be changed
#define K0 GPIO_Pin_5
#define K1 GPIO_Pin_6

//SPI
#define SPIPORT GPIOB
#define NSS_PIN GPIO_Pin_4
#define SCK_PIN GPIO_Pin_5
#define MOSI_PIN GPIO_Pin_6
#define MISO_PIN GPIO_Pin_7

//RF69 DIO's
#define RFPORT GPIOC
#define DIO0_PIN GPIO_Pin_0
#define DIO0_EXTI_PIN EXTI_Pin_0
#define DIO0_IT_PIN EXTI_IT_Pin0 //pin 18 

#define DIO1_PIN GPIO_Pin_1 //pin 19
#define DIO1_EXTI_PIN EXTI_Pin_1
#define DIO1_IT_PIN EXTI_IT_Pin1

#define RESET_PIN GPIO_Pin_4 //pin20

#define DE_PORT GPIOB
#define DE GPIO_Pin_0 //pin 10 on STM8L051F3



//UART
#define UARTPORT GPIOA
#define TXD_PIN GPIO_Pin_2
#define RXD_PIN GPIO_Pin_3

extern void initIO(void);

extern void Green_On (void);
extern void Green_Off (void);
extern void Red_On (void);
extern void Red_Off (void);




#endif

