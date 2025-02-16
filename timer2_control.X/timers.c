#include <xc.h>
#include "timers.h"

void init_timer2()
{
    //selecting post scalar (should be 000 1:1)
    TOUTPS2=0;
    TOUTPS1=0;
    TOUTPS3=0;
    TMR2ON=1;
    //Turning on the timer
    T2CKPS1=0;
    T2CKPS0=0;
    //Enable timer 2 interrupt
    TMR2IE=1;
    //cear timer2 interrupt flag
    TMR2IF=0;
    PR2=250;
    
}
