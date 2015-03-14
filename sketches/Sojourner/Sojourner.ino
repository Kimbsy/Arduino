/**
 * Controller for Sojourner RC rover.
 * 
 * Pases on instructions from 6ch receiver
 * to servo motors.
 * 
 * Also can be run in 'roving' mode.
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
int l_speed = 90;
int r_speed = 90;

// min and max receiver input values
int l_min_rx = 9999999999;
int l_max_rx = 0;
int r_min_rx = 9999999999;
int r_max_rx = 0;

// control toggle
boolean roving = false;

// loop counter
int count = 0;
int max_count = 50;

// declare functions
void get_rove_input();
void get_rx_input();
void set_bounds(unsigned long input1, unsigned long input2);
void reset();

/**
 * Setup function
 */
void setup() {
  // attach servos
  l_wheels.attach(L_WHEELS);
  r_wheels.attach(R_WHEELS);
  
  // begin serial communication
  Serial.begin(9600);
}

/**
 * Main loop
 */
void loop() {
  
  // check if tx is on (3rd param is pulseIn timeout)
  unsigned long ch2 = pulseIn(L_INPUT, INPUT, 50000);
  unsigned long ch6 = pulseIn(R_INPUT, INPUT, 50000);
  
  if (ch2 == 0 || ch6 == 0) {
    roving = true;
  }
  else {
    roving = false;
  }
  
  // get left and right servo speeds 
  if (roving) {
    get_rove_input();
  }
  else {
    get_rx_input();
  }
      
//  Serial.println(l_speed);
//  Serial.println(r_speed);
  
  // set wheel speeds
  l_wheels.write(l_speed);
  r_wheels.write(r_speed);
  
  // count cycles over certain number of loops
  count = (count + 1) % max_count;
  
//  Serial.println(count);
}

/**
 * Set servo speeds via automated roving algorithm
 */
void get_rove_input() {
  
  if (count < (max_count / 4)) {
    // forwards
    l_speed = 180;
    r_speed = 0;
  }
  else if (count < (max_count / 2)) {
    // left
    l_speed = 0;
    r_speed = 0;
  }
  else if (count < ((max_count / 4) * 3)) {
    // forwards
    l_speed = 180;
    r_speed = 0;
  }
  else {
    // right
    l_speed = 180;
    r_speed = 180;
  }
  
  
  //@TODO: do this better
}

/**
 * Decode signals from receiver, then set
 * appropriate servo speeds
 */
void get_rx_input() {
  
  // get pulse sent from receiver
  unsigned long ch2 = pulseIn(L_INPUT, INPUT);
  unsigned long ch6 = pulseIn(R_INPUT, INPUT);
  
//  Serial.println(ch2);
//  Serial.println(ch6);
  
  // map inputs to servo usable outputs
  l_speed = map(ch2, l_min_rx, l_max_rx, 0, 180);
  r_speed = map(ch6, r_min_rx, r_max_rx, 0, 180);
  
  // figure out min and max values for input
  set_bounds(ch2, ch6);

  // set dead zones
  if (abs(l_speed - 90) < 10) {
    l_speed = 90;
  }
  
  if (abs(r_speed - 90) < 10) {
    r_speed = 90;
  }
}

/**
 * Set min and max values for rx input mapping
 */
void set_bounds(unsigned long input1, unsigned long input2) {
  if (input1 > l_max_rx) {
    l_max_rx = input1;
  }
  
  if (input1 < l_min_rx) {
    l_min_rx = input1;
  }
  
  if (input2 > r_max_rx) {
    r_max_rx = input2;
  }
  
  if (input2 < r_min_rx) {
    r_min_rx = input2;
  }
  
//  Serial.println(l_min_rx);
//  Serial.println(l_max_rx);
}
