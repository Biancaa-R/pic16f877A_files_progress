/* 
 * File:   main.c
 * Author: Biancaa. R
 *
 * Created on 17 June, 2025, 8:54 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
#define _XTAL_FREQ 6000000

void __interrupt() _ISR() {
    if (INTCON & 0x02) { // Check INTF bit (bit 1)
        PORTD ^= 0x01;   // Toggle RD0
        INTCON &= ~0x02; // Clear INTF bit
    }
}

void main(void) {
    // I/O Setup
    TRISB = 0x01;      // RB0 as input (bit 0 = 1)
    TRISD = 0x00;       // PORTD as output
    PORTD = 0x00;

    // Interrupt Edge Setup
    OPTION_REG &=0x7F;
    OPTION_REG |= 0x40; // INTEDG = 1 (bit 6 = rising edge)
    //If INTEDG =0 ,falling edge

    // INTCON Setup
    INTCON = 0x90;      // GIE (bit 7) = 1, INTE (bit 4) = 1, others 0

    while (1) {
        // Main loop
        PORTB=0x02;
        __delay_ms(200);
        PORTB=0x00;
        __delay_ms(200);
    }
}
