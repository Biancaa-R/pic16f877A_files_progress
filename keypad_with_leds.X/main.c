/* 
 * File:   main.c
 * Author: Biancaa. R
 *
 * Created on 28 January, 2025, 3:02 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#define _XTAL_FREQ 20000000 //Specify the XTAL crystall FREQ
void init_config(void)
{
 /*TRISD ?? x x x x     x x x x

TRISD =TRISD & 0xFO //for configuring last 4 as output

TRISB ??> x x x x   x x x x

TRISB =TRISB | 0x 07 // for configuring last 3 as input*/
    TRISD =TRISD & 0xF0;
    TRISB =TRISB | 0x07;
    
}
int read_switches(void){
   //for row 1 
    RD3=0;
    RD2=1;
    RD1=1;
    RD0=1;
    if (RB0==0){
        return 1;
    }
    if (RB1==0){
        return 2;
    }
    if (RB2==0){
        return 3;
    }
   //for row 2
    RD3=1;
    RD2=0;
    RD1=1;
    RD0=1;
    if (RB0==0){
        return 4;
    }
    if (RB1==0){
        return 5;
    }
    if (RB2==0){
        return 6;
    }
    
    //row 3
   //for row 1 
    RD3=1;
    RD2=1;
    RD1=0;
    RD0=1;
    if (RB0==0){
        return 7;
    }
    if (RB1==0){
        return 8;
    }
    if (RB2==0){
        return 9;
    }
   //for row 1 
    RD3=1;
    RD2=1;
    RD1=1;
    RD0=0;
    if (RB0==0){
        return 10;
    }
    if (RB1==0){
        return 11;
    }
    if (RB2==0){
        return 12;
    }
}
int main() {

    init_config();
    while(1){
        unsigned int key=read_switches();
        //led is in rb4
        if (key ==1){
            RB4=!RB4;
            __delay_ms(100);
        }
    }
}

