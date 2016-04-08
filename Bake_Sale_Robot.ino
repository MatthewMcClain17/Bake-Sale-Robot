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
const int armToChute = 300; // Number of steps from horizontal to chute elevation
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


void setup() {
  // Stepper motors
  topStepper.setSpeed(30); // speed measured in RPM
  bottomStepper.setSpeed(10);
  
  // Claw
  clawServo.attach(claw);
  clawServo.write(clawNeutralAngle); // starting position

  // Buttons
  pinMode(leftButton, INPUT);
  pinMode(centerButton, INPUT);
  pinMode(rightButton, INPUT);

  // Calibration
  // Hold all three buttons down on startup to activate
  if (digitalRead(leftButton) == HIGH
  && digitalRead(centerButton) == HIGH
  && digitalRead(rightButton) == HIGH) {
    delay(debounce);
    
    if (digitalRead(leftButton) == HIGH
    && digitalRead(centerButton) == HIGH
    && digitalRead(rightButton) == HIGH) {
      calibrate();
    }
  }
  
}

void loop() {
  // Left chute
  if (digitalRead(leftButton) == LOW) {
    delay(debounce); // confirms button has been pressed only once
    if (digitalRead(leftButton) == LOW) {
      rotateArm(-150);
    }
  }

  // Back chute
  if (digitalRead(centerButton) == LOW) {
    delay(debounce); // confirms button has been pressed only once
    if (digitalRead(centerButton) == LOW) {
      rotateArm(-300);
    }
  }

  // Right chute
  if (digitalRead(rightButton) == LOW) {
    delay(debounce); // confirms button has been pressed only once
    if (digitalRead(rightButton) == LOW) {
      rotateArm(150);
    }
  }
}

// FUNCTIONS

void rotateArm(int steps) {
  // go to position
  topStepper.step(armMax);
  bottomStepper.step(steps);
  getCup();
  // return to start
  bottomStepper.step(-(steps));
  topStepper.step(-(armMax - dropPosition)); // lower to drop position
  delay(1000);
  // drop cup
  clawServo.write(clawOpenAngle); // open claw, dropping the cup
  delay(1000);
  clawServo.write(clawNeutralAngle); // set to neutral starting position
  topStepper.step(-dropPosition); // lower to horizontal starting position
}

void getCup() {
  delay(500);
  clawServo.write(clawOpenAngle); // open claw
  delay(500);
  topStepper.step(-(armMax - armToChute)); // move arm to level of chute
  delay(500);
  clawServo.write(clawClosedAngle); // close claw
  delay(500);
  topStepper.step(armMax - armToChute); // move arm back to armMax
}


void calibrate() {
  // Used to line up chutes with claw. Press center button to advance.
  // Local variables
  const int steps = 150;
  boolean escape = false;
  
  clawServo.write(clawOpenAngle); // open claw
  
  // go to left position
  topStepper.step(armMax); // raise arm
  bottomStepper.step(-steps);
  topStepper.step(-(armMax - armToChute)); // lower arm
  
  // wait until center button is pressed
  do {
    if (digitalRead(centerButton) == LOW) {
    delay(debounce); // confirms button has been pressed only once
    if (digitalRead(centerButton) == LOW) {
      escape = true;
      }
    }
  } while (escape = false);

  // go to center position
  topStepper.step(armMax - armToChute); // return arm to armMax
  bottomStepper.step(-steps);
  topStepper.step(-(armMax - armToChute)); // lower arm
  
  // wait until center button is pressed
  do {
    if (digitalRead(centerButton) == LOW) {
    delay(debounce); // confirms button has been pressed only once
    if (digitalRead(centerButton) == LOW) {
      escape = true;
      }
    }
  } while (escape = false);

  // go to right position
  topStepper.step(armMax - armToChute); // return arm to armMax
  bottomStepper.step(3 * steps);
  topStepper.step(-(armMax - armToChute)); // lower arm

  // wait until center button is pressed
  do {
    if (digitalRead(centerButton) == LOW) {
    delay(debounce); // confirms button has been pressed only once
    if (digitalRead(centerButton) == LOW) {
      escape = true;
      }
    }
  } while (escape = false);

  // return to start
  topStepper.step(armMax - armToChute); // return arm to armMax
  bottomStepper.step(-steps);
  topStepper.step(-armMax);
}

// Testing Functions

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
