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
// Use project enums instead of #define for ON and OFF.
//RD 1 RD7
//ON OFF (3 SEC DELAY) OFF ON (3 SEC DELAY ) ON ON , OFF OFF

void main(void){
    TRISD=0x00; //all bits are set as op
    PORTD=0x00;
    //setting all the led values as 0 initially
    while(1){
        PORTD=0x01; //setting PD1 only as on
        __delay_ms(3000);
        PORTD=0x80; //setting only PD7 as on
        __delay_ms(3000); //3 s delay
        PORTD=0x81; //setting both as on
        __delay_ms(3000);
        PORTD=0x00; //setting both as off
        __delay_ms(3000);

    }
}
