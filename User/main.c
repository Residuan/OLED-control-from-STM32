#include "stm32f10x.h"
#include "oled.h"
#include "spi.h"
#include "systick.h"
#include "menu.h"
#include "key.h"
#include "wifi.h"
#include "calculator.h"

uint8_t flag;

int main(void)
{

	OLED_Init();
    //key_config();

    //led_init();

    //ESP8266_Config();
    Usart1_Config();
    
    //function_test(0);
    //menu_main();
    //printf("hellow world!\n");

    //ESP8266_start();
    //ESP8266_Get();

    GetAllNumData();



    while (1)
    {
        //Usart_SendString(USART3, Data_Buff);

        /*printf("test1!\n");
        Delay_ms(1000);
        printf("test2!\n");
        Delay_ms(1000);*/
        //function_ctrl();
        //Menu_key_set();

        //OLED_ShowTime();

        /*if (strUSART_Fram_Record.InfBit.FramFinishFlag == 1) //如果接收到了串口调试助手的数据
        {
            strUSART_Fram_Record.Data_RX_BUF[strUSART_Fram_Record.InfBit.FramLength] = '\0';
            Usart_SendString(USART3, strUSART_Fram_Record.Data_RX_BUF); //数据从串口调试助手转发到ESP8266
            strUSART_Fram_Record.InfBit.FramLength = 0;                            //接收数据长度置零
            strUSART_Fram_Record.InfBit.FramFinishFlag = 0;                        //接收标志置零
        }
        if (strEsp8266_Fram_Record.InfBit.FramFinishFlag) //如果接收到了ESP8266的数据
        {
            strEsp8266_Fram_Record.Data_RX_BUF[strEsp8266_Fram_Record.InfBit.FramLength] = '\0';
            Usart_SendString(USART1, strEsp8266_Fram_Record.Data_RX_BUF); //数据从ESP8266转发到串口调试助手
            strEsp8266_Fram_Record.InfBit.FramLength = 0;                       //接收数据长度置零
            strEsp8266_Fram_Record.InfBit.FramFinishFlag = 0;                   //接收标志置零
        }*/
    }
    
}




