/**
 * Radio controlled laser turret.
 *
 * 220 Ohm resistor from pin 2 to 'S' pin on module.
 * Ground pin to '-' on module.
 *
 * Two servos for 2 axis movement.
 * 
 * Using left stick of 6ch transmitter
 *   up/down is channel 3 (purple) on pin 4
 *   left/right is channel 4 (blue) on pin 5
 */
 
#include <Servo.h>

// pin constants
#define LASER_PIN 2
#define ROTATE_IN 4
#define ELEVATE_IN 5

// min and max receiver input values
int rMax = 0;
int eMax = 0;
int rMin = 9999999999;
int eMin = 9999999999;

// variables for servo position
int rPos = 90;
int ePos = 90;
int rOld = 90;
int eOld = 90;
int rNew = 90;
int eNew = 90;

// variables for receiver values
unsigned long ch3; // elevation
unsigned long ch4; // rotation

// declare servo objects
Servo rotate;
Servo elevate;

// declare functions
void getRxInput();
void setBounds(unsigned long input1, unsigned long input2);

void setup() {
  // set pinmodes
  pinMode(LASER_PIN, OUTPUT);
  pinMode(ROTATE_IN, INPUT);
  pinMode(ELEVATE_IN, INPUT);
  
  // initialise servo objects
  rotate.attach(6);
  elevate.attach(7);
}

void loop() {
  // make sure the laser is on
  digitalWrite(LASER_PIN, HIGH);

  // check if tx is on (3rd param is timeout)
  ch3 = pulseIn(ELEVATE_IN, INPUT, 50000);
  ch4 = pulseIn(ROTATE_IN, INPUT, 50000);
  
  // get values from receiver
  getRxInput();

  // write positions to servos
  rotate.write(rPos);
  elevate.write(ePos);
}

/**
 * Decode signals from receiver, then set appropriate servo speeds.
 */
void getRxInput()
{
  // figure out min and max values for input
  setBounds(ch3, ch4);

  // map inputs to servo usable outputs (elevation is inverted)
  eNew = 180 - map(ch3, eMin, eMax, 0, 180);
  rNew = map(ch4, rMin, rMax, 0, 180);

  // only update position if it's far enogh away from the old position
  if (abs(eNew - eOld) > 20)
  {
    ePos = eNew;
    eOld = eNew;
  }
  if (abs(rNew - rOld) > 20)
  {
    rPos = rNew;
    rOld = rNew;
  }
}

/**
 * Set min and max values for rx input mapping.
 */
void setBounds(unsigned long input1, unsigned long input2)
{
  if (input1 > eMax)
  {
    eMax = input1;
  }
  
  if (input1 < eMin)
  {
    eMin = input1;
  }
  
  if (input2 > rMax)
  {
    rMax = input2;
  }
  
  if (input2 < rMin)
  {
    rMin = input2;
  }
}
