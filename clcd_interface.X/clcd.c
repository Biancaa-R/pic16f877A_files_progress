#include <stdio.h>
#include<xc.h>
#include <string.h>
#include "clcd.h"

void init_clcd(void)
{   // in 4 bit mode:
    // rd7 6 5 4 --> as the output
    // TRISDD= TRISD & 0x0F;]
    CLCD_DATA_PORT_DDR= CLCD_DATA_PORT_DDR & 0x0F;
    CLCD_RS_DDR=0;
    CLCD_EN_DDR=0;
    init_display_controller();
    
}

void clcd_putch(const char data,unsigned char addr){
    
}

void clcd_print()
{   //0x80 --> first line 
    //0xc0 -->second line
    
}

void clcd_write(int byte,int control_bit){
  //1 for data 0 for instruction  
}