/*
 * File:   adc_1.c
 * Author: Biancaa. R
 *
 * Created on 3 May, 2025, 12:20 AM
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

unsigned int adc_high;
unsigned int adc_low,calibrated_val,adc_volt;
unsigned int i,j,d1,d2,d3,d4;

// Send command to LCD
void lcd_command(unsigned char cmd) {
    PORTC &= ~0x08; // RS = 0 (Command mode)
    PORTD = cmd;    // Send command to data port
    PORTC |= 0x01;  // Enable pulse
    __delay_ms(1);
    PORTC &= ~0x01; // Disable pulse
    __delay_ms(2);
}


// Initialize LCD in 8-bit mode
void initLCD(void) {
    //OPTION_REG &= ~(1 << 7);  // Enable PORTB pull-ups (RBPU = 0)
    
    TRISC = 0x00; // Set PORTC as output (Control Pins)
    TRISD = 0x00; // Set PORTD as output (Data Pins)
    TRISB =0xF0;
    PORTB=0xF0;
    // LCD Initialization Sequence
    lcd_command(0x38); // 8-bit mode, 2-line display, 5x8 font
    __delay_ms(5);
    lcd_command(0x0C); // Display ON, Cursor OFF
    __delay_ms(5);
    lcd_command(0x06); // Entry mode: Auto-increment cursor
    __delay_ms(5);
    lcd_command(0x01); // Clear display
    __delay_ms(5);
}
// Send data to LCD
void lcd_data(unsigned char data) {
    PORTC |= 0x08;  // RS = 1 (Data mode)
    PORTD = data;   // Send data to LCD
    PORTC |= 0x01;  // Enable pulse
    __delay_ms(1);
    PORTC &= ~0x01; // Disable pulse
    __delay_ms(2);
}

// Convert integer to LCD displayable format
void lcd_number_convert(unsigned int i) {
//    unsigned char index = 0;
//
//    if (value == 0) { 
//        lcd_data('0'); // If value is zero, print directly
//        return;
//    }
//
//    while (value > 0) {
//        array[index++] = (value % 10) + '0'; // Convert integer to ASCII
//        value /= 10;
//    }
//
//    while (index > 0) {
//        lcd_data(array[--index]); // Print in correct order
//    }
    //typecasting
    d4=(unsigned char)(i/1000);
    d3=(unsigned char)((i-(d4*1000))/100);
    d2=(unsigned char)((i-(d4*1000)-(d3*100))/10);
    d1=(unsigned char)((i-(d4*1000)-(d3*100)-(d2*10)));
    lcd_command(0x88);
    lcd_data(0x30+d4);
    //fucking asci change
    lcd_command(0x89);
    lcd_data(0x30+d3);
    lcd_command(0x8A);
    lcd_data(0x30+d2);
    lcd_command(0x8B);
    lcd_data(0x30+d1);
}

// Simple delay function
void delay_ms(unsigned int count) {
    //while (--count);
    for(int i=0;i<count;i++){
       //pass
    }
}

void lcd_num_conv(unsigned int i){
    int j=1,s;
    unsigned int m;
    unsigned char k[5];
    m=i;
    while(m!=0){
        s=(m-(m/10)*10);
        k[j]=s;
        j++;
        m=m/10;
    }
    k[j]='\0';
    j--;
//    while(j!=0){
//        lcd_data(0x30 +k[j]);
//        j--;
//    }
    if(k[2]>0){
        lcd_command(0x80);
        lcd_data(0x30 +k[2]);
        
        lcd_command(0x81);
        lcd_data(0x30+k[1]);
    }
    else{
        lcd_command(0x80);
        lcd_data(0x20);
        lcd_command(0x81);
        lcd_data(0x30+k[1]);
    }
    lcd_command(0x82);
    lcd_data(0x76);
    __delay_ms(5);  // half a second delay between updates

}


void main(void) {
    //adc_lcd_init();
    initLCD();
    ADCON1 = 0x8E;     // Right justify result, Vref = Vdd
    ADCON0 = 0x81;     // ADC ON, Channel 0 (AN0)
    TRISA0 = 1;        // Set RA0/AN0 as input

    while(1){
    ADCON0 |=0x04; //ADCON0 =0x85
    delay_ms(10);
    while(ADCON0 &0X04);
    adc_high=ADRESH;
    adc_low=ADRESL;
    adc_volt =(adc_high<<8) | (adc_low);
    calibrated_val=(adc_volt*48)/1024;
    lcd_command(0x80);
    //incase of calibrating to 100 , another datatype has to be used instead
    lcd_num_conv(calibrated_val);
    __delay_ms(20);
    return;
}
}

