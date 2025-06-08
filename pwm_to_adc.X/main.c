/*
 * File:   adc_1.c
 * Author: Biancaa. R

 */

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

void adc_lcd_init();
void lcd_number_convert(unsigned int i);
void lcd_command(unsigned char);
void lcd_data(unsigned char);

unsigned int adc_calibrated_data,adc_volt;
unsigned int adc_high,adc_low;

void main()
{
    adc_lcd_init();
    while(1){
        ADCON0 |=0x04;
        while(ADCON0 & 0x04); //Cearing go done bit
        adc_high= ADRESH;
        adc_low=ADRESL;
        adc_volt =(adc_high<<8)+adc_low;
        adc_calibrated_data=((unsigned long)adc_volt*338)/1024;
        CCPR1L =(adc_calibrated_data >> 2);
        CCP1CON =((CCP1CON & 0xCF) | ((adc_calibrated_data)&0x03) <<4);
        lcd_command(0x80);
        lcd_number_convert(adc_calibrated_data);
    }
}
    
void adc_lcd_init()
    {
        //In port B we have Pwm
        TRISB=0x00;
        TRISD=0x00;
        PORTD=0x00;
        PORTB=0x00;
        //PWM configurations
        TRISC=0xFB; //RC2 as output rest of the bits as Input
        CCP1CON =0x0C;
        T2CON=0x06;
        PR2=0x5E;
        
        //LCD configurations
        lcd_command(0x30);
        __delay_ms(100);
        lcd_command(0x30);
        __delay_ms(100);
        lcd_command(0x30);
        __delay_ms(100);
        lcd_command(0x38);
        __delay_ms(100);
        lcd_command(0x06); //Set cursor shift right
        __delay_ms(100);
        lcd_command(0x0C); //Display on cursor off
        __delay_ms(100);
        lcd_command(0x01); //Clear display
        __delay_ms(100);
        
        //ADC initialization
        ADCON1 =0x8E;
        ADCON0=0x81;
        __delay_ms(10); //acquisition time
}

void lcd_command(unsigned char i){
    PORTB&=~0x08; 
    PORTD=i;
    PORTB |=0x01; //EN AT RB0
    PORTB &= ~0x01; //EN is 0 at RB0
    __delay_ms(100);
}

void lcd_data(unsigned char i){
    PORTB |=0x08;
    PORTD=i;
    PORTB |=0x01; //EN AT RB0
    PORTB &= ~0x01; //EN is 0 at RB0
    __delay_ms(100);
    
}

void lcd_number_convert(unsigned int num) {
    char digits[4];  // 3 characters + null terminator
    digits[3] = '\0';

    // Extract least significant digit
    digits[2] = (num % 10) + '0';
    num /= 10;

    // Extract middle digit or add space
    if (num > 0)
        digits[1] = (num % 10) + '0';
    else
        digits[1] = ' ';
    num /= 10;

    // Extract most significant digit or add space
    if (num > 0)
        digits[0] = (num % 10) + '0';
    else
        digits[0] = ' ';

    // Display all 3 characters
    lcd_data(digits[0]);
    lcd_data(digits[1]);
    lcd_data(digits[2]);
}
