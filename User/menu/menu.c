#include "menu.h"

u8 Get_key_next, Get_key_enter;
uint8_t  func_index = 0;

void (*current_operation_index)();

void menu_main(void)
{
    //OLED_ShowStr(32, 0, "Function");
    OLED_DrawBMP(0, 0, 128, 8, function1);
}
/*
void function_ctrl(void)
{
    if((GPIOA->IDR & GPIO_Pin_0) != RESET)
    {
        OLED_DrawBMP(0, 0, 128, 8, function2);
    }
    else 
    {
        OLED_DrawBMP(0, 0, 128, 8, function1);
    }
}*/



Menu table[6]=
{
    {0,1,3,(*fun0)},
    {1,2,4,(*fun1)},
    {2,0,5,(*fun2)},

    {3,0,0,(*fun3)},
};

void Menu_key_set(void)
{
  Get_key_next = Key1_Condition();
  Get_key_enter = Key2_Condition();

  if(Get_key_next == 1)
  {   
    func_index = table[func_index].next;
    OLED_ALL_Cram(0x00);
  }
  if(Get_key_enter == 1)
  {
    func_index = table[func_index].enter;
    OLED_ALL_Cram(0x00);
  }

  current_operation_index = table[func_index].current_operation;
  (*current_operation_index)();
}

void fun0(void)
{
    OLED_DrawBMP(0, 0, 128, 8, function2);

}
void fun1(void)
{
    OLED_DrawBMP(0, 0, 128, 8, function1);
}
void fun2(void)
{
    OLED_ShowStr(48, 0, "Fun2");
}
void fun3(void)
{
    
}
