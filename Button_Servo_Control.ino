#include <Servo.h>

Servo HServo;
const int LbuttonPin = 3;
const int RbuttonPin = 4;
const int HservoPin = 9;

const int LServoLim = 0;
const int RServoLim = 180;

int HorzPos = 90;

int LbuttonState = 0;
int RbuttonState = 0;

void setup() {
  // put your setup code here, to run once:
pinMode(LbuttonPin, INPUT);
HServo.attach(HservoPin);
HServo.write(HorzPos);
}

void loop() {
  // put your main code here, to run repeatedly:
  LbuttonState = digitalRead(LbuttonPin);
  RbuttonState = digitalRead(RbuttonPin);

  while (LbuttonState == 1){
    if (HorzPos > LServoLim){
    HorzPos--;
    HServo.write(HorzPos);
    delay(10);
    }
    LbuttonState = digitalRead(LbuttonPin);
  }
   while (RbuttonState == 1){
    if (HorzPos < RServoLim){
    HorzPos++;
    HServo.write(HorzPos);
    delay(10);
    }
    RbuttonState = digitalRead(RbuttonPin);
  }
}
