#include <AccelStepper.h>

#include <Wire.h>

#include <Encoder.h>

#include <Adafruit_MotorShield.h>

// Time variables
long duration = 10000; // 10 seconds in milliseconds
long millistart; // Grabs milliseconds since power on once motor has initially stepped.
bool run = false; // Has the cycle ended?

// Step variables
int numberofSteps = 100; // Number of steps initially taken
long oldPosition = 0; // Encoder reference point

// Create motor, encoder objects
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Encoder enc(2,3);
Adafruit_StepperMotor *myMotor = AFMS.getStepper(200,1);

void forwardStep()
{
 myMotor->onestep(FORWARD, MICROSTEP); 
}

void backwardStep()
{
  myMotor->onestep(BACKWARD, MICROSTEP);
}

AccelStepper stepper(forwardStep, backwardStep);




void setup() {
  // put your setup code here, to run once:
  stepper.setCurrentPosition(0);
  stepper.setSpeed(4);
  
  stepper.moveTo(numberofSteps);
  
  millistart = millis();
}

void loop() {
  // put your main code here, to run repeatedly:

  long newPosition = enc.read()/4;
  
  if (newPosition != oldPosition)
  {
  if (newPosition > oldPosition)
  {
    stepper.moveTo(stepper.currentPosition()+(newPosition - oldPosition));
  }
  else
  {
   stepper.moveTo(stepper.currentPosition()-(oldPosition-newPosition)); 
  }
  }
  
  newPosition = enc.read()/4;
  oldPosition = newPosition;

if (millis() > millistart + duration)
  {
    if (run == false)
    {
      
      stepper.setSpeed(4);
      stepper.moveTo(0);
      run = true;
    }
    
  }


}
