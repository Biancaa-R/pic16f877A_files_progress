#include <xc.h>
#include <stdint.h>
// CONFIGURATION BITS
#pragma config FOSC = EXTRC     
#pragma config WDTE = OFF       
#pragma config PWRTE = OFF      
#pragma config BOREN = OFF      
#pragma config LVP = OFF        
#pragma config CPD = OFF        
#pragma config WRT = OFF        
#pragma config CP = OFF         

#define _XTAL_FREQ 6000000

unsigned int adc_high;
unsigned int adc_low, adc_volt;

// Function Prototypes
void lcd_command(unsigned char cmd);
void lcd_data(unsigned char data);
void lcd_init(void);
void lcd_print_number(unsigned int val);
void lcd_goto(unsigned char pos);

// LCD Control Pins: RC3 = RS, RC0 = E
#define RS RC3
#define E  RC0

// Send command to LCD
void lcd_command(unsigned char cmd) {
    RS = 0;
    PORTD = cmd;
    E = 1;
    __delay_ms(1);
    E = 0;
    __delay_ms(2);
}

// Send data to LCD
void lcd_data(unsigned char data) {
    RS = 1;
    PORTD = data;
    E = 1;
    __delay_ms(1);
    E = 0;
    __delay_ms(2);
}

// LCD Initialization
void lcd_init() {
    TRISC = 0x00;
    TRISD = 0x00;
    lcd_command(0x38); // 8-bit mode
    lcd_command(0x0C); // Display ON, cursor OFF
    lcd_command(0x06); // Auto-increment cursor
    lcd_command(0x01); // Clear screen
    __delay_ms(5);
}

// Go to specific position
void lcd_goto(unsigned char pos) {
    lcd_command(0x80 + pos);  // pos = 0?15 for line 1, add 0x40 for line 2
}

// Print number (0?9999) to LCD
void lcd_print_number(unsigned int val) {
    lcd_data('0' + (val / 1000) % 10);
    lcd_data('0' + (val / 100) % 10);
    lcd_data('0' + (val / 10) % 10);
    lcd_data('0' + (val % 10));
}

void main(void) {
    unsigned int adc_val0, adc_val4, adc_val4_1;

    lcd_init();
    ADCON1 = 0x82; // Right justify, Vref=Vdd
    TRISA = 0xFF;  // AN0 and AN4 (RA0 and RA5) as input

    while(1) {
        // --- Read AN0 (channel 0) ---
        ADCON0 = 0x81;       // Select AN0, ADC ON
        __delay_ms(2);
        ADCON0 |= 0x04;      // Start conversion
        while (ADCON0 & 0x04);
        adc_high = ADRESH;
        adc_low = ADRESL;
        adc_val0 = (adc_high << 8) | adc_low;
        __delay_ms(10);

        // --- Read AN4 (channel 4) ---
        ADCON0 = 0xA1;       // Select AN4, ADC ON
        __delay_ms(2);
        ADCON0 |= 0x04;      // Start conversion
        while (ADCON0 & 0x04);
        adc_high = ADRESH;
        adc_low = ADRESL;
        adc_val4 = (adc_high << 8) | adc_low;
        //adc_val4_1 = (adc_val4 * 135) / 1023;  // Scale 0?1023 to 0?135
        adc_val4_1 = ((unsigned long)adc_val4 * 135) / 1023;
        

        // --- Display CH1 ---
        lcd_command(0x80);   // Line 1 Start
        lcd_data('C'); lcd_data('H'); lcd_data('1'); lcd_data(':');
        lcd_print_number(adc_val0);           // Display full 10-bit ADC value

        // --- Display CH2 ---
        lcd_command(0xC0);   // Line 2 Start
        lcd_data('C'); lcd_data('H'); lcd_data('2'); lcd_data(':');
        lcd_print_number(adc_val4_1);         // Display scaled value 0?135

        __delay_ms(200);
    }
}

