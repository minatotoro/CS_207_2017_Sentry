#include <Servo.h>

Servo HServo;
const int LbuttonPin = 3;
const int RbuttonPin = 4;
const int HservoPin = 9;

const int LServoLim = -127;
const int RServoLim = 127;

int HorzPos = 0;

int LbuttonState = 0;
int RbuttonState = 0;

void setup() {
  // put your setup code here, to run once:
pinMode(LbuttonPin, INPUT);
HServo.attach(HservoPin);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  LbuttonState = digitalRead(LbuttonPin);
  RbuttonState = digitalRead(RbuttonPin);

  while (LbuttonState == 1){
    if (HorzPos > LServoLim){
    HorzPos--;
    HServo.write(HorzPos);
    }
    LbuttonState = digitalRead(LbuttonPin);
  }
   while (RbuttonState == 1){
    if (HorzPos < RServoLim){
    HorzPos++;
    HServo.write(HorzPos);
    }
    RbuttonState = digitalRead(RbuttonPin);
  }
}
