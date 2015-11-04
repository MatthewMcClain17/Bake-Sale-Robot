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
#include <Servo.h>
#include <Stepper.h>
#include <CapacitiveSensor.h> //make sure you have this installed, found at:
//http://playground.arduino.cc/Main/CapacitiveSensor?from=Main.CapSense


// SETTINGS AND THRESHOLDS
const int distSensor = 7; //Infrared distance sensor signal pin
const int stepsPerRevolution = 200;  // number of steps per revolution for our motors
// Stepper motor fixed movement angles
const int armMax = -650; // Move arm above the chute to its maximum height
const int armToChute = 200; // Move arm to height of chute
const int true90 = 70; // Value that actually moves bottom stepper 90 degrees clockwise
// Servo limits – to prevent the claw from breaking itself, stay near these angles
const int clawNeutralAngle = 100;
const int clawOpenAngle = 145;
const int clawClosedAngle = 115;
// Capacitive sensor activation thresholds
const int cookieThreshold = 100;
const int donutThreshold = 100;
const int muffinThreshold = 100;
const int distSenseThreshold = 500; // Distance sensor hand sensing threshold


// OBJECT INITIALIZATION
// initialize capacitive sensors
CapacitiveSensor Cookie = CapacitiveSensor(48, 49); // Green wire?
CapacitiveSensor Donut = CapacitiveSensor(50, 51); // Red wire?
CapacitiveSensor Muffin = CapacitiveSensor(52, 53); // Black wire?
// initialize stepper motors
Stepper topStepper(stepsPerRevolution, 22, 24, 26, 28);
Stepper bottomStepper(stepsPerRevolution, 23, 25, 27, 29);
// initialize claw servo
Servo clawServo;



void setup() {
  pinMode(distSensor, INPUT); // set the distance sensor's signal to input

 // set the rpm of the stepper
  topStepper.setSpeed(30);
  bottomStepper.setSpeed(5);
  
  clawServo.attach(4);
  
  /* Put motors in their starting positions
  topStepper.step(-200);*/
  clawServo.write(clawNeutralAngle);

  // initialize the serial port for testing purposes:
  Serial.begin(9600);
}

void loop() {
 // FOR TESTING PURPOSES
   /* Distance sensor testing
  Serial.println(analogRead(distSensor));
  delay(500);
  */
  /* Claw servo testing
  clawServo.write(180);
  delay(1000);
  clawServo.write(100);
  delay(1000);
  */
  /* Stepper testing
  bottomStepper.step(70);
  delay(500);
  bottomStepper.step(-70);
  delay(500);
  */
 
 /*
  if (Cookie.capacitiveSensor(30) > cookieThreshold) {
    action1();
  }

  if (Donut.capacitiveSensor(30) > donutThreshold) {
  action2();
  }

  if (Muffin.capacitiveSensor(30) > muffinThreshold) {
  action3();
  }
  */
}

// FUNCTIONS

void action1() { // CLOCKWISE 90 DEGREES
  clawServo.write(clawNeutralAngle); //set the servo to the neutral position
  topStepper.step(armMax); // decrease elevates; increase brings servo down (+ down, - up?)
  bottomStepper.step(true90); // step 90 degrees clockwise
  clawServo.write(clawOpenAngle); // fully open the claw
  topStepper.step(armToChute); // decrease elevates; increase brings servo down
  bottomStepper.step(true90 / 10); // move the claw to push the cup to the side for easy grabbing
  clawServo.write(clawClosedAngle); // close the claw and grab the item
  
  topStepper.step(-armToChute); // elevate arm to max height again
  bottomStepper.step((-true90) - (true90 / 10)); // return the arm back to the front, accounting for extra nudge
  topStepper.step(-clawOpenAngle); // return arm to its starting angle
  
  if (analogRead(distSensor) > distSenseThreshold) { // if there is a hand above the distance sensor
   delay(100);
   if (analogRead(distSensor) > distSenseThreshold) { // if there is STILL a hand above sensor
    clawServo.write(clawOpenAngle); // open the claw and drop the item
    delay(3000);
    clawServo.write(clawNeutralAngle); // return the claw to its neutral position
   }
  }
  // return to loop and wait for another command
}

void action2() { // CLOCKWISE 180 DEGREES
  clawServo.write(clawNeutralAngle); //set the servo to the neutral position
  topStepper.step(armMax); // decrease elevates; increase brings servo down (+ down, - up?)
  bottomStepper.step(2 * true90); // step 90 degrees clockwise
  clawServo.write(clawOpenAngle); // fully open the claw
  topStepper.step(armToChute); // decrease elevates; increase brings servo down
  bottomStepper.step(true90 / 10); // move the claw to push the cup to the side for easy grabbing
  clawServo.write(clawClosedAngle); // close the claw and grab the item
  
  topStepper.step(-armToChute); // elevate arm to max height again
  bottomStepper.step((-2 * true90) - (true90 / 10)); // return the arm back to the front, accounting for extra nudge
  topStepper.step(-clawOpenAngle); // return arm to its starting angle
  
  if (analogRead(distSensor) > distSenseThreshold) { // if there is a hand above the distance sensor
   delay(100);
   if (analogRead(distSensor) > distSenseThreshold) { // if there is STILL a hand above sensor
    clawServo.write(clawOpenAngle); // open the claw and drop the item
    delay(3000);
    clawServo.write(clawNeutralAngle); // return the claw to its neutral position
   }
  }
  // return to loop and wait for another command
}

void action3() { // COUNTERCLOCKWISE 90 DEGREES
  clawServo.write(clawNeutralAngle); //set the servo to the neutral position
  topStepper.step(armMax); // decrease elevates; increase brings servo down (+ down, - up?)
  bottomStepper.step(-true90); // step 90 degrees clockwise
  clawServo.write(clawOpenAngle); // fully open the claw
  topStepper.step(armToChute); // decrease elevates; increase brings servo down
  bottomStepper.step(-true90 / 10); // move the claw to push the cup to the side for easy grabbing
  clawServo.write(clawClosedAngle); // close the claw and grab the item
  
  topStepper.step(-armToChute); // elevate arm to max height again
  bottomStepper.step(true90 + (true90 / 10)); // return the arm back to the front, accounting for extra nudge
  topStepper.step(-clawOpenAngle); // return arm to its starting angle
  
  if (analogRead(distSensor) > distSenseThreshold) { // if there is a hand above the distance sensor
   delay(100);
   if (analogRead(distSensor) > distSenseThreshold) { // if there is STILL a hand above sensor
    clawServo.write(clawOpenAngle); // open the claw and drop the item
    delay(3000);
    clawServo.write(clawNeutralAngle); // return the claw to its neutral position
   }
  }
  // return to loop and wait for another command
}
