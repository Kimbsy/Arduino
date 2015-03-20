/**
 * Basic laser control.
 * 220 Ohm resistor from pin 2 to 'S'.
 * Ground pin to '-'.
 */

int laserPin = 2;

void setup() {
  pinMode(laserPin, OUTPUT);
}

void loop() {
  digitalWrite(laserPin, HIGH);
  delay(1000);
//  digitalWrite(laserPin, LOW);
  delay(1000);
}
