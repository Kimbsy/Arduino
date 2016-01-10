/**
 * Arduino sketch for 6ch receiver testing suite.
 *
 * Detects signal frequency and sends data over serial bus.
 */

long sigVals[] = {0, 0, 0, 0, 0, 0};

void setup()
{
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  Serial.begin(9600);
}

void loop()
{
  bool fucked = false;

  // Get new values.
  sigVals[0] = pulseIn(2, INPUT, 50000);
  sigVals[1] = pulseIn(3, INPUT, 50000);
  sigVals[2] = pulseIn(4, INPUT, 50000);
  sigVals[3] = pulseIn(5, INPUT, 50000);
  sigVals[4] = pulseIn(6, INPUT, 50000);
  sigVals[5] = pulseIn(7, INPUT, 50000);

  // Output.
  for (int i = 0; i < 6; i++) {
    if (sigVals[i] == 0) {
      fucked = true;
    }

    if (!fucked) {
      Serial.print(sigVals[i]);
      if (i != 5) {
        Serial.print(",");
      }
    }
  }
  if (!fucked) {
    Serial.print("\n");
  }
}
