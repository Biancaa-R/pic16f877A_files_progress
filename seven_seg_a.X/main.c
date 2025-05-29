#pragma config FOSC = HS     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits
#pragma config CP = OFF         // Flash Program Memory Code Protection bit

#include <xc.h>
#define _XTAL_FREQ 6000000

unsigned char arr[10] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6};
unsigned char i;

void main(void) {
    TRISB = 0x00;          // PORTB as output
    OPTION_REG &= 0x7F;    // Timer0 clock source internal
    PORTB = 0xFF;        

    i = 0;

    while(1) {
        PORTB = arr[i];   
        __delay_ms(1000);

        i++;
        if(i > 9) {
            i = 0;
        }
    }
}
