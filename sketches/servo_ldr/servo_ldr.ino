#include <Servo.h>

Servo servo;
int level = 0;
int min_level = 1025;
int max_level = 0;

void setup()
{
  servo.attach(2);
}

void loop()
{
  level = analogRead(A0);
  
  if (level > max_level) {
    max_level = level;
  }
  if (level < min_level) {
    min_level = level;
  }
  
  int out = map(level, min_level, max_level, 0, 180);
  
  servo.write(out);
}


