#include "key.h"

void key_config(void)//A0, C13
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

u8 Key1_Condition(void)
{
    if((GPIOA->IDR & GPIO_Pin_0) != RESET)
    {
        Delay_ms(10);
        if((GPIOA->IDR & GPIO_Pin_0) != RESET)
        {
            while((GPIOA->IDR & GPIO_Pin_0) != RESET);
            return 1;
        }
    }
    return 0;
}

u8 Key2_Condition(void)
{
    if((GPIOC->IDR & GPIO_Pin_13) != RESET)
    {
        Delay_ms(10);
        if((GPIOC->IDR & GPIO_Pin_13) != RESET)
        {
            while((GPIOA->IDR & GPIO_Pin_13) != RESET);
            return 1;
        }
    }
    return 0;
}





