/* 
 * File:   main.c
 * Author: Biancaa. R
 *
 * Created on 30 May, 2025, 7:28 PM
 */

//slave code

#pragma config FOSC = HS     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits
#pragma config CP = OFF         // Flash Program Memory Code Protection bit

#include <xc.h>

#include <xc.h>
#define _XTAL_FREQ 6000000

void uart_init();
void lcd_init();
void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void lcd_display(const char*, unsigned char);
void lcd_clear();

unsigned char rx_buffer, tx_buffer;

void main() {
    uart_init();
    lcd_init();

    while (1) {
        if (RCIF) {
            rx_buffer = RCREG;

 // Display RX on LCD line 1
            lcd_clear();
            lcd_display("RX: '", 1);
            lcd_data(rx_buffer);
            lcd_data('\'');

            // Map uppercase to lowercase response
            switch (rx_buffer) {
                case 'A': tx_buffer = 'a'; break;
                case 'B': tx_buffer = 'b'; break;
                case 'C': tx_buffer = 'c'; break;
                case 'D': tx_buffer = 'd'; break;
                default: tx_buffer = 0; break;
            }

            // Send back lowercase char if valid
            if (tx_buffer) {
                while (!TXIF); // Wait until TXREG is ready
                TXREG = tx_buffer;
                __delay_ms(100);

                // Display TX on LCD line 2
                lcd_display("TX: '", 2);
                lcd_data(tx_buffer);
                lcd_data('\'');
            }
        }
    }
}

void uart_init() {
    TRISC = 0xC0; // RC6 TX, RC7 RX
    TXSTA = 0x20;
    SPBRG = 0x09;
    RCSTA = 0x90;

    // LCD Pins
    TRISD = 0x00; // Data
    TRISB3 = 0;   // RS
    TRISB1 = 0;   // EN
    PORTD = 0x00;
}

void lcd_init() {
    lcd_cmd(0x38); // 8-bit, 2 lines
    lcd_cmd(0x0C); // Display ON, cursor OFF
    lcd_cmd(0x01); // Clear display
    lcd_cmd(0x06); // Entry mode set
    __delay_ms(2);
}

void lcd_cmd(unsigned char cmd) {
    PORTD = cmd;
    RB3 = 0; // RS = 0 for command
    RB1 = 1; __delay_ms(2); RB1 = 0;
}

void lcd_data(unsigned char data) {
    PORTD = data;
    RB3 = 1; // RS = 1 for data
    RB1 = 1; __delay_ms(2); RB1 = 0;
}

void lcd_clear() {
    lcd_cmd(0x01);
  __delay_ms(2);
}

void lcd_display(const char *msg, unsigned char line) {
    if (line == 1) lcd_cmd(0x80);       // Line 1 start
    else if (line == 2) lcd_cmd(0xC0);  // Line 2 start

    while (*msg) lcd_data(*msg++);
}