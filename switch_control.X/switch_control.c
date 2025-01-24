//switch rb8 led rd0
#include <xc.h>
#pragma config WDTE=OFF
#include "main.h"
void init_config(void) 
{
  //config RB3 as input
    TRISB3 = 0xFF;
    
  // cofig RD0 as output 
    TRISD0 = 0x00;
    
}

void main(void) 
{
    init_config();
    while (1) 
    {
        // switch is pressed toggle LED
        //checking if switch is pressed
        if (SWITCH1 == 0)
        {
            LED1 = !LED1;
            for(unsigned int i=0;i<50000;i++){
              //no operation  
            }
        }
        
    }
    
}