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
// Servo limits – to prevent the claw from breaking itself, stay near these angles
const int clawNeutralAngle = 100;
const int clawOpenAngle = 150;
const int clawClosedAngle = 80;
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

void action1() {

  clawServo.write(clawNeutralAngle); //sets the servo to the neutral position
  topStepper.step(650); // decrease elevates; increase brings servo down
  // step one revolution (stepsPerRevolution = 200) clockwise
  bottomStepper.step(50);
  clawServo.write(clawOpenAngle); // fully opens the claw
  topStepper.step(-250); // decrease elevates; increase brings servo down
  
  clawServo.write(clawClosedAngle);
  
  // step one revolution in the other direction:
  topStepper.step(200);
  bottomStepper.step(-50);
  
  if (analogRead(distSensor) > distSenseThreshold) { // if there is a hand above the distance sensor
   clawServo.write(clawOpenAngle); // open the claw and drop the item
   delay(3000);
   clawServo.write(clawNeutralAngle);
  }
}

void action2() {
   clawServo.write(0); //sets the angle of the servo to 0 degrees
  topStepper.step(650); // decrease elevates; increase brings servo down
  // step one revolution (stepsPerRevolution = 200) clockwise
  bottomStepper.step(100);
  topStepper.step(-250); // decrease elevates; increase brings servo down
  
  clawServo.write(95); //176 is maximum vibration limit, 180 is absolute max
  
  // step one revolution in the other direction:
  topStepper.step(200);
  bottomStepper.step(-100);
  
  Serial.println(analogRead(distSensor)); //FIX THIS!!  
  
  clawServo.write(0); //176 is maximum vibration limit, 180 is absolute max
  
}

void action3() {
  clawServo.write(0); //sets the angle of the servo to 0 degrees
  topStepper.step(650); // decrease elevates; increase brings servo down
  // step one revolution (stepsPerRevolution = 200) clockwise
  bottomStepper.step(150);
  topStepper.step(-250); // decrease elevates; increase brings servo down
  
  clawServo.write(95); //176 is maximum vibration limit, 180 is absolute max
  
  // step one revolution in the other direction:
  topStepper.step(200);
  bottomStepper.step(-150);
  
  Serial.println(analogRead(distSensor)); //FIX THIS!!  
  
  clawServo.write(0); //176 is maximum vibration limit, 180 is absolute max
}
