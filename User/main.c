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

        /*if (strUSART_Fram_Record.InfBit.FramFinishFlag == 1) //������յ��˴��ڵ������ֵ�����
        {
            strUSART_Fram_Record.Data_RX_BUF[strUSART_Fram_Record.InfBit.FramLength] = '\0';
            Usart_SendString(USART3, strUSART_Fram_Record.Data_RX_BUF); //���ݴӴ��ڵ�������ת����ESP8266
            strUSART_Fram_Record.InfBit.FramLength = 0;                            //�������ݳ�������
            strUSART_Fram_Record.InfBit.FramFinishFlag = 0;                        //���ձ�־����
        }
        if (strEsp8266_Fram_Record.InfBit.FramFinishFlag) //������յ���ESP8266������
        {
            strEsp8266_Fram_Record.Data_RX_BUF[strEsp8266_Fram_Record.InfBit.FramLength] = '\0';
            Usart_SendString(USART1, strEsp8266_Fram_Record.Data_RX_BUF); //���ݴ�ESP8266ת�������ڵ�������
            strEsp8266_Fram_Record.InfBit.FramLength = 0;                       //�������ݳ�������
            strEsp8266_Fram_Record.InfBit.FramFinishFlag = 0;                   //���ձ�־����
        }*/
    }
    
}




