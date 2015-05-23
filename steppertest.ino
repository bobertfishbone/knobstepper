/* 
This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
It won't work with v1.x motor shields! Only for the v2's with built in PWM
control

For use with the Adafruit Motor Shield v2 
---->	http://www.adafruit.com/products/1438
*/


#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *myMotor = AFMS.getStepper(200, 1);


long millistart;
bool run = false;
int numberofSteps = 115; //number of steps to take


//long duration = 10000; //1 minute in milliseconds -- Testing
long duration = 7200000; //2 hours in milliseconds

void setup() {

  Serial.begin(9600);
  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  myMotor->setSpeed(1);  // 2 rpm  

  Serial.println("Stepping motor");
  myMotor->step(numberofSteps, FORWARD, MICROSTEP);
  myMotor->release();
  millistart = millis();

}

void loop() {

  Serial.println(millistart);
  if (millis() > millistart + duration)
  {
    if (run == false)
    {
      Serial.print("STEPPIN");
      myMotor->step(numberofSteps, BACKWARD, MICROSTEP);
      Serial.print("done");
      myMotor->release();
      run = true;
    }
    
  }
  
}

