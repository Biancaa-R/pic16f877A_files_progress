# include <stdio.h>

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
# define _XTAL_FREQ 20000000
void main1(){
    TRISB=0xFF;
    //All bits are set as input
    PORTB=0xFF;
    TRISC=0x00;
    PORTC=0X00;
    //all bits are configured to output low
    //setting rb1 rb2 rb3 rb4 as input pins
    //setting rc1 rand rc2 as output
    while(1){
        if (PORTB==0xFD){
            PORTC=0x02;
        }
        if(PORTB ==0xFB){
            PORTC =0x04;
        }
        if (PORTB == 0xF7){
            PORTC =0x06;
        }
        if (PORTB == 0xEF){
            PORTC= 0x00;
        }
    }
}
