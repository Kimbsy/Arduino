/**
 * Using an arduino to control Kevin robot.
 */

void setup()
{
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop()
{
  // forward
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  delay(500);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  delay(500);

  // right
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  delay(500);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  delay(500);
}
