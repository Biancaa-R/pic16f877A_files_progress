#include "keypad.h"
#define _XTAL_FREQ 6000000
void init_keypad(void){
    //TRISB=0x0F;
    TRISB = 0b11111000;  // RB7-RB4 = input (rows), RB3-RB0 = output (columns)
    PORTB = 0x0F;  // Ensure columns start high
    OPTION_REG=0x7F;
    //Setting the Rows as input and the collumns as output
    PORTB &= 0b00000111;      // Clear column outputs (RB0-RB2), keep MSBs untouched
    
}

void keypad(){
    // Column 1 scan
    C1=0; C2=1; C3=1;
    if (R1==0){ lcd_data('1'); while(R1==0); __delay_ms(200); }
    if (R2==0){ lcd_data('4'); while(R2==0); __delay_ms(200); }
    if (R3==0){ lcd_data('7'); while(R3==0); __delay_ms(200); }
    if (R4==0){ lcd_data('*'); while(R4==0); __delay_ms(200); }

    // Column 2 scan
    C1=1; C2=0; C3=1;
    if (R1==0){ lcd_data('2'); while(R1==0); __delay_ms(200); }
    if (R2==0){ lcd_data('5'); while(R2==0); __delay_ms(200); }
    if (R3==0){ lcd_data('8'); while(R3==0); __delay_ms(200); }
    if (R4==0){ lcd_data('0'); while(R4==0); __delay_ms(200); }

    // Column 3 scan
    C1=1; C2=1; C3=0;
    if (R1==0){ lcd_data('3'); while(R1==0); __delay_ms(200); }
    if (R2==0){ lcd_data('6'); while(R2==0); __delay_ms(200); }
    if (R3==0){ lcd_data('9'); while(R3==0); __delay_ms(200); }
    if (R4==0){ lcd_data('#'); while(R4==0); __delay_ms(200); }

    // Set all columns back to HIGH
    C1=1; C2=1; C3=1;
}
