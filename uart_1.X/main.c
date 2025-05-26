/* 
 * File:   main.c
 * Author: Biancaa. R
 *
 * Created on 25 May, 2025, 3:02 PM
 */

// PIC16F877A Configuration Bit Settings
//No need of pull up as enabled internal pull up
// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>

#define _XTAL_FREQ 6000000  // 6MHz crystal frequency

#include <stdio.h>
#include <stdlib.h>

void uart_init();
unsigned char value;
int main(int argc, char** argv) {
    
    uart_init();
    while(1){
        value =PORTB;
        switch(value){
            case 0xE0:
                TXREG='A';
                __delay_ms(100);
                break;
            case 0xD0:
                TXREG='B';
                __delay_ms(100);
                break;
            case 0xB0:
                TXREG='C';
                __delay_ms(100);
                break;
            case 0x70:
                TXREG='D';
                __delay_ms(100);
                break;
        }
    }
    return (EXIT_SUCCESS);
}

void uart_init(){
    //pin config
    TRISB=0xF0;  //RB4 to RB7 as input
    PORTB=0x00;
    OPTION_REG &= 0x7F; //enable pull up
    //uart configuration
    TRISC =0xC0;
    TXSTA =0x20;
    //transmit status and control register
    SPBRG =0x09;
    RCSTA=0x90;
}

