/* 
 * File:   main.c
 * Author: Biancaa. R
 *
 * Created on 16 February, 2025, 12:13 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "clcd.h"
#pragma config WDTE=OFF
void init_config()
{
    init_clcd();
}
int main(void) {
    init_config();
    while(1){
        clcd_putch('A',LINE1(0));
        clcd_print("Hello",LINE2(0));
    }
    //return (EXIT_SUCCESS);
}

