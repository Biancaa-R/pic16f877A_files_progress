/* 
 * File:   lcd.h
 * Author: Biancaa. R
 *
 * Created on 7 June, 2025, 1:47 PM
 */

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <xc.h>
#define RS RD0
#define EN RD1

void lcd_data(unsigned char data);
void lcd_command(unsigned char command);
void lcd_string(const unsigned char *string,unsigned char length);
void lcd_initialize();
#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

