/*
 - - - BAKE SALE ROBOT MASTER CODE - - -

 Written by Matthew McClain, Josh Kramer, Noah Thomas, and Tyler Kim

 TO DO:
 -Name the robot
 -ADVANCED: Code interrupts for calibration or emergency shutdowns
*/

// LIBRARIES

#include <Servo.h>
#include <Stepper.h>


// SETTINGS AND THRESHOLDS

// Stepper motors
const int stepsPerRevolution = 200; // Number of steps per revolution for steppers used
const int armMax = 550; // Number of steps from horizontal to highest arm elevation
const int armToChute = 260; // Number of steps from horizontal to chute elevation
const int dropPosition = 200; // Number of steps from horizontal to drop position
const int tuning = 10; // Adjustable value to increase accuracy of rotation
Stepper topStepper(stepsPerRevolution, 22, 24, 26, 28);
Stepper bottomStepper(stepsPerRevolution, 23, 25, 27, 29);

// Claw
const int claw = 4;
const int clawNeutralAngle = 80; // basic position of claw
const int clawOpenAngle = 145; // for preparing to grab cups
const int clawClosedAngle = 115; // for grabbing cups
Servo clawServo;

// Buttons
const int leftButton = 10; // left button (formerly cookie)
const int centerButton = 11; // center button (formerly muffin)
const int rightButton = 12; // right button (formerly donut)
const int debounce = 20; // wait time (in ms) to ensure button has truly been pressed

bool calibrate = false;

void setup() {
  // Stepper motors
  topStepper.setSpeed(30); // speed measured in RPM
  //bottomStepper.setSpeed(10);
  
  // Claw
  clawServo.attach(claw);

  // Buttons
  pinMode(leftButton, INPUT);
  pinMode(centerButton, INPUT);
  pinMode(rightButton, INPUT);

  // Calibration
  // Hold all three buttons down on startup to activate
  if (digitalRead(leftButton) == LOW
  && digitalRead(centerButton) == LOW
  && digitalRead(rightButton) == LOW) {
    delay(debounce);

    // until buttons are released, set calibrate to true
    while (digitalRead(leftButton) == LOW
    && digitalRead(centerButton) == LOW
    && digitalRead(rightButton) == LOW) {
      calibrate = true;
    }
  }
  
  clawServo.write(clawNeutralAngle); // set claw to starting position
}

void loop() {
  // Left chute
  if (digitalRead(leftButton) == LOW) {
    delay(debounce); // confirms button has been pressed only once
    if (digitalRead(leftButton) == LOW) {
      bottomStepper.setSpeed(10);
      rotateArm(-150, 0, 0);
    }
  }

  // Back chute
  if (digitalRead(centerButton) == LOW) {
    delay(debounce); // confirms button has been pressed only once
    if (digitalRead(centerButton) == LOW) {
      bottomStepper.setSpeed(10);
      rotateArm(-300, 0, 0);
    }
  }

  // Right chute – the one that works best
  if (digitalRead(rightButton) == LOW) {
    delay(debounce); // confirms button has been pressed only once
    if (digitalRead(rightButton) == LOW) {
      bottomStepper.setSpeed(10);
      rotateArm(150, 0, 0);
    }
  }
}

// FUNCTIONS

void rotateArm(int steps, int tuning1, int tuning2) {
  // go to position
  topStepper.step(armMax);
  bottomStepper.step(steps + tuning1);
  getCup();
  // return to start
  bottomStepper.step(-(steps + tuning2));
  topStepper.step(-(armMax - dropPosition)); // lower to drop position
  delay(1000);
  // drop cup
  clawServo.write(clawOpenAngle); // open claw, dropping the cup
  delay(1000);
  clawServo.write(clawNeutralAngle); // set to neutral starting position
  delay(200);
  topStepper.step(-dropPosition); // lower to horizontal starting position
}

void getCup() {
  delay(500);
  clawServo.write(clawOpenAngle); // open claw
  delay(500);
  topStepper.step(-(armMax - armToChute)); // move arm to level of chute
  delay(500);
  calibrateClaw();
  clawServo.write(clawClosedAngle); // close claw
  delay(500);
  topStepper.step(armMax - armToChute); // move arm back to armMax
}


void calibrateClaw() {
  // Used to line up chutes with claw. Press center button to advance
  boolean escape = false;
  
  if (calibrate = true) {
    // wait until center button is pressed
    do {
      if (digitalRead(centerButton) == LOW) {
      delay(debounce); // confirms button has been pressed only once
      if (digitalRead(centerButton) == LOW) {
        escape = true;
        }
      }
    } while (escape == false);
  }
}




/* Testing Functions

void clawTesting() { // Tests the claw by setting it to neutral, open, and closed
  clawServo.write(clawNeutralAngle);
  delay(500);
  clawServo.write(clawOpenAngle);
  delay(500);
  clawServo.write(clawClosedAngle);
  delay(500);
  clawServo.write(clawNeutralAngle);
}

void piezoTesting() { // Beeps a piezoelectric buzzer attached to 6 and GND
  pinMode(6, OUTPUT);
  analogWrite(6, 128);
  delay(1000);
  analogWrite(6, 0);
}
*/
