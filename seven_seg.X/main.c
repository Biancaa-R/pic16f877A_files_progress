#include <xc.h>
#define _XTAL_FREQ 6000000

#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = OFF
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

unsigned char seg[] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xD8,0x00,0x90};

void main(void) {
    TRISC = 0x00;
    PORTC = 0x00;

    while(1) {
        for(unsigned char i = 0; i < 10; i++) {
            PORTC = seg[i];
            __delay_ms(200);
        }
    }
}
