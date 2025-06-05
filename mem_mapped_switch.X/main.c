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
    //For portB
    unsigned char* dir_reg1=(unsigned char*)0x86;
    unsigned char* data_reg1=(unsigned char*)0x06;
    //For portc
    unsigned char* dir_reg2= (unsigned char*)0x87;
    unsigned char* data_reg2 =(unsigned char*)0x07;
    //RB4-RB7   as input regs
    //RC1 and RC4 as output regs
    //option reg =0x7F
    unsigned char* option_reg =(unsigned char*) 0x81;
    *dir_reg1 = 0xF0; //Setting MSBs as input
    *dir_reg2= 0xED; //1110 1101
    *option_reg=07F;
    while(1){
        switch(*data_reg1){
            case 0xEF:
                //RB4 switched on 
                *data_reg2=0x02;
                //RC1 ON
                break;
            case 0xDF:
                *data_reg2=0x10;
                //RC4 ON
                break;
            case 0xBF:
                *data_reg2=0x12;
                //both RC1 and RC4 on
                break;
            case 0x7F:
                *data_reg2=0x00;
                //Both Rc1 and RC4 are off
                break;
        }
    }
    
    return (EXIT_SUCCESS);
}

