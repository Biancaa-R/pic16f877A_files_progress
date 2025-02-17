// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = ON         // Data EEPROM Memory Code Protection bit (Data EEPROM code-protected)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdio.h>
#define _XTAL_FREQ 20000000
void delay(unsigned int t)
{
    for(int i=0;i<t;i++){
        __delay_ms(1);
        //for setting up a multiple of 1 ms
    }
}
//Set up a delay function instead of direct fn, to increase code reusability
void main(void){
    TRISB=0x00; //all bits are set as op
    PORTB=0x00;
    //setting all the led values as 0 initially
    while(1){
        PORTB=0x01; //setting PB0 only as on
        delay(100);
        PORTB=0x00;
        delay(100); //setting PB0 as OFF
    }
}

