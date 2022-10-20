#include "stm32f10x.h"
#include "oled.h"
#include "spi.h"
#include "systick.h"
#include "menu.h"
#include "key.h"
#include "wifi.h"
#include "calculator.h"
#include <stdlib.h>
#include <math.h>

void GetAllNumData(void);

uint8_t flag;
char extern getnum[50];
uint16_t g;

int main(void)
{

    OLED_Init();
    // key_config();

    // led_init();

    // ESP8266_Config();
    Usart1_Config();

    // function_test(0);
    // menu_main();
    // printf("hellow world!\n");

    // ESP8266_start();
    // ESP8266_Get();

    while (1)
    {
        // Usart_SendString(USART3, Data_Buff);

        /*printf("test1!\n");
        Delay_ms(1000);
        printf("test2!\n");
        Delay_ms(1000);*/
        // function_ctrl();
        // Menu_key_set();

        // OLED_ShowTime();

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

        GetAllNumData();
        // printf("�ѻ�����ݣ�����Ϊ%s\n", getnum);
        Delay_ms(1000);
    }
}

void GetAllNumData(void)
{
    uint8_t i, j, k, l, z, g, x, o, m = 0, n = 0, p = 0, wei = 0;
    char sym[10], get = ' ';
    uint16_t out[20];
    uint8_t fanxiang[20];
    uint32_t firstout = 0;
    uint32_t allout[10];
    uint32_t output;

    for (g = 0; g < strlen(getnum); g++)
    {
        if (getnum[g] != '=')
        {
            printf("�ѻ�����ݣ�����Ϊ%s\n", getnum);
        }
        else
        {
            printf("�ѻ���������ݣ�����Ϊ%s\n���ڽ��м���\n", getnum);
            for (z = 0; z < strlen(getnum); z++)
            {
                if (z != 0)
                {
                    // wei += 1;
                    get = ' ';
                    z--;
                }
                for (i = z; (get != '+') && (get != '-') && (get != '*') && (get != '/') && (get != '='); i++) //ȡ��һ������ǰ���ַ�����ת��Ϊ����
                {

                    get = getnum[i];
                    out[m] = get - 48;
                    // printf("%d\n", out);

                    z++;
                    m++;
                }
                sym[p++] = get;
                wei = m - 1;
                // printf("λ��%d\n", wei);
                // jisuan(i, out);
                k = wei;
                for (j = 0; j <= wei; j++) //����д�����鷽����м���
                {
                    fanxiang[j] = out[k - 1];
                    k--;
                    // printf("�������%d\n", fanxiang[j]);
                }

                for (l = 0; l < wei; l++) //����������
                {
                    firstout += fanxiang[l] * pow(10, l);
                }
                // printf("�������1Ϊ%d\n", firstout);
                allout[n++] = firstout;
                allout[n++] = get;
                firstout = 0;
                m = 0;
                for (x = 0; x < 20; x++)
                {
                    fanxiang[x] = 0;
                    out[x] = 0;
                }
                // printf("�������Ϊ%d\n", allout[0]);
                // printf("�������Ϊ%d\n", allout[1]);
            }



            for (o = 0; o < strlen(sym); o++)
            {
                switch (sym[o])
                {
                case '*':
                    output = allout[o] * allout[o + 1];
                    o += 2;
                    break;
                case '/':
                    output[o - 1] = allout[o] / allout[o + 1];
                    break;
                default:
                    output[o] = allout[o];
                }

                for (o = 0; o < strlen(sym); o++)
                {
                    switch (sym[o])
                    {
                    case '+':
                        output[o - 1] = allout[o] + allout[o + 1];
                        break;
                    case '-':
                        output[o - 1] = allout[o] - allout[o + 1];
                        break;
                    default:
                        break;
                    }
                }
            }

            printf("������Ϊ��%d\n", output[1]);
        }
    }
}
