/* 
 * File:   lcd.c
 * Author: Biancaa. R
 *
 * Created on 7 June, 2025, 1:48 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "lcd.h"
//#include <xc.h>
#define _XTAL_FREQ 6000000
void lcd_data(unsigned char data){
    PORTC=data;
    RS=1;
    EN=1;
    __delay_ms(5);
    EN=0;
}

void lcd_command(unsigned char command){
    PORTC =command;
    RS=0;
    EN=1;
    __delay_ms(5);
    EN=0;
}

void lcd_string(const unsigned char *string,unsigned char length){
    unsigned char i;
    for (i=0;i<length;i++){
        lcd_data(string[i]);
    }
}

void lcd_initialize()
{
    lcd_command(0x38);
    lcd_command(0x06);
    lcd_command(0x0C);
    lcd_command(0x01);
}

