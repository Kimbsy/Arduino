/**
 * Arduino sketch controlling EMF rover.
 *
 * Detects signals from HK 6ch transceiver.
 */

#define PIN_LEFT 8
#define PIN_RIGHT 9

long sigVals[] = {0, 0, 0, 0, 0, 0};

long min_steer = 99999;
long max_steer = 0;

void setup()
{
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);

  pinMode(PIN_LEFT, OUTPUT);
  pinMode(PIN_RIGHT, OUTPUT);

  Serial.begin(9600);
}

void loop()
{
  // Get new values.
  sigVals[0] = pulseIn(2, INPUT, 50000);
  sigVals[1] = pulseIn(3, INPUT, 50000);
  sigVals[2] = pulseIn(4, INPUT, 50000);
  sigVals[3] = pulseIn(5, INPUT, 50000);
  sigVals[4] = pulseIn(6, INPUT, 50000);
  sigVals[5] = pulseIn(7, INPUT, 50000);

  // sigVals[0] represents white wire channel (6?)

  if (sigVals[0] < min_steer) {
    min_steer = sigVals[0];
  }
  if (sigVals[0] > max_steer) {
    max_steer = sigVals[0];
  }

  int normalized_steer = map(sigVals[0], min_steer, max_steer, 0, 255);

  // Turn right.
  if (normalized_steer > 180) {
    Serial.println("RIGHT");
    digitalWrite(PIN_RIGHT, HIGH);
  }
  // Turn left.
  if (normalized_steer < 80) {
    Serial.println("LEFT");
    digitalWrite(PIN_LEFT, HIGH);
  }

  if (Serial.available() > 0) {
    // read incoming serial data:
    char inChar = Serial.read();
    if (inChar == (int) 'r') {
        min_steer = 99999;
        max_steer = 0;
    }
  }
}
