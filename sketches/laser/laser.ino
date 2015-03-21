/**
 * Basic laser control.
 * 220 Ohm resistor from pin 2 to 'S'.
 * Ground pin to '-'.
 *
 * Two servos for 2 axis movement. 
 */
 
#include <Servo.h>

int laserPin = 2;

Servo rotate;
Servo elevate;

void setup() {
  pinMode(laserPin, OUTPUT);
  
  rotate.attach(3);
  elevate.attach(4);
}

void loop() {
  digitalWrite(laserPin, HIGH);
  
  rotate.write(180);
  elevate.write(180);
  
  delay(1000);
  
  rotate.write(0);
  elevate.write(0);
  
  delay(1000);
}
