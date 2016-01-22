#define LED 2

#define OUT_1 3
#define OUT_2 4
#define OUT_3 5

#define SENSORPIN 6

#define OUT_1_HI() digitalWrite(OUT_1, HIGH);
#define OUT_1_LO() digitalWrite(OUT_1, LOW);
#define OUT_2_HI() digitalWrite(OUT_2, HIGH);
#define OUT_2_LO() digitalWrite(OUT_2, LOW);
#define OUT_3_HI() digitalWrite(OUT_3, HIGH);
#define OUT_3_LO() digitalWrite(OUT_3, LOW);

int sensorState = 0;
int lastState = 0;
int score = 0;

void triggerGoal();

void setup()
{
  pinMode(LED, OUTPUT);  
  pinMode(OUT_1, OUTPUT);  
  pinMode(OUT_2, OUTPUT);  
  pinMode(OUT_3, OUTPUT);  
  pinMode(SENSORPIN, INPUT);  

  digitalWrite(SENSORPIN, HIGH);

  Serial.begin(9600);

  randomSeed(analogRead(0));
}

void loop()
{
  sensorState = digitalRead(SENSORPIN);
 
  // Check if the sensor beam is broken
  if (sensorState == LOW) {     
    digitalWrite(LED, HIGH);
    score++;
    Serial.println(score);
    triggerGoal();
  } 
  else {
    // turn LED off:
    digitalWrite(LED, LOW); 
  }
  
  lastState = sensorState;
}

void triggerGoal()
{
  int choice = random(3) + 1;

  switch (choice) {
    case 1:
      OUT_1_HI();
      delay(100);
      OUT_1_LO();
      break;
    case 2:
      OUT_2_HI();
      delay(100);
      OUT_2_LO();
      break;
    case 3:
      OUT_3_HI();
      delay(100);
      OUT_3_LO();
      break;
  }

  delay(1000);
}