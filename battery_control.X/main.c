// PIC16F877A Configuration Bit Settings

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

// Function Prototypes
void initLCD(void);
void lcd_command(unsigned char);
void lcd_data(unsigned char);
void lcd_output(float);
void delay_ms(unsigned int);

// Global Variables
//unsigned char displayBuffer[6];  // Buffer to store converted digits
//unsigned int num1 = 100, num2 = 200, sum;
void keyscan();
//OPTION_REG &= ~(1 << 7);
//or OPTION_REG &=0x7F;
//0 ->Pull up enabled 1-> pull up disabled
//INTCONbits_t.RBPU = 0; // ? Enable PORTB internal pull-up resistors
unsigned char array[15]={"BAT volt:    V"};
unsigned char arr1[15]={"BAT LOW"};
unsigned char arr2[15]={"BAT MEDIUM"};
unsigned char arr3[15]={"BAT HIGH"};
unsigned char X,m,n,value;
unsigned int i,d1,d2,d3,d4;
float j=15.5;
int main() {
    initLCD();  // Initialize LCD

    //sum = num1 + num2;  // Perform addition
    while(1){
        keyscan();
    }
    
}
void checking(){
    lcd_command(0xC0);
    for(int i = 0; i < 16; i++) lcd_data(' '); // Clear line

    lcd_command(0xC0); // Reset cursor to beginning of line
    if(j>15.5 &&j<=17.5){
        lcd_command(0xC0);
        for(int i=0;i<7;i++){
            lcd_data(arr1[i]);
        }
    }
    if(j>17.5 &&j<=20.5){
        lcd_command(0xC0);
        for(int i=0;i<10;i++){
            lcd_data(arr2[i]);
        }
    }
    if(j>20.5 &&j<=27.5){
        lcd_command(0xC0);
        for(int i=0;i<8;i++){
            lcd_data(arr3[i]);
        }
    }
}

// Initialize LCD in 8-bit mode
void initLCD(void) {
    //OPTION_REG &= ~(1 << 7);  // Enable PORTB pull-ups (RBPU = 0)
    TRISC = 0x00; // Set PORTC as output (Control Pins)
    TRISD = 0x00; // Set PORTD as output (Data Pins)
    TRISB =0xF0;
    PORTB=0xF0;
    // LCD Initialization Sequence
    lcd_command(0x38); // 8-bit mode, 2-line display, 5x8 font
    __delay_ms(5);
    lcd_command(0x0C); // Display ON, Cursor OFF
    __delay_ms(5);
    lcd_command(0x06); // Entry mode: Auto-increment cursor
    __delay_ms(5);
    lcd_command(0x01); // Clear display
    __delay_ms(5);
}

// Send command to LCD
void lcd_command(unsigned char cmd) {
    PORTC &= ~0x08; // RS = 0 (Command mode)
    PORTD = cmd;    // Send command to data port
    PORTC |= 0x01;  // Enable pulse
    __delay_ms(1);
    PORTC &= ~0x01; // Disable pulse
    __delay_ms(2);
}

// Send data to LCD
void lcd_data(unsigned char data) {
    PORTC |= 0x08;  // RS = 1 (Data mode)
    PORTD = data;   // Send data to LCD
    PORTC |= 0x01;  // Enable pulse
    __delay_ms(1);
    PORTC &= ~0x01; // Disable pulse
    __delay_ms(2);
}

// Convert integer to LCD displayable format
void lcd_output(float value) {
//    unsigned char index = 0;
//
//    if (value == 0) { 
//        lcd_data('0'); // If value is zero, print directly
//        return;
//    }
//
//    while (value > 0) {
//        array[index++] = (value % 10) + '0'; // Convert integer to ASCII
//        value /= 10;
//    }
//
//    while (index > 0) {
//        lcd_data(array[--index]); // Print in correct order
//    }
    //typecasting
//    d4=(unsigned char)(i/1000);
//    d3=(unsigned char)((i-(d4*1000))/100);
//    d2=(unsigned char)((i-(d4*1000)-(d3*100))/10);
//    d1=(unsigned char)((i-(d4*1000)-(d3*100)-(d2*10)));
//    lcd_command(0x88);
//    lcd_data(0x30+d4);
//    //fucking asci change
//    lcd_command(0x89);
//    lcd_data(0x30+d3);
//    lcd_command(0x8A);
//    lcd_data(0x30+d2);
//    lcd_command(0x8B);
//    lcd_data(0x30+d1);
    unsigned int int_part = (unsigned int)value;  // Extract integer part
    unsigned int decimal_part = (unsigned int)((value - int_part) * 10);  // Extract decimal part

    lcd_command(0x88);
    lcd_data(int_part / 10 + '0');  // Tens place
    lcd_data(int_part % 10 + '0');  // Units place
    lcd_data('.');                  // Decimal point
    lcd_data(decimal_part + '0');   // Decimal place

}

// Simple delay function
void delay_ms(unsigned int count) {
    //while (--count);
    for(int i=0;i<count;i++){
       //pass
    }
}

void keyscan()
{
    value=PORTB &0xF0;
    //to omit any values in lower digits
    //rb 4 5 6 7--> output
    //pull up registers]
    switch(value){
        case 0xE0:
            __delay_ms(100); // Debounce delay
            lcd_command(0x80);
            //pressed RB4
            for(unsigned int x=0;x<9;x++){
                //as the characters start after the 9th location
                lcd_data(array[x]);
                //printing the stupid values fromm the stupid array
            }
            lcd_command(0x8C);
            for(unsigned int x=13;x<15;x++){
                lcd_data(array[x]);
                //after that replace the space with fucking values
            }
            lcd_command(0x88);
            //point that fked up location
            lcd_output(j);
            //default output as 000
            checking();
            break;
        case 0xD0:
            __delay_ms(100); // Debounce delay
            j+=0.1;
            if(j>27.5){
                j=27.5;
            }
            lcd_command(0x88);
            lcd_output(j);
            //increment j and display it as output
            checking();
            break;
        case 0xB0:
            __delay_ms(100); // Debounce delay
            j-=0.1;
            if(j<15.5){
                j=15.5;
            }
            lcd_command(0x88);
            lcd_output(j);
            checking();
            break;
        case 0x70:
            __delay_ms(100); // Debounce delay
            j=15.5;
            lcd_command(0x88);
            //reset value of j
            lcd_output(j);
            checking();
            break;
    }
}

