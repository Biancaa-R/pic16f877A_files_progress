#include<pic.h>
// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
//#pragma config CPD = ON         // Data EEPROM Memory Code Protection bit (Data EEPROM code-protected)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF   

void t0delay();

void main()
{
  TRISB=0;
  OPTION_REG=0x07;   //Prescale is assigned to Timer 0, Prescaler value = 256, Fclk = 11.0592MHz
  while(1) {
    PORTB=0xff;
    t0delay();
    PORTB=0x00;
    t0delay();
  }
}

void t0delay()          // 1 second
{
  int i;
  for(i=0;i<42;i++) {
    while(!T0IF);
    T0IF=0;
  }
}        
