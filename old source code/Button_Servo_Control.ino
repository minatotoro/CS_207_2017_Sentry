#include <Servo.h>
//create servo entity
Servo HServo;
//pin variables
const int LbuttonPin = 3;
const int RbuttonPin = 4;
const int HservoPin = 9;
//Servo limits to allow quick adjustment
const int LServoLim = 0;
const int RServoLim = 180;
//default position and Horizontal Position indicator
int HorzPos = 90;
//Button State variables
int LbuttonState = 0;
int RbuttonState = 0;

void setup() {
//sets pins to read input from buttons
pinMode(LbuttonPin, INPUT);
pinMode(RbuttonPin, INPUT);
//attaches servo to pin
HServo.attach(HservoPin);
HServo.write(HorzPos); //sets servo to default position.
}

void loop() {
  //Reads the button state
  LbuttonState = digitalRead(LbuttonPin);
  RbuttonState = digitalRead(RbuttonPin);

  while (LbuttonState == 1){//checks for button L status
    if (HorzPos > LServoLim){///If button L is push servo rotates left 
    HorzPos--;
    HServo.write(HorzPos);
    delay(10);
    }
    LbuttonState = digitalRead(LbuttonPin); //refreshed button status
  }/
   while (RbuttonState == 1){//checks for button R status
    if (HorzPos < RServoLim){//If button R is push servo rotates right 
    HorzPos++;
    HServo.write(HorzPos);
    delay(10);
    }
    RbuttonState = digitalRead(RbuttonPin);//refreshed button status
  }
}
