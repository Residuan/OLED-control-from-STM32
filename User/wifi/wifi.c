#include "wifi.h"

volatile uint8_t ucTcpClosedFlag = 0;
struct  STRUCT_USARTx_Fram strEsp8266_Fram_Record = { 0 };
struct  STRUCT_USARTx_Fram strUSART_Fram_Record = { 0 };


char cStr [ 1500 ] = { 0 };

void led_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_SetBits(GPIOB, GPIO_Pin_0);
}

void ESP8266_start(void)
{
    ESP8266_RST_ENABLE();
    ESP8266_EN_DISABLE();
    Delay_ms(500);
    ESP8266_EN_ENABLE();
    Delay_ms(1000);
    ESP8266_Test();
}



void USART1_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;

    NVIC_Init(&NVIC_InitStructure);
}

void ESP8266_USART_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;

    NVIC_Init(&NVIC_InitStructure);
}

void Usart1_Config(void)
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    USART_DeInit(USART1);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_Init(GPIOA, &GPIO_InitStructure);  

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1, &USART_InitStructure);

    USART1_NVIC_Config();

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    //USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);

    USART_Cmd(USART1, ENABLE);

}

void ESP8266_Config(void)
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOG, ENABLE);
    USART_DeInit(USART3);

/*ESP8266使能口和复位口初始化*/   
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOG, &GPIO_InitStructure);

/*ESP8266串口IO初始化*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

/*ESP8266串口初始化*/
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART3, &USART_InitStructure);

    ESP8266_USART_NVIC_Config();

    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
    USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);

    USART_Cmd(USART3, ENABLE);
}

void ESP8266_Test(void)
{
    /*strEsp8266_Fram_Record.InfBit.FramLength = 0;
    Usart_SendString(USART3, "AT\r\n");
    Delay_ms(1000);
    strEsp8266_Fram_Record.Data_RX_BUF[strEsp8266_Fram_Record.InfBit.FramLength] = '\0';
    strEsp8266_Fram_Record.InfBit.FramLength = 0; //清除接收标志
    strEsp8266_Fram_Record.InfBit.FramFinishFlag = 0;
    if ((bool)strstr(strEsp8266_Fram_Record.Data_RX_BUF, "OK"))
    {

        printf("AT测试通过\n");
    }

    
    strEsp8266_Fram_Record.InfBit.FramLength = 0;
    Usart_SendString(USART3, "AT+CWJAP=\"Cynosural\",\"1234567890\"\r\n");
    Delay_ms(5000);

    strEsp8266_Fram_Record.Data_RX_BUF[strEsp8266_Fram_Record.InfBit.FramLength] = '\0';
    strEsp8266_Fram_Record.InfBit.FramLength = 0; //清除接收标志
    strEsp8266_Fram_Record.InfBit.FramFinishFlag = 0;
    if ((bool)strstr(strEsp8266_Fram_Record.Data_RX_BUF, "OK"))
    {
        printf("已连接wifi\n");
    }*/
    printf("正在测试AT指令");
    while(!ESP8266_Cmd("AT", "OK", NULL, 500));
    printf("测试成功,正常运行\n");
    Delay_ms(2000);

    printf("正在设置运行模式\n");
    while(!ESP8266_Cmd("AT+CWMODE=1", "OK", NULL, 500));
    printf("设置完成\n");
    Delay_ms(2000);

    printf("正在重启设备\n");
    while(!ESP8266_Cmd("AT+RST", "OK", NULL, 500));
    Delay_ms(4000);
    printf("重启完成\n");

    printf("正在设置连接模式\n");
    while(!ESP8266_Cmd("AT+CIPMUX=0", "OK", NULL, 500));
    printf("设置完成\n");
    Delay_ms(2000);

    printf("正在连接wifi\n");
    while(!ESP8266_JoinAP("Cynosural", "1234567890"));
    printf("已连接wifi\n");
    Delay_ms(2000);
    
    printf("ESP8266初始化完成\n");

}

void ESP8266_Get(void)
{
    printf("正在建立连接\n");
    while(!ESP8266_Cmd("AT+CIPSTART=\"TCP\",\"tianqiapi.com\",80", "OK", NULL, 500));
    printf("已建立连接\n");
/*
    printf("开启透传模式\n");
    while(!ESP8266_Cmd("AT+CIPMODE=1", "OK", NULL, 500));
    printf("已开启\n");

    printf("正在获取时间\n");
    while(!ESP8266_Cmd("AT+CIPSEND=1", "OK", NULL, 500));
    ESP_SendString("GET /time15.asp HTTP/1.1\r\nHost:www.beijing-time.org\r\n");*/

}

bool ESP8266_JoinAP ( char * pSSID, char * pPassWord )
{
	char cCmd [120];

	sprintf ( cCmd, "AT+CWJAP=\"%s\",\"%s\"", pSSID, pPassWord );
	
	return ESP8266_Cmd ( cCmd, "OK", NULL, 5000 );
	
}

bool ESP8266_Cmd(char *cmd, char *reply1, char *reply2, u32 waittime)
{
    strEsp8266_Fram_Record.InfBit.FramLength = 0; //从新开始接收新的数据包

    macESP8266_Usart("%s\r\n", cmd);

    if ((reply1 == 0) && (reply2 == 0)) //不需要接收数据
        return true;

    Delay_ms(waittime); //延时

    strEsp8266_Fram_Record.Data_RX_BUF[strEsp8266_Fram_Record.InfBit.FramLength] = '\0';

    macPC_Usart("%s", strEsp8266_Fram_Record.Data_RX_BUF);
    strEsp8266_Fram_Record.InfBit.FramLength = 0; //清除接收标志
    strEsp8266_Fram_Record.InfBit.FramFinishFlag = 0;
    if ((reply1 != 0) && (reply2 != 0))
        return ((bool)strstr(strEsp8266_Fram_Record.Data_RX_BUF, reply1) ||
                (bool)strstr(strEsp8266_Fram_Record.Data_RX_BUF, reply2));

    else if (reply1 != 0)
        return ((bool)strstr(strEsp8266_Fram_Record.Data_RX_BUF, reply1));

    else
        return ((bool)strstr(strEsp8266_Fram_Record.Data_RX_BUF, reply2));
}

int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到串口 */
		USART_SendData(USART1, (uint8_t) ch);
		
		/* 等待发送完毕 */
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

///重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
int fgetc(FILE *f)
{
		/* 等待串口输入数据 */
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USART1);
}

void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* 发送一个字节数据到USART */
	USART_SendData(pUSARTx,ch);
		
	/* 等待发送数据寄存器为空 */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}


void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
  do 
  {
      Usart_SendByte( pUSARTx, *(str + k) );
      k++;
  } while(*(str + k)!='\0');
  
  /* 等待发送完成 */
  while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET)
  {}
}

void ESP_SendString(const char* str)
{
	uint8_t k = 0;
	do
	{
		Usart_SendByte(USART3,str[k]);
		while(USART_GetFlagStatus(USART3,USART_FLAG_TXE) == RESET);
		k++;
	}while(*(str+k)!='\0');
	while(USART_GetFlagStatus(USART3,USART_FLAG_TC) == RESET);
}
