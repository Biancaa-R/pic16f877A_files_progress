/*
 * File:   clcd.c
 * Author: Biancaa.R
 *
 * Created on 22 February, 2025, 1:30 AM
 */
#include <stdio.h>
#include <xc.h>
#include <string.h>
#include "clcd_inter.h"

void clcd_write(unsigned char byte, unsigned char mode) {
    // 1 for data, 0 for instruction  
    CLCD_RS = (mode != 0);  // Ensure mode is 0 or 1

    // Send upper nibble
    CLCD_DATA_PORT = byte & 0xF0;
    CLCD_EN = HI;
    __delay_us(100);
    CLCD_EN = LOW;

    // Send lower nibble
    CLCD_DATA_PORT = (unsigned char)((byte & 0x0F) << 4);
    CLCD_EN = HI;
    __delay_us(100);
    CLCD_EN = LOW;

    __delay_ms(4);  // Replacing 4100 us with 4 ms
}

static void init_display_controller(void) {
    /* Startup Time for the CLCD controller */
    __delay_ms(30);

    /* CLCD Startup Sequence */
    clcd_write(EIGHT_BIT_MODE, INST_MODE);  // 0x33
    __delay_ms(4);
    clcd_write(EIGHT_BIT_MODE, INST_MODE);  // 0x3
    __delay_us(100);
    clcd_write(EIGHT_BIT_MODE, INST_MODE);  // 0x3
    __delay_us(1);

    clcd_write(FOUR_BIT_MODE, INST_MODE);  // 0x20
    __delay_us(100);
    clcd_write(TWO_LINES_5x8_4_BIT_MODE, INST_MODE);  // 0x28
    __delay_us(100);
    clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
    __delay_ms(2);
    clcd_write(DISP_ON_AND_CURSOR_OFF, INST_MODE);
    __delay_us(100);
}

void clcd_putch(const char data, unsigned char addr) {
    clcd_write(addr, INST_MODE);  // Set cursor position
    clcd_write(data, DATA_MODE);  // Write character
}

void clcd_print(const char *str, unsigned char addr) {
    clcd_write(addr, INST_MODE);  // Set cursor position

    while (*str != '\0') {
        clcd_write(*str, DATA_MODE);  // Write each character
        str++;
    }
}
void clcd_print_right_to_left(const char *str, unsigned char addr)
{
    int len = strlen(str);
    
    // Start printing from the rightmost position
    //addr = addr + (16 - len);  
    //strrev(str);
    for (int i = 0; i <len; i++) {
        clcd_write(addr, INST_MODE); // Move cursor
        clcd_write(str[i], DATA_MODE); // Print character
        addr=addr-1; // Move left
        
       // __delay_ms(500); // Optional delay for visibility
    }
}


void init_clcd(void) {
    // Set data port upper nibble as output
    CLCD_DATA_PORT_DDR &= 0x0F;
    CLCD_RS_DDR = 0;
    CLCD_EN_DDR = 0;

    init_display_controller();
}
