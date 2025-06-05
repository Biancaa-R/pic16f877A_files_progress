/* 
 * File:   main.c
 * Author: Biancaa. R
 *
 * Created on 5 June, 2025, 9:44 PM
 */

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

//#include <xc.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    unsigned char* dir_reg= (unsigned char*)0x87;
    unsigned char* data_reg =(unsigned char*)0x07;
    *dir_reg=0x00; //Setting it as output
    while(1){
        *data_reg= 0x00;
        for(int i=0;i<100000;i++){
            //blocking delay
        }
        *data_reg=(unsigned char*)0xFF;
        for(int i=0;i<100000;i++){
            //blocking delay
        }
    }
    return (EXIT_SUCCESS);
}

