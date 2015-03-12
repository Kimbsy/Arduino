/**
 * CERBERUS eye
 * 
 * Usage:
 *   # stop the dween from resetting imediately after the serial port is closed
 *   stty -F /dev/ttyUSB0 -hupcl
 *   # send a 'y' or 'n' character to the dween
 *   echo "y" > /dev/ttyUSB0
 *   echo "n" > /dev/ttyUSB0
 */

// set up pin constants
#define ORANGE 5
#define BLUE 6
#define EYE 3

// led HI-LO functions
#define O_HI() digitalWrite(ORANGE, HIGH);
#define O_LO() digitalWrite(ORANGE, LOW);
#define B_HI() digitalWrite(BLUE, HIGH);
#define B_LO() digitalWrite(BLUE, LOW);
#define E_HI() digitalWrite(EYE, HIGH);
#define E_LO() digitalWrite(EYE, LOW);

boolean active = false;

void setup() {
  // set pin modes
  pinMode(ORANGE, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(EYE, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  
  // check if Serial has a new byte in the buffer (otherwise returns -1)
  if (Serial.available() > 0) {
    // read new byte
    int input = Serial.read();
    
    switch (input) {
      // if is character 'y', start the things
      case 'y':
        active = true;
        break;
       // if is character 'n', stop the things
      case 'n':
        active = false;
        break;
      // default do nothing
      default:
        break;
    }
  }
    
  if (active) {
    // turn on eye
    E_HI();
    
    // blink lights
    O_HI();
    B_LO()
    delay(500);
    O_LO();
    B_HI();
    delay(500);
  }
  else {
    // turn off eye
    E_LO();
    
    // turn off lights
    O_LO();
    B_LO();
  }
}
