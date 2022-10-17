#ifndef _WIFI_H
#define _WIFI_H

#include "stm32f10x.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "systick.h"
#include "control.h"

#define ESP8266_EN_ENABLE() GPIO_SetBits(GPIOG, GPIO_Pin_13)
#define ESP8266_EN_DISABLE() GPIO_ResetBits(GPIOG, GPIO_Pin_13)

#define ESP8266_RST_ENABLE() GPIO_SetBits(GPIOG, GPIO_Pin_14)
#define ESP8266_RST_DISABLE() GPIO_ResetBits(GPIOG, GPIO_Pin_14)

#define     macESP8266_Usart( fmt, ... )           USART_printf ( USART3, fmt, ##__VA_ARGS__ ) 
#define     macPC_Usart( fmt, ... )                printf ( fmt, ##__VA_ARGS__ )

extern volatile uint8_t ucTcpClosedFlag;

#if defined(__CC_ARM)
#pragma anon_unions
#endif

#define RX_BUF_MAX_LEN 1024 //最大接收缓存字节数

extern struct STRUCT_USARTx_Fram //串口数据帧的处理结构体
{
  char Data_RX_BUF[RX_BUF_MAX_LEN];

  union
  {
    __IO u16 InfAll;
    struct
    {
      __IO u16 FramLength : 15;    // 14:0
      __IO u16 FramFinishFlag : 1; // 15
    } InfBit;
  };

} strEsp8266_Fram_Record;

extern struct STRUCT_USARTx_Fram strUSART_Fram_Record;

void led_init(void);
void ESP8266_Config(void);
void Usart1_Config(void);
void ESP8266_USART_NVIC_Config(void);
void USART1_NVIC_Config(void);
void Usart_SendString(USART_TypeDef *pUSARTx, char *str);
void Usart_SendByte(USART_TypeDef *pUSARTx, uint8_t ch);
void ESP8266_start(void);
void ESP8266_Test(void);
bool ESP8266_Cmd(char *cmd, char *reply1, char *reply2, u32 waittime);
bool ESP8266_JoinAP ( char * pSSID, char * pPassWord );
void ESP8266_Get(void);
void ESP_SendString(const char* str);




#endif
