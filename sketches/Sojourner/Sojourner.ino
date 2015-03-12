/**
 * Controller for Sojourner RC rover.
 * 
 * Pases on instructions from 6ch receiver
 * to servo motors.
 * 
 * Also can be run in 'rove' mode.
 *
 * Pins 2 & 3 are servo signal outputs.
 * Pins 4 & 5 are receiver signal input.
 * 
 * 5V goes to Vcc on receiver and both servos.
 * Gnd goes to Gnd on receiver and both servos.
 */
 
#include <Servo.h> 
 
// set up pin constants
// outputs
#define L_WHEELS 2
#define R_WHEELS 3
//inputs
#define L_INPUT 4
#define R_INPUT 5

// declare servo objects
Servo l_wheels;
Servo r_wheels;

// variables for servo speed
// 0 = backward
// 90 = no movement,
// 180 = forward,
int l_speed = 90;
int r_speed = 90;

// min and max receiver input values
int min_rx = 9999999999;
int max_rx = 0;

// setup function
void setup() {
  // attach servos
  l_wheels.attach(L_WHEELS);
  r_wheels.attach(R_WHEELS);
  
  // begin serial communication
  Serial.begin(9600);
}

// main loop function
void loop() {
  
  // get pulse sent from receiver
  unsigned long ch2 = pulseIn(L_INPUT, INPUT);
  unsigned long ch6 = pulseIn(R_INPUT, INPUT);
  
  // map inputs to servo usable outputs
  l_speed = map(ch2, 21270, 22780, 0, 180);
  r_speed = map(ch6, 21270, 22780, 0, 180);
  
//  Serial.println(l_speed);
//  Serial.println(r_speed);
  
  // figure out min and max values for input
//  if (ch6 > max_rx) {
//    max_rx = ch6;
//  }
//  
//  if (ch6 < min_rx) {
//    min_rx = ch6;
//  }
//  
//  Serial.println(min_rx);
//  Serial.println(max_rx);
  
//22778
//21277

//22755
//21297

  // set dead zone
  if (abs(l_speed - 90) < 10) {
    l_speed = 90;
  }


  // set wheel speeds
  l_wheels.write(l_speed);
  r_wheels.write(r_speed);
}
