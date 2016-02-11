/**
 * Arduino sketch controlling EMF rover.
 *
 * Detects signals from HK 6ch transceiver.
 */

#define PIN_LEFT 8
#define PIN_RIGHT 9
#define PIN_FORWARD 10
#define PIN_REVERSE 11

long sigVals[] = {0, 0, 0, 0, 0, 0};

long min_steer = 99999;
long max_steer = 0;
long min_drive = 99999;
long max_drive = 0;

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
  // Get channel values.
  sigVals[0] = pulseIn(2, INPUT, 50000);
  sigVals[1] = pulseIn(3, INPUT, 50000);
  sigVals[2] = pulseIn(4, INPUT, 50000);
  sigVals[3] = pulseIn(5, INPUT, 50000);
  sigVals[4] = pulseIn(6, INPUT, 50000);
  sigVals[5] = pulseIn(7, INPUT, 50000);

  // sigVals[0] represents white wire channel (6?) used for steering.
  long steer = sigVals[0];
  if (steer < min_steer) {
    min_steer = steer;
  }
  if (steer > max_steer) {
    max_steer = steer;
  }

  // sigVals[2] represents purple wire channel (2?) used for drive.
  long drive = sigVals[2];
  if (drive < min_drive) {
    min_drive = drive;
  }
  if (drive > max_drive) {
    max_drive = drive;
  }

  int normalized_steer = map(steer, min_steer, max_steer, 0, 255);
  int normalized_drive = map(drive, min_drive, max_drive, 0, 255);

  // Turn right.
  if (normalized_steer > 180) {
    Serial.println("RIGHT");
    digitalWrite(PIN_RIGHT, HIGH);
  } else {
    digitalWrite(PIN_RIGHT, LOW);
  }
  // Turn left.
  if (normalized_steer < 80) {
    Serial.println("LEFT");
    digitalWrite(PIN_LEFT, HIGH);
  } else {
    digitalWrite(PIN_LEFT, LOW);
  }

  // Drive forward.
  if (normalized_drive > 180) {
    Serial.println("FORWARD");
    digitalWrite(PIN_FORWARD, HIGH);
  } else {
    digitalWrite(PIN_FORWARD, LOW);
  }
  // Drive reverse.
  if (normalized_drive < 80) {
    Serial.println("REVERSE");
    digitalWrite(PIN_REVERSE, HIGH);
  } else {
    digitalWrite(PIN_REVERSE, LOW);
  }

  // Allow min/max values to be reset from serial console.
  if (Serial.available() > 0) {
    // read incoming serial data:
    char inChar = Serial.read();
    if (inChar == (int) 'r') {
        min_steer = 99999;
        max_steer = 0;
        min_drive = 99999;
        max_drive = 0;
    }
  }
}
