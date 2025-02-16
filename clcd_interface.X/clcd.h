/* 
 * File:   clcd.h
 * Author: Biancaa. R
 *
 * Created on 16 February, 2025, 12:15 AM
 */

#ifndef CLCD_H
#define	CLCD_H

#define _XTAL_FREQ                  20000000
//setting up of frequency for setting up internal delay

#define CLCD_DATA_PORT_DDR          TRISD  // PORTD as input
#define CLCD_RS_DDR                 TRISE2 //RE2 as RS pin
#define CLCD_EN_DDR                 TRISE1 //RE1 as EN pin

#define CLCD_DATA_PORT              PORTD
#define CLCD_RS                     RE2
#define CLCD_EN                     RE1

#define INST_MODE                   0
#define DATA_MODE                   1

#define HI                          1
#define LOW                         0

#define LINE1(x)                    (0x80 + x)  // line1(0) -> 0x80... line1(15)
#define LINE2(x)                    (0xC0 + x)
#define LINE3(x)                    (0x90 + x)
#define LINE4(x)                    (0xD0 + x)
//defining the address of the first 4 lines


#define EIGHT_BIT_MODE              0x33
#define FOUR_BIT_MODE               0x02
#define TWO_LINES_5x8_4_BIT_MODE    0x28
#define CLEAR_DISP_SCREEN           0x01
#define DISP_ON_AND_CURSOR_OFF      0x0C

void init_clcd(void);// initialization of the clcd
void clcd_putch(const char data, unsigned char addr);
void clcd_print(const char *str, unsigned char addr);
void clcd_write(unsigned char byte, unsigned char mode);
// in 4 bit mode:
// rd7 6 5 4 --> as the output
// TRISDD= TRISD && 0x0F;]
#endif	/* CLCD_H */

