// PIC16F877A Configuration Bit Settings

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>

#define _XTAL_FREQ 6000000  // 6MHz crystal frequency

// Function Prototypes
void initLCD(void);
void lcd_command(unsigned char);
void lcd_data(unsigned char);
void lcd_output(unsigned int);
void delay_ms(unsigned int);

// Global Variables
unsigned char displayBuffer[6];  // Buffer to store converted digits
unsigned int num1 = 100, num2 = 200, sum;

int main() {
    initLCD();  // Initialize LCD

    sum = num1 + num2;  // Perform addition

    lcd_command(0x80); // Move cursor to the first line
    
    lcd_output(num1);   // Display first number
    lcd_data('+');      // Display '+'
    lcd_output(num2);   // Display second number
    lcd_data('=');      // Display '='
    lcd_output(sum);    // Display sum

    while (1); // Infinite loop to keep display ON
}

// Initialize LCD in 8-bit mode
void initLCD(void) {
    TRISC = 0x00; // Set PORTC as output (Control Pins)
    TRISD = 0x00; // Set PORTD as output (Data Pins)

    // LCD Initialization Sequence
    lcd_command(0x38); // 8-bit mode, 2-line display, 5x8 font
    delay_ms(5);
    lcd_command(0x0C); // Display ON, Cursor OFF
    delay_ms(5);
    lcd_command(0x06); // Entry mode: Auto-increment cursor
    delay_ms(5);
    lcd_command(0x01); // Clear display
    delay_ms(5);
}

// Send command to LCD
void lcd_command(unsigned char cmd) {
    PORTC &= ~0x08; // RS = 0 (Command mode)
    PORTD = cmd;    // Send command to data port
    PORTC |= 0x01;  // Enable pulse
    __delay_ms(1);
    PORTC &= ~0x01; // Disable pulse
    delay_ms(2);
}

// Send data to LCD
void lcd_data(unsigned char data) {
    PORTC |= 0x08;  // RS = 1 (Data mode)
    PORTD = data;   // Send data to LCD
    PORTC |= 0x01;  // Enable pulse
    __delay_ms(1);
    PORTC &= ~0x01; // Disable pulse
    delay_ms(2);
}

// Convert integer to LCD displayable format
void lcd_output(unsigned int value) {
    unsigned char index = 0;

    if (value == 0) { 
        lcd_data('0'); // If value is zero, print directly
        return;
    }

    while (value > 0) {
        displayBuffer[index++] = (value % 10) + '0'; // Convert integer to ASCII
        value /= 10;
    }

    while (index > 0) {
        lcd_data(displayBuffer[--index]); // Print in correct order
    }
}

// Simple delay function
void delay_ms(unsigned int count) {
    while (--count);
}
