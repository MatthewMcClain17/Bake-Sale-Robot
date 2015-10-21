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

//CapacitiveSensor Cookie = CapacitiveSensor(48, 49);
//CapacitiveSensor Donut = CapacitiveSensor(50, 51);
//CapacitiveSensor Muffin = CapacitiveSensor(52, 53);

#include <Servo.h>
#include <Stepper.h>
#include <CapacitiveSensor.h> //make sure you have this installed, found at:
//http://playground.arduino.cc/Main/CapacitiveSensor?from=Main.CapSense

const int distSensor = 15; //Infrared distance sensor signal pin

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor


// initialize the stepper library on pins 8 through 11:
Stepper bottomStepper(stepsPerRevolution, 22, 24, 26, 28);
Stepper topStepper(stepsPerRevolution, 23, 25, 27, 29);
// initialize claw servo
Servo clawServo;

void setup() {
  pinMode(distSensor, INPUT); // set the distance sensor's signal to input
  // set the speed at 30 rpm:

  bottomStepper.setSpeed(30);
  topStepper.setSpeed(30);

  clawServo.attach(43);

  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {

  if (Cookie.CapacitiveSensor > 100) { // if Cookie is greater than 100 (an arbitrary threshold)
    action1();
  }

  if (Donut.CapacitiveSensor > 100) { // if Donut is greater than 100 (an arbitrary threshold)
  action2();
  }

  if (Muffin.CapacitiveSensor > 100) { // if Muffin is greater than 100 (an arbitrary threshold)
  action3();
  }
}

// FUNCTIONS

void action1() {

  clawServo.write(0); //sets the angle of the servo to 0 degrees
  topStepper.step(650); // decrease elevates; increase brings servo down
  // step one revolution (stepsPerRevolution = 200) clockwise
  bottomStepper.step(50);
  topStepper.step(-250); // decrease elevates; increase brings servo down
  
  clawServo.write(95); //176 is maximum vibration limit, 180 is absolute max
  
  // step one revolution in the other direction:
  topStepper.step(200);
  bottomStepper.step(-50);
  
  Serial.println(analogRead(distSensor)); //FIX THIS!!  
  
  clawServo.write(0); //176 is maximum vibration limit, 180 is absolute max

 
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
