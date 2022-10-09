#include "systick.h"

void Delay_ms(u32 ms)
{
    u32 i;
    SysTick_Config(72000);
    for(i = 0; i < ms; i++)
    {
        while(!((SysTick ->CTRL)&(1<<16)));
    }
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}


