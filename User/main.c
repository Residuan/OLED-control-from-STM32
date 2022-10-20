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

        GetAllNumData();
        // printf("已获得数据，数据为%s\n", getnum);
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
            printf("已获得数据，数据为%s\n", getnum);
        }
        else
        {
            printf("已获得所有数据，数据为%s\n正在进行计算\n", getnum);
            for (z = 0; z < strlen(getnum); z++)
            {
                if (z != 0)
                {
                    // wei += 1;
                    get = ' ';
                    z--;
                }
                for (i = z; (get != '+') && (get != '-') && (get != '*') && (get != '/') && (get != '='); i++) //取第一个符号前的字符串并转化为数字
                {

                    get = getnum[i];
                    out[m] = get - 48;
                    // printf("%d\n", out);

                    z++;
                    m++;
                }
                sym[p++] = get;
                wei = m - 1;
                // printf("位数%d\n", wei);
                // jisuan(i, out);
                k = wei;
                for (j = 0; j <= wei; j++) //反向写入数组方便进行计算
                {
                    fanxiang[j] = out[k - 1];
                    k--;
                    // printf("反向输出%d\n", fanxiang[j]);
                }

                for (l = 0; l < wei; l++) //最终输出结果
                {
                    firstout += fanxiang[l] * pow(10, l);
                }
                // printf("最终输出1为%d\n", firstout);
                allout[n++] = firstout;
                allout[n++] = get;
                firstout = 0;
                m = 0;
                for (x = 0; x < 20; x++)
                {
                    fanxiang[x] = 0;
                    out[x] = 0;
                }
                // printf("最终输出为%d\n", allout[0]);
                // printf("最终输出为%d\n", allout[1]);
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

            printf("最后输出为：%d\n", output[1]);
        }
    }
}
