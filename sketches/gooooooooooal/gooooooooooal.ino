#define OUT_1 2
#define OUT_2 3
#define OUT_3 4

#define OUT_1_HI() digitalWrite(OUT_1, HIGH);
#define OUT_1_LO() digitalWrite(OUT_1, LOW);
#define OUT_2_HI() digitalWrite(OUT_2, HIGH);
#define OUT_2_LO() digitalWrite(OUT_2, LOW);
#define OUT_3_HI() digitalWrite(OUT_3, HIGH);
#define OUT_3_LO() digitalWrite(OUT_3, LOW);

void triggerGoal();

void setup()
{
  pinMode(OUT_1, OUTPUT);  
  pinMode(OUT_2, OUTPUT);  
  pinMode(OUT_3, OUTPUT);  
}

void loop()
{
  triggerGoal();
}

void triggerGoal()
{
  // first
  OUT_1_HI();
  delay(100);
  OUT_1_LO();
  delay(1000);

  // second
  OUT_2_HI();
  delay(100);
  OUT_2_LO();
  delay(1000);

  // third
  OUT_3_HI();
  delay(100);
  OUT_3_LO();
  delay(1000);
}