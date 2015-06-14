double count = 0;

long min1 = 9999999;
long min2 = 9999999;
long min3 = 9999999;
long min4 = 9999999;
long min5 = 9999999;
long min6 = 9999999;
long max1 = 0;
long max2 = 0;
long max3 = 0;
long max4 = 0;
long max5 = 0;
long max6 = 0;

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
  long sig1 = pulseIn(2, INPUT, 50000);
  long sig2 = pulseIn(3, INPUT, 50000);
  long sig3 = pulseIn(4, INPUT, 50000);
  long sig4 = pulseIn(5, INPUT, 50000);
  long sig5 = pulseIn(6, INPUT, 50000);
  long sig6 = pulseIn(7, INPUT, 50000);

  if (sig1 > max1) max1 = sig1;
  if (sig2 > max2) max2 = sig2;
  if (sig3 > max3) max3 = sig3;
  if (sig4 > max4) max4 = sig4;
  if (sig5 > max5) max5 = sig5;
  if (sig6 > max6) max6 = sig6;
  
  if (sig1 < min1) min1 = sig1;
  if (sig2 < min2) min2 = sig2;
  if (sig3 < min3) min3 = sig3;
  if (sig4 < min4) min4 = sig4;
  if (sig5 < min5) min5 = sig5;
  if (sig6 < min6) min6 = sig6;

  // value, fromlow, fromhigh, tlow, tohigh
  Serial.print(1023 - map(sig1, min1, max1, 0, 1023));
  Serial.print(",");
  Serial.print(1023 - map(sig2, min2, max2, 0, 1023));
  Serial.print(",");
  Serial.print(1023 - map(sig3, min3, max3, 0, 1023));
  Serial.print(",");
  Serial.print(1023 - map(sig4, min4, max4, 0, 1023));
  Serial.print(",");
  Serial.print(1023 - map(sig5, min5, max5, 0, 1023));
  Serial.print(",");
  Serial.print(1023 - map(sig6, min6, max6, 0, 1023));
  Serial.print("\n");
  count++;
}