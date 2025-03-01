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

unsigned char val;
void main() {
    // Disable analog inputs (for PIC16F877A or similar)
    //ADCON1 = 0x06;
    //CMCON = 0x07;

    TRISB = 0xF0;  // PORTB as input rb4 to rb7
    PORTB = 0x00;  // Pull-down resistors (if needed externally)

    TRISC = 0x00;  // PORTC as output
    PORTC = 0x00;  // Initialize to LOW

    while(1) {
        val=PORTB;
        switch(val){
            case 0x10:
                PORTC=0x02;
                break;
            case 0x20:
                PORTC=0x04;
                break;
            case 0x40:
                PORTC=0x06;
                break;
            case 0x80:
                PORTC=0x00;
                break;
        }
    }
}


