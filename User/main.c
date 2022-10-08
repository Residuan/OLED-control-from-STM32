#include "stm32f10x.h"
#include "oled.h"
#include "spi.h"
#include "systick.h"
#include "menu.h"
#include "key.h"




int main(void)
{
	OLED_Init();
    key_config();
    
    function_test(1);
    //menu_main();


    

    while (1)
    {
        //function_ctrl();
        //Menu_key_set();
        
    }
    
}




