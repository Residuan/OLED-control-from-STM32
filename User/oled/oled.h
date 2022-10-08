#ifndef _OLED_H
#define _OLED_H

#include "stm32f10x.h"
#include "spi.h"
#include "systick.h"
#include "library.h"

#define OLED_CMD 0
#define OLED_DATA 1

#define OLED_CS   GPIO_Pin_11   
#define OLED_DC   GPIO_Pin_10   
#define OLED_RST  GPIO_Pin_12   


#define OLED_CS_Clr()  GPIO_ResetBits(GPIOB,OLED_CS)
#define OLED_CS_Set()  GPIO_SetBits(GPIOB,OLED_CS)

#define OLED_DC_Clr()  GPIO_ResetBits(GPIOB,OLED_DC)
#define OLED_DC_Set()  GPIO_SetBits(GPIOB,OLED_DC)
 					   
#define OLED_RST_Clr()  GPIO_ResetBits(GPIOB,OLED_RST)
#define OLED_RST_Set()  GPIO_SetBits(GPIOB,OLED_RST)

void OLED_GPIO_Config(void);
void OLED_Reset(void);
void OLED_Init(void);
void OLED_WR_Byte(unsigned dat, unsigned cmd);
void OLED_ALL_Cram(u8 da);
void SetPos(unsigned char x,unsigned char y);
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);
void OLED_DrawString(unsigned char x0,unsigned char y0,unsigned char string[]);
void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[]);
void function_test(unsigned char en);
void OLED_Show32Num(unsigned char x, unsigned char y, unsigned char num);



#endif

