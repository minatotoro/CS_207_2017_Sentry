#include <Servo.h>

Servo xServo;
Servo yServo;
Servo trigger;

const int X_SERVO = 8;
const int Y_SERVO = 9;
const int T_SERVO = 10;

const int L_BUTTON = 4;
const int R_BUTTON = 5;
const int U_BUTTON = 2;
const int D_BUTTON = 3;
const int T_BUTTON = 6;

bool lPushed = false;
bool rPushed = false;
bool uPushed = false;
bool dPushed = false;
bool tPushed = false;

int xpos = 90;
int ypos = 90;
int tpos = 90;

void fire();
void setXpos(int &val);
void setYpos(int &val);
void readButtons(bool &lButton, bool &rButton, bool &uButton, bool &dButton, bool &fButton);
  
void setup() {
  // put your setup code here, to run once:
  xServo.attach(X_SERVO);
  yServo.attach(Y_SERVO);
  trigger.attach(T_SERVO);

  xServo.write(xpos);
  yServo.write(ypos);
  trigger.write(tpos);

  pinMode(L_BUTTON,INPUT_PULLUP);
  pinMode(R_BUTTON,INPUT_PULLUP);
  pinMode(U_BUTTON,INPUT_PULLUP);
  pinMode(D_BUTTON,INPUT_PULLUP);
  pinMode(T_BUTTON,INPUT_PULLUP);
  Serial.begin (9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  /*
  for(int pos = 10; pos < 170; pos +=5)
  {
    xServo.write(pos);
    delay(50);
  }
  for(int pos = 170; pos > 10; pos -=5)
  {
    xServo.write(pos);
    delay(50);
  }
  */

  readButtons(lPushed, rPushed, uPushed, dPushed, tPushed);

  if(lPushed)
    xpos -=5;
  if(rPushed)
    xpos += 5;
  if(uPushed)
    ypos -= 5;
  if(dPushed)
    ypos += 5;
  if(tPushed)
    fire();
  
  if (xpos > 180)
    xpos = 180;
  if (xpos < 0)
    xpos = 0;
  if (ypos > 180)
    ypos = 180;
  if (ypos < 0)
    ypos = 0;

  xServo.write(xpos);
  yServo.write(ypos);
  
  
  lPushed = false;
  rPushed = false;
  uPushed = false;
  dPushed = false;
  tPushed = false;
  
  Serial.print("x: ");
  Serial.println(xpos);
  Serial.print("y: ");
  Serial.println(ypos);
  delay(100);
}

void readButtons(bool &lButton, bool &rButton, bool &uButton, bool &dButton, bool &fButton)
{
  lButton = (digitalRead(L_BUTTON) == LOW)? true: false;
  rButton = (digitalRead(R_BUTTON) == LOW)? true: false;
  uButton = (digitalRead(U_BUTTON) == LOW)? true: false;
  dButton = (digitalRead(D_BUTTON) == LOW)? true: false;
  fButton = (digitalRead(T_BUTTON) == LOW)? true: false;
  
}

void fire()
{
  trigger.write(0);
  delay(175);
  trigger.write(80);
  Serial.println("Fire");
}


