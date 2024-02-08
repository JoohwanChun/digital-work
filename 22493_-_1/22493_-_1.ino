byte ledPin = 13;

const byte LEDPIN = 13; //set LEDPin connected to pin 13
const byte PAW1 = 1; //set PAW1 connected to pin 1 
const byte PAW2 = 2; //set PAW2 connected to pin 2
const byte PAW3 = 3; //set PAW3 connected to pin 3
const byte PAW4 = 4; //set PAW4 connected to pin 4


void setup() {
  pinMode(LEDPIN, OUTPUT); //set LEDPIN as an OUTPUT
  pinMode(PAW1, INPUT); //set PAW1 as an input
  pinMode(PAW2, INPUT); //set PAW2 as an input
  pinMode(PAW3, INPUT); //set PAW3 as an input
  pinMode(PAW4, INPUT); //set PAW4 as an input
}

void loop() {
  //IF PAW1 is pressed, then do the following
  if (digitalRead (PAW1) == HIGH){
    digitalWrite (LEDPIN, HIGH);
  }
  //IF PAW2 is pressed, then do the following
  if(digitalRead (PAW2) == HIGH){
    playMusic();
  }
  //IF PAW3 is pressed, then do the following
  if(digitalRead (PAW3) == HIGH){
    playGame();
  }
  //IF PAW4 is pressed, then do the following
  if(digitalRead (PAW4) == HIGH){
    int score = playGame();
  }
}

void playMusic(){
  //play MP3 file here
}

int playGame(){
  byte score = 99;
  //play simon says game
  return score;
}
