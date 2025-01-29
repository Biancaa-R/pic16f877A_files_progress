/*
 * File:   main.c
 */

#include <xc.h>

#include "matrix_keypad.h"

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)






static void init_config(void) {
   
    init_matrix_keypad();
    TRISB4 = 0;
    
    
}

void main(void) {
    unsigned char key;
    
    init_config();

    while (1) {
        key = read_matrix_keypad(STATE);  // 0 1 2 3 4 5 6 7 8 9 '*' '#'  ALL_RELEASED
        if(key == 1)
        {
            RB4 = !RB4;
        }
        
    }
   
}

