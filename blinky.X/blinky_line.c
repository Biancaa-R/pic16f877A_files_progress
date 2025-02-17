#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
//#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdio.h>
#define _XTAL_FREQ 20000000
void main1()
{
    TRISB=0x00;
    //setting all the B as Output
    PORTB=0x00;
    while(1){
        RB0=1;
        RB7=0;
        __delay_ms(100);
        RB1=1;
        RB0=0;
        __delay_ms(100);
        RB2=1;
        RB1=0;
        __delay_ms(100);
        RB3=1;
        RB2=0;
        __delay_ms(100);
        RB4=1;
        RB3=0;
        __delay_ms(100);
        RB5=1;
        RB4=0;
        __delay_ms(100);
        RB6=1;
        RB5=0;
        __delay_ms(50);
        RB7=1;
        RB6=0;
        __delay_ms(50); 
        
    }
}
