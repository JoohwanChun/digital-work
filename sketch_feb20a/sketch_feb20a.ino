#include<Adafruit_LiquidCrystal.h>
const byte BTNPIN = 13;
const byte PDTPIN = A1;
const byte NOISEPIN = A0;

Adafruit_LiquidCrystal screen(0);

void setup() {
  pinMode (BTNPIN, INPUT);
  pinMode (PDTPIN, INPUT);

  Serial.begin(9600);

  if(!screen.begin (16, 2)){
    Serial.println ("couldn't start the screen? check wiring")
  }
}


void loop(){
  if (digitalRead (BTNPIN) == HIGH) {
    Serial.println ("Rolling Dice");
    int diceType = analogRead (PDTPIN);
    diceType = map(diceType, 0, 1023, 1, 6);
    rollDice (diceType);
    }
}

void rollDice(byte numSides) {
  byte diceRoll = 255;
  switch (numSides) {
    case 1:
    Serial.print ("A 4 sided dice rolls: ");
    diceRoll = random(1,4);
    break;
    case 2:
    Serial.print ("A 6 sided dice rolls: ");
    diceRoll = random(1,6);
    break; 
    case 3:
    Serial.print ("A 8 sided dice rolls: ");
    diceRoll = random(1,8);
    break; 
    case 4:
    Serial.print ("A 12 sided dice rolls: ");
    diceRoll = random(1,12);
    break;  
    case 5:
    Serial.print ("A 16 sided dice rolls: ");
    diceRoll = random(1,16);
    break;
    case 6:
    Serial.print ("A 20 sided dice rolls: ");
    diceRoll = random(1,20);
    break; 
    default:
    Serial.println("Issue with mapping potentiometer values");
    break;
  }
  Serial.println (diceRoll);
}
