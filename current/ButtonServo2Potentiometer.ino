/**
 *  CS207 Winter 2017 Final Project - Paintball Sentry
 *  
 *  Members:
 *    -Russell Tagle
 *    -Richard Sipley
 *    -Brandon Peterson
 *  Our Github:
 *    https://github.com/ruckers10/CS_207_2017_Sentry
 *  
 *  An potentiometer/button controlled paintball sentry.
 *  
 *  Parts: 
 *    3 Servos
 *      -2 Hitec HS-645MG Servos for a torque and base
 *      -1 Hitec HS-311 for trigger (trigger works better with a stronger servo like the HS-645MG)
 *    2 potentiometers
 *    1 or 5 pushbuttons
 *    4 AA's or 6V power supply for the servos
 *    Arduino Uno R3
 *    
 *  Notes:
 *    Servo range is from 0 - 180 degrees
 *    Check the circuit diagram to see how the parts are wired
 *
 *    x axis servo - pin 8
 *    y axis servo - pin 9
 *    trigger servo - pin 10
 *
 *    x axis potentiometer pin - A0
 *    y axis potentiometer pin - A1
 *    trigger button pin - 6
 *
 *    if using buttons,
 *    up button pin - 2
 *    down button pin - 3
 *    left button pin - 4
 *    right button pin - 5
 */
#include <Servo.h>

//Servo Objects
Servo xServo; //base servo
Servo yServo; //arm servo
Servo trigger;  //trigger servo

//Servo Pins
const int X_SERVO = 8;
const int Y_SERVO = 9;
const int T_SERVO = 10;
/*
//Button Pins - Uncomment for buttons
const int L_BUTTON = 4;
const int R_BUTTON = 5;
const int U_BUTTON = 2;
const int D_BUTTON = 3;*/
const int T_BUTTON = 6;

//Potentiometer Pins
const int lPot = A0;
const int rPot = A1;

/*
 //Button Pins - Uncomment for buttons
bool lPushed = false;
bool rPushed = false;
bool uPushed = false;
bool dPushed = false;*/
bool tPushed = false;

//Initial Position of the servos
unsigned int xpos = 90;
unsigned int ypos = 90;
int tpos = 90;

//Function Prototypes
void fire();            //pull trigger
//void readButtons(bool &lButton, bool &rButton, bool &uButton, bool &dButton, bool &tButton);
void readPots(unsigned int &left, unsigned int &right, bool &tButton);
  
void setup() {
  // put your setup code here, to run once:
  xServo.attach(X_SERVO);
  yServo.attach(Y_SERVO);
  trigger.attach(T_SERVO);

  xServo.write(xpos);
  yServo.write(ypos);
  trigger.write(tpos);
  
  /*
  pinMode(L_BUTTON,INPUT_PULLUP);
  pinMode(R_BUTTON,INPUT_PULLUP);
  pinMode(U_BUTTON,INPUT_PULLUP);
  pinMode(D_BUTTON,INPUT_PULLUP);*/
  pinMode(T_BUTTON,INPUT_PULLUP);
  Serial.begin (9600);
}

void loop() {
  //Servo sweep test
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

  //readButtons(lPushed, rPushed, uPushed, dPushed, tPushed); //buttons
  readPots(xpos, ypos, tPushed);  //potentiometers

  /*//Uncomment for buttons
  if(lPushed)
    xpos -=5;
  if(rPushed)
    xpos += 5;
  if(uPushed)
    ypos -= 5;
  if(dPushed)
    ypos += 5; */
  if(tPushed)
    fire();
  
  
  if (xpos > 180)
    xpos = 180;
  if (xpos < 0)
    xpos = 0;
  if (ypos > 145)
    ypos = 145;
  if (ypos < 0)
    ypos = 0;

  xServo.write(xpos);   //translate values to servo positions
  yServo.write(ypos);
  
  /*//Reset push buttons to false
  lPushed = false;
  rPushed = false;
  uPushed = false;
  dPushed = false;*/
  tPushed = false;

  //Output servo position values
  Serial.print("x: ");
  Serial.println(xpos);
  Serial.print("y: ");
  Serial.println(ypos);
  delay(150);
}

/*
 * Read button values
 * Arguments:
 * lButton - set true if button was pushed
 * rButton - set true if button was pushed
 * uButton - set true if button was pushed
 * dButton - set true if button was pushed
 * tButton - set true if button was pushed
 *//*
void readButtons(bool &lButton, bool &rButton, bool &uButton, bool &dButton, bool &tButton)
{
  lButton = (digitalRead(L_BUTTON) == LOW)? true: false;
  rButton = (digitalRead(R_BUTTON) == LOW)? true: false;
  uButton = (digitalRead(U_BUTTON) == LOW)? true: false;
  dButton = (digitalRead(D_BUTTON) == LOW)? true: false;
  tButton = (digitalRead(T_BUTTON) == LOW)? true: false;
  
}*/

/*
 * Pull the trigger
 * Servo limited from 0 to 80 degrees for trigger
 */
void fire()
{
  trigger.write(0);
  delay(175);
  trigger.write(80);
  Serial.println("Fire"); //output if firing
}

/*
 * Read potentiometer values and translate them into servo positions
 * Arguments:
 * left - variable x position of servo
 * right - variable for y position of servo
 * tButton - boolean value that decides to execute fire() function
 */
void readPots(unsigned int &left, unsigned int &right, bool &tButton)
{
  double fLeft = 0;   //double conversion needed for calculation
  double fRight = 0;
  fLeft = analogRead(lPot);
  fLeft *= 180.0;
  fLeft /= 1023.0;
  left = (int) fLeft;

  fRight = analogRead(rPot);  //set the range of yServo from 0 - 145 degrees so it dosn't point straight down into base
  fRight *= 145.0;
  fRight /= 1023;
  right = (int) fRight;

  //monitor raw values of pots
  //Serial.println(analogRead(lPot));
  //Serial.println(analogRead(rPot));
  
  tButton = (digitalRead(T_BUTTON) == LOW)? true: false;  //set true if button is pushed, false otherwise
}

