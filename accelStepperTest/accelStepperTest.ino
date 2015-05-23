#include <AccelStepper.h>

#include <Wire.h>

#include <Encoder.h>

#include <Adafruit_MotorShield.h>

// Time variables
long duration = 20000; // 10 seconds in milliseconds
long millistart; // Grabs milliseconds since power on once motor has initially stepped.
bool run = false; // Has the cycle ended?

// Step variables
int numberofSteps = 100; // Number of steps initially taken
long oldPosition = 0; // Encoder reference point

// Create motor, encoder objects
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Encoder enc(2, 5);
Adafruit_StepperMotor *myMotor = AFMS.getStepper(200, 1);
AccelStepper stepper(forwardStep, backwardStep);
void forwardStep()
{
  myMotor->onestep(FORWARD, MICROSTEP);
}

void backwardStep()
{
  myMotor->onestep(BACKWARD, MICROSTEP);
}






void setup() {
  // put your setup code here, to run once:
  AFMS.begin();

  stepper.setMaxSpeed(100);
  stepper.setAcceleration(500);
  //stepper.setCurrentPosition(0);
  stepper.runToNewPosition(1200);
  
  millistart = millis();
}

void loop() {
 if (run == false){
  // put your main code here, to run repeatedly:
  stepper.setMaxSpeed(100);
  stepper.setAcceleration(500);
  long newPosition = enc.read();



  if (newPosition != oldPosition)
  {
    if (newPosition > oldPosition)
    {
      stepper.moveTo(stepper.currentPosition() + 40*(newPosition - oldPosition));
      
    }
    else
    {
      stepper.moveTo(stepper.currentPosition() - 40*(oldPosition - newPosition));
    }
  }


  oldPosition = newPosition;
  stepper.run();
  
  if (millis() > millistart + duration)
  {
    if (run == false)
    {

      stepper.setMaxSpeed(100);
      stepper.setAcceleration(500);
stepper.runToNewPosition(0);
      run = true;
      myMotor->release();
    }

  }
 }

}
