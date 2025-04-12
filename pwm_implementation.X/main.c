/*
 * File:   main.c
 * Author: Biancaa. R
 *
 * Created on 11 April, 2025, 9:42 PM
 */
//time period is stored in PR2 register
//CCPR1L,CCP1CON(5:4) stores the duty cycle)
//CCP1CON __ ___ CCPXX CCPXY CCPXM3 CCPXM2 CCPXM1 CCPXM0
//T2CKPS1->0 To set pre scalar value 00->1,01->4 1X->16
//set to 16 
//38 -> 0010 0110
//duty cycle =0.1/pwm_freq
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
#include <xc.h>
#define _XTAL_FREQ 6000000

unsigned char pwm10_low;
unsigned char pwm10_high;
//just storing of the value in a variable before assigning it to a register
unsigned char pwm50_high;
unsigned char pwm50_low;
unsigned char pwm80_high;
unsigned char pwm80_low;
    
void pwm_init(void);
void pwm_dutycycle_update(void);
void main(void) {
    pwm_init();
    while(1){
        pwm_dutycycle_update();
    }
    return;
}
//void pwm_dutycycle_update(void){
//    CCPR1L=pwm10_high;//msb high
//    //CCP1CON=((CCP1CON)& 0xCF ) |(pwm10_low<<4);//10per low value 4:5
//    CCP1CON = (CCP1CON & 0xCF) | ((pwm10_low << 4) & 0x30);  // update bits 5:4
//    // Make sure you previously initialized PWM mode: CCP1CON = 0x0C;
//    __delay_ms(1000);
//    CCPR1L=pwm50_high;
//    CCP1CON=(CCP1CON&0xCF) |(pwm50_low<<4);
//    __delay_ms(1000);
//    CCPR1L=pwm80_high;
//    CCP1CON=(CCP1CON&0xCF) |(pwm80_low<<4);
//    __delay_ms(1000);
//}

void pwm_dutycycle_update(void){
    CCPR1L = pwm10_high;
    CCP1CON = (CCP1CON & 0xCF) | ((pwm10_low ) << 4);
    __delay_ms(1000);

    CCPR1L = pwm50_high;
    CCP1CON = (CCP1CON & 0xCF) | ((pwm50_low ) << 4);
    __delay_ms(1000);

    CCPR1L = pwm80_high;
    CCP1CON = (CCP1CON & 0xCF) | ((pwm80_low ) << 4);
    __delay_ms(1000);
}

void pwm_init(void){
    //Configure RC2 -->op
    TRISC= 0xFB;
    CCP1CON=0x0c;
    //no data configuring 11xx -> PWM enable
    T2CON =0x06;
    //pwm period =pr2+1 *4* Tosc
    //PB2 =(FOSC/($*fpwm*TMR2_PRESCALER_VALUE))-1
    PR2=0x5E; //for setting duration of pwm
    pwm10_low=0x02;
    pwm10_high=0x09;
    //just storing of the value in a variable before assigning it to a register
    pwm50_high =0x2F;
    pwm50_low =0x00;
    pwm80_high =0x4B;
    pwm80_low =0x00;
}