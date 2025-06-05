#define _XTAL_FREQ 20000000
#include <xc.h>

// CONFIG
#pragma config FOSC = HS, WDTE = OFF, PWRTE = OFF, BOREN = OFF, LVP = OFF, CPD = OFF, WRT = OFF, CP = OFF

#define RS RB3
#define EN RB1
#define LCDPORT PORTD

void lcd_cmd(char cmd) {
    RS = 0;
    LCDPORT = cmd;
    EN = 1;
    __delay_ms(2);
    EN = 0;
}

void lcd_data(char data) {
    RS = 1;
    LCDPORT = data;
    EN = 1;
    __delay_ms(2);
    EN = 0;
}

void lcd_init() {
    TRISD = 0x00;
    //TRISB3 = 0;
    //TRISB1 = 0;
    TRISBbits.TRISB3 = 0;   // Set RB3 (RS) as output
    TRISBbits.TRISB1 = 0;   // Set RB1 (EN) as output
    LCDPORT = 0;

    __delay_ms(20);       // Power-on delay
    lcd_cmd(0x38);        // 8-bit mode
    lcd_cmd(0x0C);        // Display ON, Cursor OFF
    lcd_cmd(0x01);        // Clear display
    lcd_cmd(0x06);        // Entry mode
}

void lcd_set_cursor(char row, char col) {
    char pos = (row == 1) ? 0x80 + (col - 1) : 0xC0 + (col - 1);
    lcd_cmd(pos);
}

void lcd_string(const char *str) {
    while (*str) lcd_data(*str++);
}

void main() {
    lcd_init();
    lcd_set_cursor(1, 1);
    lcd_string("LCD OK TEST");
    lcd_set_cursor(2, 1);
    lcd_string("WORKING");
    while (1);
}
