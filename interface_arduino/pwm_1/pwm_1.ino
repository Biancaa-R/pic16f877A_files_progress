#define PWM 9
void setup() {
  // put your setup code here, to run once:
  pinMode(PWM,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int i;
  for(int i=0;i<255;i++){
    analogWrite(PWM,i);
    delay(20);
    //for seeing the waveform orrectly
  }
  for(i=255;i>0;i--){
    analogWrite(PWM,i);
    delay(20);
    //for seeing the waveform orrectly
  }
}
