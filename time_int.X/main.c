/* 
 * File:   main.c
 * Author: Biancaa. R
 *
 * Created on 1 June, 2025, 8:07 PM
 */

#include <stdio.h>
#include <stdlib.h>
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

unsigned char timer_count=0;

void __interrupt() timer_0()
{
    if(INTCONbits.TMR0IF==1){
        timer_count++;
        INTCONbits.TMR0IF=0;
        TMR0=197;
        //clearing the flag 0f the timer
//        if(timer_count%2==1){
//            PORTB=0x01; //turning on led
//        }
//        else{
//            PORTB=0x00;
//            //Turning off led
//        }
    }
}
int main(int argc, char** argv) {
    //command line arguments :)
    INTCONbits.GIE =1; //Eneral interrupt enable bit
    INTCONbits.PEIE =1; //Peripheral interrupt enable bit
    INTCONbits.TMR0IE =1; //Timer interrupt enable bit
    //Setting the prescalar to 256
    OPTION_REG=0x07; //ps2 ps1 ps0
    TMR0 =197;
    //10 MS
    TRISB =0x00;
    //setting it as output
    while(1){
        if(timer_count==0){
            PORTBbits.RB0=1;
        }
        if(timer_count==100){
            PORTBbits.RB0=0;
        }
        if(timer_count==200){
            timer_count=0;
        }
    }
    return (EXIT_SUCCESS);
}

