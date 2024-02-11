//22493

#include <Servo.h>

const byte LEDPIN = 13; //set LEDPin connected to pin 13
const byte PAW1 = 1; //set PAW1 connected to pin 1 
const byte PAW2 = 2; //set PAW2 connected to pin 2
const byte PAW3 = 3; //set PAW3 connected to pin 3
const byte PAW4 = 4; //set PAW4 connected to pin 4
const byte LEFTEARPIN = 9; //set LEFTEARPIN connected to pin 9
const byte RIGHTEARPIN = 10; // set RIGHTEARPIN connected to pin 10

Servo leftEar;
Servo rightEar;

void setup() {
  pinMode(LEDPIN, OUTPUT); //set LEDPIN as an OUTPUT
  pinMode(PAW1, INPUT); //set PAW1 as an input
  pinMode(PAW2, INPUT); //set PAW2 as an input
  pinMode(PAW3, INPUT); //set PAW3 as an input
  pinMode(PAW4, INPUT); //set PAW4 as an input
  leftEar.attach(LEFTEARPIN); //attach left ear to LEFTEARPIN
  rightEar.attach(RIGHTEARPIN); //attach right ear to RIGHTEARPIN
}

void loop() {
  //IF PAW1 is pressed, then do the following
  if (digitalRead (PAW1) == HIGH){
    digitalWrite (LEDPIN, HIGH);
  }
  //IF PAW2 is pressed, then do the following
  if(digitalRead (PAW2) == HIGH){
    digitalWrite (LEDPIN, LOW);
  }
  //IF PAW3 is pressed, then do the following
  if(digitalRead (PAW3) == HIGH){
    wagEars();
  }
  //IF PAW4 is pressed, then do the following
  if(digitalRead (PAW4) == HIGH){
    blinkingLed();
  }
}

void wagEars(){
  leftEar.write(0);
  leftEar.write(90);
  leftEar.write(0);

  rightEar.write(0);
  rightEar.write(90);
  rightEar.write(0);

  leftEar.write(0);
  rightEar.write(0);
  leftEar.write(90);
  rightEar.write(90);
  leftEar.write(0);
  rightEar.write(0);
}

void blinkingLed(){
  byte randumNumber = radnom(1,3);

  for (int i = 0; i < randomnumber; i++){
    digitalWrite(LEDPIN, HIGH);
    delay(500);
    digitalWrite(LEDPIN, LOW);
    delay(500);
  }
}
