#ifndef _SPI_H
#define _SPI_H

#include "stm32f10x.h"


void SPI_Config(void);
u8 SPI_WriteByte(SPI_TypeDef* SPIx, u8 Byte);






#endif

