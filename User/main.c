#include "stm32f10x.h"
#include "oled.h"
#include "spi.h"
#include "systick.h"
#include "menu.h"
#include "key.h"
#include "wifi.h"



int main(void)
{
	OLED_Init();
    key_config();

    ESP8266_Config();
    Usart1_Config();
    
    function_test(0);
    //menu_main();
    printf("hellow world!\n");
    

    

    while (1)
    {
        printf("test1!\n");
        Delay_ms(1000);
        printf("test2!\n");
        Delay_ms(1000);
        //function_ctrl();
        //Menu_key_set();
        //OLED_ShowTime();
        
    }
    
}




