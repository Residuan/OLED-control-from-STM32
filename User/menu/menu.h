#ifndef _MENU_H
#define _MENU_H

#include "stm32f10x.h"
#include "oled.h"
#include "library.h"
#include "systick.h"
#include "key.h"


typedef struct
{
    unsigned char now;
    unsigned char next;
    unsigned char enter;
     void(*current_operation)(void);
    /* data */
}Menu;

void menu_main(void);
void function_ctrl(void);
void Menu_key_set(void);
void fun0(void);
void fun1(void);
void fun2(void);
void fun3(void);











#endif
