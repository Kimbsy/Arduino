#define RED 2

#define RED_HI() digitalWrite(RED, HIGH);
#define RED_LO() digitalWrite(RED, LOW);

boolean active = false;

void setup() {
  pinMode(RED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    int input = Serial.read();
    
    switch(input) {
      case 'y':
        active = true;
        break;
      case 'n':
        active = false;
        break;
      default:
        break;
    }
  }
  
  if (active) {
    RED_HI();
  }
  else {
    RED_LO();
  }
}
