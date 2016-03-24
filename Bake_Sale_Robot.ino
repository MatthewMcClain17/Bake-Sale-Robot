/*
 - - - BAKE SALE ROBOT MASTER CODE - - -

 Written by Matthew McClain, Josh Kramer, Noah Thomas, and Tyler Kim

 TO DO:
 -Delete last remaining Micro commands
 -Name the robot
 -Clean up unneccesary portions of code
 -ADVANCED: Code interrupts for calibration or emergency shutdowns
*/

// LIBRARIES
#include <Servo.h>
#include <Stepper.h>

// SETTINGS AND THRESHOLDS
// Stepper motors
const int stepsPerRevolution = 200; // Number of steps per revolution for steppers used
const int armMax = 550; // Number of steps from horizontal to highest arm elevation
const int armToChute = 300; // Number of steps from horizontal to chute elevation
Stepper topStepper(stepsPerRevolution, 22, 24, 26, 28);
Stepper bottomStepper(stepsPerRevolution, 23, 25, 27, 29);

// Claw
const int claw = 4;
const int clawNeutralAngle = 80;
const int clawOpenAngle = 145; // HIGH
const int clawClosedAngle = 115; // LOW
Servo clawServo;

// Buttons
const int cookiebuttonpin = 10;
const int muffinbuttonpin = 11;
const int donutbuttonpin = 12;
const int debounce = 20;


void setup() {
  // Stepper motors
  //topStepper.step(-armMax); //delete soon
  topStepper.setSpeed(30); //speed measured in RPM
  bottomStepper.setSpeed(10);
  
  // Claw
  clawServo.attach(claw);
  clawServo.write(clawNeutralAngle); // Starting position

  // Buttons
  pinMode(cookiebuttonpin, INPUT);
  pinMode(muffinbuttonpin, INPUT);
  pinMode(donutbuttonpin, INPUT);

  // Test piezoelectric buzzer – remove after servo issue is dealt with
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
      rotateArm(-150);
    }
  }

  // Back chute
  if (digitalRead(muffinbuttonpin) == LOW) {
    delay(debounce); // Confirms button has been pressed only once
    if (digitalRead(muffinbuttonpin) == LOW) {
      rotateArm(-300);
    }
  }

  // Right chute
  if (digitalRead(donutbuttonpin) == LOW) {
    delay(debounce); // Confirms button has been pressed only once
    if (digitalRead(donutbuttonpin) == LOW) {
      rotateArm(150);
    }
  }
}

void rotateArm(int steps) {
  //go to position
  testing(); // delete soon
  topStepper.step(armMax);
  testing();
  bottomStepper.step(steps);
  getCup();
  // return to start
  bottomStepper.step(-steps);
  topStepper.step(-armMax);
  // drop cup
  clawServo.write(clawOpenAngle);
  delay(500);
  clawServo.write(clawNeutralAngle);
  /*
  digitalWrite(claw, HIGH); // tell micro to open claw
  delay(1000);
  digitalWrite(claw, LOW); // tell micro to close claw
  */
}

void getCup() {
  //digitalWrite(claw, HIGH); // tell micro to open claw
  clawServo.write(clawOpenAngle);
  topStepper.step(-(armMax - armToChute)); // move arm to level of chute
  //digitalWrite(claw, LOW); // tell micro to close claw
  clawServo.write(clawClosedAngle);
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
  clawServo.write(clawNeutralAngle);
  delay(500);
  clawServo.write(clawOpenAngle);
  delay(500);
  clawServo.write(clawClosedAngle);
  delay(500);
  clawServo.write(clawNeutralAngle);
  /*
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
