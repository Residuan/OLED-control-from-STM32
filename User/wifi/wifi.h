#ifndef _WIFI_H
#define _WIFI_H

#include "stm32f10x.h"
#include <stdio.h>

#define ESP8266_EN_ENABLE() GPIO_SetBits(GPIOG, GPIO_Pin_13)
#define ESP8266_EN_DISABLE() GPIO_ResetBits(GPIOG, GPIO_Pin_13)

#define ESP8266_RST_ENABLE() GPIO_SetBits(GPIOG, GPIO_Pin_14)
#define ESP8266_RST_DISABLE() GPIO_ResetBits(GPIOG, GPIO_Pin_14)


void ESP8266_Config(void);
void Usart1_Config(void);
void ESP8266_USART_NVIC_Config(void);
void USART1_NVIC_Config(void);











#endif
