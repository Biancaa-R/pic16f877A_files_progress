#include<xc.h>
//for toggling an led from port b
//using data direction register
//unsigned char*TRISB=0x86;
//need not create a pointer as it is included (definition of address )in xc.h
#pragma config WDTE=OFF
//WDTE stands for Watchdog Timer Enable in a PIC microcontroller. It is a configuration setting
//that allows the microcontroller to reset if the internal watchdog timer rolls over
void init_config(void)
{
   TRISB=0x00; 
   //configure it as output
   //note :in simulator turn off rtc
}
int main()
{
    init_config();
    while(1){
      PORTB=0xFF;
      //turn all leds
      for(unsigned int i=0;i<50000;i++){
          //no event
      }
      PORTB=0x00;
      for(unsigned int i=0;i<50000;i++){
          //no event
      }
    }
}
