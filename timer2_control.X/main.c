/* 
 * File:   main.c
 * Author: Biancaa. R
 *
 * Created on 31 January, 2025, 7:57 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#pragma config WDTE=OFF;

void init_config()
{
//(int argc, char** argv) {
    TRISD =0x00;
    init_timer2();
    GIE=1;
    PEIE=1;
    //Enabling peripheral interrupts
    
    //return (EXIT_SUCCESS);
}
int main()
{
    init_config();
    while(1){
        
    }
}

