
/*
   BYJ48 Stepper motor code
   Connect :
   IN1 >> D2
   IN2 >> D3
   IN3 >> D4
   IN4 >> D5
   VCC ... 5V Prefer to use external 5V Source
   Gnd
   written By :Mohannad Rawashdeh
  http://www.instructables.com/member/Mohannad+Rawashdeh/
     28/9/2013
  */

#define IN1  2
#define IN2  3
#define IN3  4
#define IN4  5

int steps = 0;
boolean direction = true;
unsigned long lastTime;
unsigned long currentMillis ;
int stepsLeft = 4095;
long t;

void setup()
{
  Serial.begin(115200);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  // delay(1000);
}

void loop()
{
  while(stepsLeft > 0){
    currentMillis = micros();
    if(currentMillis - lastTime >= 1000){
      stepper(1);
      t = t + micros() - lastTime;
      lastTime = micros();
      stepsLeft--;
    }
  }
  Serial.println(t);
  Serial.println("Wait...!");
  delay(2000);
  direction = !direction;
  stepsLeft = 4095;
}

void stepper(int xw){
  for (int x = 0; x < xw; x++){
    switch(steps){
      case 0:
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
      break;
      case 1:
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, HIGH);
      break;
      case 2:
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
      break;
      case 3:
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
      break;
      case 4:
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
      break;
      case 5:
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
      break;
        case 6:
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
      break;
      case 7:
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
      break;
      default:
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
      break;
    }
    SetDirection();
  }
}
void SetDirection(){
  if (direction == 1) { steps++; }
  if (direction == 0) { steps--; }
  if (steps > 7) { steps = 0; }
  if (steps < 0) { steps = 7; }
}
