#include <xc.h>

#define _XTAL_FREQ 20000000

// CONFIG
#pragma config FOSC = EXTRC     
#pragma config WDTE = OFF       
#pragma config PWRTE = OFF      
#pragma config BOREN = OFF      
#pragma config LVP = OFF        
#pragma config CPD = OFF        
#pragma config WRT = OFF        
#pragma config CP = OFF         

void main() {
    // Disable analog inputs (for PIC16F877A or similar)
    ADCON1 = 0x06;
    CMCON = 0x07;

    TRISB = 0xFF;  // PORTB as input
    PORTB = 0xFF;  // Pull-up resistors (if needed externally)

    TRISC = 0x00;  // PORTC as output
    PORTC = 0x00;  // Initialize to LOW

    while(1) {
        if ((PORTB & 0x02) == 0) { // RB1 LOW
            PORTC = 0x02;
        }
        if ((PORTB & 0x04) == 0) { // RB2 LOW
            PORTC = 0x04;
        }
        if ((PORTB & 0x08) == 0) { // RB3 LOW
            PORTC = 0x06;
        }
        if ((PORTB & 0x10) == 0) { // RB4 LOW
            PORTC = 0x00;
        }
    }
}

