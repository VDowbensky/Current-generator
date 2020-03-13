#include "spi_interface.h"

void initSPI(void);
uint8_t spi_transfer(uint8_t b);


void initSPI(void)
  {
    SPI_DeInit(SPI1);
    //SPI_Init(SPI1, SPI_FirstBit_MSB, SPI_BaudRatePrescaler_16, SPI_Mode_Master, SPI_CPOL_Low, SPI_CPHA_1Edge, SPI_Direction_Tx, SPI_NSS_Soft, 0);
    SPI_Init(SPI1, SPI_FirstBit_MSB, SPI_BaudRatePrescaler_16, SPI_Mode_Master, SPI_CPOL_Low, SPI_CPHA_1Edge, SPI_Direction_2Lines_FullDuplex, SPI_NSS_Soft, 0);
     
    SPI_Cmd(SPI1, ENABLE);
    //interrupt
    //SPI_ITConfig(SPI1, SPI_IT_TXE | SPI_IT_RXNE, ENABLE);
    
  }

uint8_t spi_transfer(uint8_t b)
{
  uint8_t data;
  while (SPI_GetFlagStatus(SPI1, SPI_FLAG_TXE) == RESET);
  SPI_SendData(SPI1, b);
  while (SPI_GetFlagStatus(SPI1, SPI_FLAG_RXNE) == RESET);
  data = SPI_ReceiveData(SPI1);
  while (SPI_GetFlagStatus(SPI1, SPI_FLAG_BSY) == SET);
  return data;
}