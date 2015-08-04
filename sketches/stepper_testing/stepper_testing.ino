/**
 * Testing stepper motor control with AccelStepper library.
 */

#include <AccelStepper.h>

// Define a stepper and the pins it will use
AccelStepper stepper; // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5

int full_rotation = 2038;

int target = 0;

void setup()
{  
  stepper.setMaxSpeed(1000);
}

void doStuff()
{
  stepper.moveTo(target);
  stepper.setSpeed(300);
  stepper.runSpeedToPosition();
}

void checkStuff()
{
  if (stepper.currentPosition() == target)
  {
    target += (full_rotation / 4);
    delay(500);
  }
}

void loop()
{
  doStuff();
  checkStuff();
}
