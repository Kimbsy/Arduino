// gmail chat led definitions
#define RED 2
#define YEL 3
#define GRE 4

#define RED_HI() digitalWrite(RED, HIGH);
#define RED_LO() digitalWrite(RED, LOW);
#define YEL_HI() digitalWrite(YEL, HIGH);
#define YEL_LO() digitalWrite(YEL, LOW);
#define GRE_HI() digitalWrite(GRE, HIGH);
#define GRE_LO() digitalWrite(GRE, LOW);

boolean red = false;
boolean yellow = false;
boolean green = false;

// activity toggle
boolean show_notifications = true;

// ultrasonic distance measurement definitions
#define echo_pin 12
#define trig_pin 11

int max_range = 200;
int min_range = 0;
long duration, distance;

void setup() {
  // gmail pin setup
  pinMode(RED, OUTPUT);
  pinMode(YEL, OUTPUT);
  pinMode(GRE, OUTPUT);
  
  // ultrasound pin setup
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  
  Serial.begin(9600); 
}

void loop() {
  
  // check ultrasound sensor
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);

  // send a ping
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  
  // receive the echo
  digitalWrite(trig_pin, LOW);
  duration = pulseIn(echo_pin, HIGH);
  
  //calculate distance based on speed of sound in air
  distance = duration/58.138;
  
  // is distance fine?
  if (distance >= max_range || distance <= min_range) {
//    RED_LO();
  }
  else {
    Serial.println("wooooooo");  
//    RED_HI();
    show_notifications = !show_notifications;
    delay(1000);
  }
  
  if (show_notifications) {
  
    // check for bytes coming down usb-serial to tell leds what to do
    if (Serial.available() > 0) {
      int input = Serial.read();
      int delayTime = 0;
      
      switch(input) {
        // allow user input delay
        case 'd':
          delayTime = Serial.parseInt();
          delay(delayTime);
          break;
        // red led
        case 'r':
          red = true;
          break;
        case 'f':
          red = false;
          break;
        //yellow led
        case 'y':
          yellow = true;
          break;
        case 'h':
          yellow = false;
          break;
        //green led
        case 'g':
          green = true;
          break;
        case 'b':
          green = false;
          break;
        default:
          break;
      }
    }
    
    // turn LEDS on/off
    if (red) {
      RED_HI();
    }
    else {
      RED_LO();
    }
    
    if (yellow) {
      YEL_HI();
    }
    else {
      YEL_LO();
    }
    
    if (green) {
      GRE_HI();
    }
    else {
      GRE_LO();
    }
    
  }
  else {
    RED_LO();
    YEL_LO();
    GRE_LO();
  }
}

