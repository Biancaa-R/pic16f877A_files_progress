#define LED 3
#define BUTTON 2

void setup() {
  // put your setup code here, to run once:
  pinMode(LED,OUTPUT);
  pinMode(BUTTON,INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned char val;
  val= digitalRead(BUTTON);
  if(val==0){
    digitalWrite(LED,HIGH);
  }
  else{
    digitalWrite(LED,LOW);
  }
}
