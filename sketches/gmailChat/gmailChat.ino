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


void setup() {
  pinMode(RED, OUTPUT);
  pinMode(YEL, OUTPUT);
  pinMode(GRE, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  
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

