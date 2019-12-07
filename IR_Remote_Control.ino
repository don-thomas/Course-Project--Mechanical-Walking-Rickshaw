// Author: Don Thomas
// Created : Year 2017


// The libraries needed for this Project
#include <IRremote.h> // You might have to download this library
#include <Servo.h>

//The pins in the dc motor and the servo pin 
int servoPin = 9;
int In1 = 7;
int In2 = 8;
int ENA = 6;

//Angle of 50 is the middle of the servo in our design
int servoAngle = 50;
int motorSpeed = 0;
Servo myservo;

//These conditions will determine the forward and backward motion
boolean goingForward = false;
boolean goingBack = false;

// The IR Recevier Pin.
int RECV_PIN = 11;

//These are hexadecimal value of the button pressed in the remote to be used to 
// control the decesion of the ardunio
#define Button5 0x20DFA857 // Stop everything and reset
#define Button5_2 0xFF38C7 // Stop everything and reset

#define Button2 0x20DF48B7 // Move Forward
#define Button2_2 0xFF18E7 // Move Forward

#define Button8 0x20DF18E7 // Move Backward
#define Button8_2 0xFF4AB5 // Move Backward

#define Button4 0x20DF28D7 // Turn left
#define Button4_2 0xFF10EF // Turn left

#define Button6 0x20DF6897 //Turn Right
#define Button6_2 0xFF5AA5 //Turn Right

// The IR Recevier Object is created and instailzed 
IRrecv irrecv(RECV_PIN);
//This will keep the information stored from the IR Pulse
decode_results results;

//This method is used to make it go forward 
void goFront() {
  if (goingForward != true) {
    goingForward = true;
    motorSpeed = 140;
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);

  }
}

//This is to make in go Back
void goBack() {
  if (goingBack != true) {
    goingBack = true;
    motorSpeed = 140;
    digitalWrite(In1, LOW);
    digitalWrite(In2, HIGH);

  }

}

//This will stop the forward and backwards motion
void stopMotion() {
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  goingForward = false;
  goingBack = false;
  motorSpeed = 0;
}


//This method will make it turn Right
void turnRight() {
  if (servoAngle < 75) {
    servoAngle += 25;
    myservo.write(servoAngle);
  }
}

//This Method will turn the leg left
void turnLeft() {
  if (servoAngle > 25) {
    servoAngle -= 25;
    myservo.write(servoAngle);
  }
}

// This will increase the speed of the motor 
void speedUp(){
  if(motorSpeed<255){
    motorSpeed+=10;
  }
}

// This will decrease the speed of the motor
void speedDown(){
  if(motorSpeed>105){
    motorSpeed-=10;
  }
}

//This code will only run once
void setup()
{
  //This will tell which pin the servo Control Pin is connected
  myservo.attach(servoPin);
  //Now the IR Recevier will IR Pulse
  irrecv.enableIRIn();

  // These motor pins are for outputs.
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(ENA, OUTPUT);

  //This will set the first angle of the servo
  myservo.write(servoAngle);
}

//This is the main loop of the program
void loop() {

  // If there is any results from the Recevier
  if (irrecv.decode(&results))
  {

    /*
     * All of the 'if' statement is for different buttons being pressed 
     */
     
    if (results.value == Button5 || results.value == Button5_2)
    {
      stopMotion();
    }
    else if (results.value == Button2 || results.value == Button2_2)
    {
      if (goingForward == goingBack) {
        goFront();
      }
      else if (goingForward == true || goingBack == true) {
        speedUp();
      }

    }
    else if (results.value == Button8 || results.value == Button8_2)
    {
      if (goingForward == goingBack) {
        goBack();
      }
      else if (goingForward == true || goingBack == true) {
        speedDown();
      }
    }
    else if (results.value == Button4 || results.value == Button4_2)
    {
      turnLeft();
    }
    else if (results.value == Button6 || results.value == Button6_2)
    {
      turnRight();
    }

    //Reset the motor Speed
    analogWrite(ENA, motorSpeed);
    irrecv.resume();
  }
}
