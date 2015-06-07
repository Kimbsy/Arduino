/**
 * Controller for Sojourner RC rover.
 * 
 * Passes on instructions from 6ch receiver (rx) to servo motors.
 * 
 * Turn off transmitter (tx) to run in 'roving' mode.
 * In roving mode rover cecks for obstacles with ultrasonic sensor (HC-SR04)
 *
 * Pins 2 & 3 are servo signal outputs.
 * Pins 4 & 5 are rx signal input.
 * Pin 6 is SR04 trig pin
 * Pin 7 is SR04 echo pin
 * 
 * 5V goes to Vcc on rx, both servos and SR04.
 * Gnd goes to Gnd on rx, both servos and SR04.
 */
 
#include <Servo.h> 
 
// set up pin constants
// outputs
#define L_WHEELS 2
#define R_WHEELS 3
#define TRIG_PIN 6
// inputs
#define L_INPUT 4
#define R_INPUT 5
#define ECHO_PIN 7

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

// varibles for receiver values
unsigned long ch2 = 0;
unsigned long ch6 = 0;

// variables for measuring distance
long distance;

// variables for roving control
boolean roving = false;
int turning = 0;

// declare functions
void getRoveInput();
long getDistance();
void getRxInput();
void setBounds(unsigned long input1, unsigned long input2);
void reset();

/**
 * Setup function.
 */
void setup()
{
  // attach servos
  l_wheels.attach(L_WHEELS);
  r_wheels.attach(R_WHEELS);

  // set pinmodes for SR04
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // pin 0 is unconnected so random noise is a good seed
  randomSeed(analogRead(0));
  
  // begin serial communication
  Serial.begin(9600);
}

/**
 * Main loop.
 */
void loop()
{
  // check if tx is on (3rd param is timeout)
  ch2 = pulseIn(L_INPUT, INPUT, 50000);
  ch6 = pulseIn(R_INPUT, INPUT, 50000);
  
  if (ch2 == 0 || ch6 == 0)
  {
    roving = true;
  }
  else
  {
    roving = false;
  }
  
  // get left and right servo speeds 
  if (roving)
  {
    getRoveInput();
  }
  else
  {
    getRxInput();
  }
      
  // set servo speeds
  l_wheels.write(l_speed);
  r_wheels.write(r_speed);
}

/**
 * Set servo speeds via automated roving algorithm.
 *
 * Check distance in front
 * if clear
 *   move forward
 * else
 *   if we're already turning
 *     keep turning
 *   else
 *     decide which way to turn
 *   turn
 */
void getRoveInput()
 {
  // check the distance in front of the rover
  distance = getDistance();

  // if there are no obstacles, go straight on
  if (distance > 15)
  {
    // stop turning
    turning = 0;

    // forwards
    l_speed = 180;
    r_speed = 0;
  }
  else
  {
    // check if we're not already turning
    if (turning == 0)
    {
      // choose random direction
      if (random(2))
      {
        turning = 1;
      }
      else
      {
        turning = -1;
      }
    }

    // turn in chosen direction
    if (turning == 1)
    {
      // right
      l_speed = 180;
      r_speed = 180;
    }
    else if (turning == -1)
    {
      // left
      l_speed = 0;
      r_speed = 0;
    }
  }
}

/**
 * Check distance in front of rover with ultrasonic sensor (HC-SR04).
 */
long getDistance()
{
  // set trigger low (make sure it's off)
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // send out ping
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  // stop ping
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);

  // distance in cm based on speed of sound
  return duration / 58.2;
}

/**
 * Decode signals from receiver, then set appropriate servo speeds.
 */
void getRxInput()
{
  // map inputs to servo usable outputs
  l_speed = map(ch2, l_min_rx, l_max_rx, 0, 180);
  r_speed = map(ch6, r_min_rx, r_max_rx, 0, 180);
  
  // figure out min and max values for input
  setBounds(ch2, ch6);

  // set dead zones
  if (abs(l_speed - 90) < 10)
  {
    l_speed = 90;
  }
  
  if (abs(r_speed - 90) < 10)
  {
    r_speed = 90;
  }
}

/**
 * Set min and max values for rx input mapping.
 */
void setBounds(unsigned long input1, unsigned long input2)
{
  if (input1 > l_max_rx)
  {
    l_max_rx = input1;
  }
  
  if (input1 < l_min_rx)
  {
    l_min_rx = input1;
  }
  
  if (input2 > r_max_rx)
  {
    r_max_rx = input2;
  }
  
  if (input2 < r_min_rx)
  {
    r_min_rx = input2;
  }
}
