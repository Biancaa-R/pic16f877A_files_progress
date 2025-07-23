/* 
 * File:   main.c
 * Author: Biancaa. R
 *
 * Created on 23 July, 2025, 11:09 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

unsigned int byte;
unsigned int rem;
int arr1[10]={};

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
    PORTD=0x00;
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


// Simple delay function
void delay_ms(unsigned int count) {
    //while (--count);
    for(int i=0;i<count;i++){
       //pass
    }
}

void WriteByteToEE(unsigned char data,const unsigned char address){
    EEADR=address;
    EEDATA=data;
    //EECON1bits.EEPGD=0 //To show we are writing to data memory
    EECON1 &= ~(1<<7);
    //EECON1bits.WREN=1
    EECON1 |= (1<<2);
    EECON2=0x55;
    EECON2=0xAA;
    //It is an imaginary register
    //EECON1bits.WR=1
    EECON1 |= (1<<1);
    //as the steps given to write to the eeprom
    //wait for the write flag to be set
    while(PIR2bits.EEIF==0);
    PIR2bits.EEIF=0;
}

void ReadByteFromEE(const unsigned char address){
    EEADR=address;
    EECON1 &= ~(1<<7);//to set the reading to be from data
    //to set the read bit to trigger reading
    EECON1 |=(1<<0);
    byte=EEDATA;//global
}

void main(void) {
    //adc_lcd_init();
    initLCD();
    lcd_command(0x80);
    char* value="EEPROM VALUE:";
    for(int i=0;i<strlen(value);i++){
        lcd_data(value[i]);
    }
        //printed in the starting
        //Ok I want to implement squares
        WriteByteToEE(0,0x00);
        WriteByteToEE(1,0x01);
        WriteByteToEE(4,0x02);
        WriteByteToEE(9,0x03);
        WriteByteToEE(16,0x04);
        WriteByteToEE(25,0x05);
        WriteByteToEE(36,0x06);
        WriteByteToEE(49,0x07);
        WriteByteToEE(64,0x08);
        WriteByteToEE(81,0x09);
        WriteByteToEE(100,0x0A);
        WriteByteToEE(121,0x0B);
        WriteByteToEE(144,0x0C);
        WriteByteToEE(169,0x0D);
        WriteByteToEE(196,0x0E);
        WriteByteToEE(225,0x0F);
    while(1){
        for (int i=0;i<16;i++){
            ReadByteFromEE(i); 
            __delay_ms(200);
            int count=0;
            lcd_command(0xC0);
            lcd_data(32);
            lcd_data(32);
            lcd_data(32);
            lcd_data(32);
            //clearing the screen
            lcd_command(0xC0);
            //only if data is 
            if(byte<10){
                lcd_data(byte+0x30);
                //single digit
            }
            else{
                while(byte>0){
                    int rem=byte%10;
                    byte=byte/10;
                    arr1[count]=rem;
                    count++;//1 extra than the actual written vlues
                }
                //arr1[count+1]='\0';
                for(int j=count-1;j>=0;j--){
                    //lcd_data(arr1[j]);
                    lcd_data(arr1[j] + 0x30);
                }
            }
            //lcd_data(byte+0x30);
            //data that is read from the eeprom
        }
    }
    return;
}


