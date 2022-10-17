#include "oled.h"




void OLED_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_SetBits(GPIOB, GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12);
}


void OLED_Init(void)
{
    SPI_Config();
    OLED_GPIO_Config();
    Delay_ms(200);
    OLED_Reset();
 
    OLED_WR_Byte(0xAE, OLED_CMD);
    OLED_WR_Byte(0x00, OLED_CMD);
    OLED_WR_Byte(0x10, OLED_CMD);
    OLED_WR_Byte(0x40, OLED_CMD);
    OLED_WR_Byte(0xB0, OLED_CMD);
    OLED_WR_Byte(0x81, OLED_CMD);
    OLED_WR_Byte(0xFF, OLED_CMD);
    OLED_WR_Byte(0xA1, OLED_CMD);
    OLED_WR_Byte(0xA6, OLED_CMD);
    OLED_WR_Byte(0xA8, OLED_CMD);
    OLED_WR_Byte(0x3F, OLED_CMD);
    OLED_WR_Byte(0xC8, OLED_CMD);
    OLED_WR_Byte(0xD3, OLED_CMD);
    OLED_WR_Byte(0x00, OLED_CMD);
    OLED_WR_Byte(0xD5, OLED_CMD);
    OLED_WR_Byte(0x80, OLED_CMD);
    OLED_WR_Byte(0xD9, OLED_CMD);
    OLED_WR_Byte(0XF1, OLED_CMD);
    OLED_WR_Byte(0xDA, OLED_CMD);
    OLED_WR_Byte(0x12, OLED_CMD);
    OLED_WR_Byte(0xDB, OLED_CMD);
    OLED_WR_Byte(0x30, OLED_CMD);
    OLED_WR_Byte(0x8D, OLED_CMD);
    OLED_WR_Byte(0x14, OLED_CMD);
    OLED_WR_Byte(0xAF, OLED_CMD);
    OLED_ALL_Cram(0x00);
}

 
void SetPos(unsigned char x,unsigned char y)  //设置起点坐标
{
    OLED_WR_Byte(0xb0+y, OLED_CMD);
	OLED_WR_Byte((x&0xf0)>>4|0x10, OLED_CMD); //取高位
	OLED_WR_Byte((x&0x0f)|0x01, OLED_CMD);    //取低位
}

void OLED_Reset(void)
{
    OLED_RST_Set();
    Delay_ms(100);
    OLED_RST_Clr();
    Delay_ms(100);
    OLED_RST_Set();
}


void OLED_WR_Byte(unsigned dat, unsigned cmd)
{
    if (cmd)
    {
        OLED_DC_Set();
    }
    else
    {
        OLED_DC_Clr();
    }
    OLED_CS_Clr();
    SPI_WriteByte(SPI2, dat);
    OLED_CS_Set();
}


void OLED_ALL_Cram(u8 da)
{
    int i = 0, j = 0;
    for (i = 0; i < 8; i++)
    {
		OLED_WR_Byte (0xb0+i, OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (0x00, OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (0x10, OLED_CMD);      //设置显示位置—列高地址 
        for (j = 0; j < 128; j++)
        {
            OLED_WR_Byte(da, OLED_DATA);
        }
    }
 
}


void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[])
{
	unsigned int j=0;
	unsigned char x,y;
	
	if(y1%8 == 0)
		y = y1/8;
	else
		y = y1/8 +1;
	for(y=y0;y<y1;y++)
	{
		SetPos(x0,y);
        for(x=x0;x<x1;x++)
		{	
			OLED_WR_Byte(BMP[j++], OLED_DATA);
		}		
	}
}

void OLED_DrawString(unsigned char x0,unsigned char y0,unsigned char string[])
{
    unsigned int j=0;
	unsigned char x,y;
    unsigned char xend,yend;

    yend = y0 + 2;
	for(y=y0;y<yend;y++)
	{
        xend = x0+8;
		SetPos(x0,y);
        for(x=x0;x<xend;x++)
		{	
			OLED_WR_Byte(string[j++], OLED_DATA);
		}		
	}
}


void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[])
{
    unsigned char c = 0, i = 0, j = 0;

    while (ch[j] != '\0')
    {
        c = ch[j] - 32;
        if (x > 120) // 8*16  120越界 没懂
        {
            x = 0;
            y+=2; //回到第一行，下一列
        }
        SetPos(x, y);
        for (i = 0; i < 8; i++) //把16分成两个部分， 屏幕是分成了8页 上下显示（目前还不太懂）
            OLED_WR_Byte(bit16[c * 16 + i], OLED_DATA);

        SetPos(x, y + 1);
        
        for (i = 0; i < 8; i++)
            OLED_WR_Byte(bit16[c * 16 + 8 + i], OLED_DATA);
        x += 8; //转到下一个字符
        j++;
    }
}

void OLED_Show32Num(unsigned char x0, unsigned char y0, unsigned char num)
{
    //unsigned int j=0;
	unsigned char x,y;
    unsigned char xend,yend;
    unsigned int shownum = 0, we = 64;

    yend = y0 + 4;
    shownum = num * we; 
	for(y=y0;y<yend;y++)
	{
        xend = x0+16;
		SetPos(x0,y);
        for(x=x0;x<xend;x++)
		{	
			OLED_WR_Byte(num32[shownum++], OLED_DATA);
		}		
	}
}


void OLED_ShowTime(void)
{
    unsigned char second1 = 0, second2 = 0;
    unsigned char minute1 = 0, minute2 = 0;
    unsigned char hour1 = 0, hour2 = 0;

    

    OLED_Show32Num(10, 2, hour1);
    OLED_Show32Num(26, 2, hour2);

    OLED_ShowStr(42, 3, ":");

    OLED_Show32Num(50, 2, minute1);
    OLED_Show32Num(66, 2, minute2);

    OLED_ShowStr(82, 3, ":");

    OLED_Show32Num(90, 2, second1);
    OLED_Show32Num(106, 2, second2);
}



void function_test(unsigned char en)
{
    if(en)
    {
        //OLED_DrawBMP(0, 0, 96, 8, BMP);//图片测试
        OLED_ALL_Cram(0xff);
        //OLED_DrawString(0, 1, capitalletter26[0]);
        //OLED_ShowStr(0, 0, "ABCDEFGHIJKLMNOPRQSTUVWXYZ!");
        //OLED_Show32Num(0, 0, 4);
    }
    else return;
}





