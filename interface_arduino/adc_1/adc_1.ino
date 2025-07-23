
// include the library code:
#include <LiquidCrystal.h>
#define ADC A0
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  pinMode(ADC ,INPUT_PULLUP);
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("ADC output:");
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("ADC output:");
  int i = analogRead(ADC);
  lcd.setCursor(0, 1);     // Start at beginning of second row
  lcd.print("ADC: ");      
  lcd.print(i);
  lcd.print("     ");      // To overwrite old digits

  delay(200);              // Small delay for readability
}
  //the value read by the adc pin

