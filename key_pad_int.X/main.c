/* 
 * File:   main.c
 * Author: Biancaa. R
 *
 * Created on 7 June, 2025, 1:44 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "lcd.h"
#include "keypad.h"
#define _XTAL_FREQ 6000000

#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = OFF
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

int main(int argc, char** argv) {
    TRISC=0x00;
    TRISD=0x00;
    lcd_initialize();
    lcd_command(0x80);
    lcd_string("KEYPAD",7);
    init_keypad();
    lcd_command(0xC0); //To go to second line
    while(1){
        keypad();
        __delay_ms(200); // Wait between scans
    }
    return (EXIT_SUCCESS);
}

