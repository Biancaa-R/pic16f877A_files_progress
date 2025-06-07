/* 
 * File:   keypad.h
 * Author: Biancaa. R
 *
 * Created on 7 June, 2025, 2:12 PM
 */

#ifndef KEYPAD_H
#define	KEYPAD_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <xc.h>
#include "lcd.h"
#define R1 RB3
#define R2 RB4
#define R3 RB5
#define R4 RB6
#define C1 RB0
#define C2 RB1
#define C3 RB2
//For defining the keywords
//MSBs as input and LSB s as output
void init_keypad(void);
void keypad();
#ifdef	__cplusplus
}
#endif

#endif	/* KEYPAD_H */

