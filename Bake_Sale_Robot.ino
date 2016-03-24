/*
 - - - BAKE SALE ROBOT MASTER CODE - - -

 Written by Matthew McClain, Josh Kramer, and Tyler Kim

 TO DO:
 -Code capacitive sensors
 -Write three if statements to check if each capacitive sensor has been touched
 -Code specific response for each capacitive sensor
 -Write functions for redundant code (code which would be identical in multiple
  different places)
 -ADVANCED: Code interrupts for calibration or emergency shutdowns
*/

// LIBRARIES
//#include <Servo.h> // delete when micro test is successful
#include <Stepper.h>

// SETTINGS AND THRESHOLDS
// Stepper motors
const int stepsPerRevolution = 200;
const int armMax = 550; // Number of steps from horizontal to highest point
const int armToChute = 300; // Number of steps from horizontal to chute
Stepper topStepper(stepsPerRevolution, 22, 24, 26, 28);
Stepper bottomStepper(stepsPerRevolution, 23, 25, 27, 29);

// Claw
const int claw = 4; // Pin to transmit claw commands to micro
const int clawNeutralAngle = 80;
const int clawOpenAngle = 145; // HIGH
const int clawClosedAngle = 115; // LOW
//Servo clawServo; delete soon

// Buttons
const int cookiebuttonpin = 10;
const int muffinbuttonpin = 11;
const int donutbuttonpin = 12;
const int debounce = 20;


void setup() {
  Serial.begin(9600); //delete in final code
  
  // Stepper motors
  //topStepper.step(-armMax); //delete soon
  topStepper.setSpeed(30); //speed measured in RPM
  bottomStepper.setSpeed(10);
  
  // Claw
  pinMode(claw, OUTPUT);
  digitalWrite(claw, LOW); //tell micro to close claw

  // Buttons
  pinMode(cookiebuttonpin, INPUT);
  pinMode(muffinbuttonpin, INPUT);
  pinMode(donutbuttonpin, INPUT);

  // Test piezoelectric buzzer
  pinMode(6, OUTPUT);
  analogWrite(6, 128);
  delay(1000);
  analogWrite(6, 0);
  
}

void loop() {
  // Left chute
  if (digitalRead(cookiebuttonpin) == LOW) {
    delay(debounce); // Confirms button has been pressed only once
    if (digitalRead(cookiebuttonpin) == LOW) {
      Serial.println("cookieLOW");
      rotateArm(-150);
    }
    else {
      Serial.println("cookieHigh");
    }
  }

  // Back chute
  if (digitalRead(muffinbuttonpin) == LOW) {
    delay(debounce); // Confirms button has been pressed only once
    if (digitalRead(muffinbuttonpin) == LOW) {
      Serial.println("muffinLOW");
      rotateArm(-300);
    }
    else {
      Serial.println("muffinHIGH");
    }
  }

  // Right chute
  if (digitalRead(donutbuttonpin) == LOW) {
    delay(debounce); // Confirms button has been pressed only once
    if (digitalRead(donutbuttonpin) == LOW) {
      Serial.println("donutLOW");
      rotateArm(150);
    }
    else {
      Serial.println("donutHIGH");
    }
  }
}

void rotateArm(int steps) {
  //go to position
  testing(); // no problem
  topStepper.step(armMax);
  testing(); //stops here
  bottomStepper.step(steps);
  //getCup();
  // return to start
  bottomStepper.step(-steps);
  topStepper.step(-armMax);
  // drop cup
  digitalWrite(claw, HIGH); // tell micro to open claw
  delay(1000);
  digitalWrite(claw, LOW); // tell micro to close claw
}

void getCup() {
  digitalWrite(claw, HIGH); // tell micro to open claw
  topStepper.step(-(armMax - armToChute)); // move arm to level of chute
  digitalWrite(claw, LOW); // tell micro to close claw
  topStepper.step((armMax - armToChute)); // move arm back to armMax
}








// Old Functions (to delete)

void CookieAction() {
  const int dist = -150;
  //go to position
  topStepper.step(armMax);
  bottomStepper.step(dist);
  getCup();
  //return to start
  bottomStepper.step(-dist);
  topStepper.step(-armMax);

}

void MuffinAction() {
  const int dist = -300;
  //go to position
  topStepper.step(armMax);
  bottomStepper.step(dist);
  getCup();
  //return to start
  bottomStepper.step(-dist);
  topStepper.step(-armMax);
}

void DonutAction() {
  /*
  const int dist = 150;
  //go to position
  topStepper.step(armMax);
  bottomStepper.step(dist);
  getCup();
  //return to start
  bottomStepper.step(-dist);
  topStepper.step(-armMax);
  */ //BASIC CLAW TESTING
  digitalWrite(claw, HIGH); // tell micro to open claw
  delay(1000);
  digitalWrite(claw, LOW); // tell micro to close claw
  delay(1000);
  //
}




void testing() {
  delay(500);
  digitalWrite(claw, HIGH);
  delay(500);
  digitalWrite(claw, LOW);
  delay(500);
  
  /*claw button command testing
  while (digitalRead(donutbuttonpin) == LOW) {
        digitalWrite(claw, HIGH);
        delay(500);
      }
      digitalWrite(claw, LOW);
      
  //BASIC CLAW TESTING
  digitalWrite(claw, HIGH); // tell micro to open claw
  delay(1000);
  digitalWrite(claw, LOW); // tell micro to close claw
  delay(1000);
  /*buttonState1 = digitalRead(cookiebuttonpin);
  buttonState2 = digitalRead(muffinbuttonpin);
  buttonState3 = digitalRead(donutbuttonpin);
  if(digitalRead(cookiebuttonpin) == HIGH){
  Serial.println("cookie");
  }
  if(digitalRead(muffinbuttonpin) == HIGH){
  Serial.println("muffin");
  }
  if(digitalRead(donutbuttonpin) ==  HIGH){
  Serial.println("Donut");
  }
  /* if(buttonState1 >= 20){
  Serial.println(buttonState1);
  Serial.println("1");

  }
  if(buttonState2 >= 20){
  Serial.println(buttonState2);
  Serial.println("2");
  }
  if(buttonState3 >= 20){
  Serial.println(buttonState3);
  Serial.println("3");
  }
*/
}
