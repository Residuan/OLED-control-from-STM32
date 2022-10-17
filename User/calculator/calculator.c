#include "calculator.h"

uint8_t *GetNum[] = {"1","2","3","+"};



uint8_t *GetAllNumData(void)
{
    uint8_t i = 0;
    while(i++)
    {
        if ((GetNum[i] == "+") || (GetNum[i] == "-") || (GetNum[i] == "*") || (GetNum[i] == "/"))
        {
            break;
        }
        *GetNum[i] = USART_ReceiveData(USART1);
        
    }
    printf("%d", &GetNum);
    return *GetNum;
}

void calculate(void)
{


}



