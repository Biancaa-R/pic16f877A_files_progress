//edge triggering
#include <xc.h>
#pragma config WDTE=OFF
unsigned int once=1;
void init_config(void) 
{
  //config RB3 as input
    TRISB3 = 1;
    
  // cofig RD0 as output 
    TRISD0 = 0;
    
}
int main()
{   
while(1){
for(unsigned int wait=500; wait>0; wait--);
if(RB3==0 && once==1){
    once=0;
    RD0=!RD0;
    }
if(RB3==1){
    //to check if switch is released
    once=1;
}
}
} 