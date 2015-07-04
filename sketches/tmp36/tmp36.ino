/**
 * Measures the temperature using a TMP36 high acuracy temperature sensor.
 *
 * Facing flat side of sensor:
 *   left => 5V
 *   middle => analogue pin 0
 *   right => ground
 *
 * Get computer to read out temperatuer every 5 seconds using espeak:
 * 
 *   while [ "true" ]; do espeak "the temperature is $(cat /dev/ttyUSB0) degrees celcius"; sleep 5; done
 *   
 */

#define A_IN 0

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  // read voltage from TMP36
  int reading = analogRead(A_IN);

  // convert to voltage (use 3.3 for 3.3V power)
  float voltage = reading * 5;
  voltage /= 1024;

  // 10mv per degree, with 500mv as offset for negative temps
  float tempC = (voltage - 0.5) * 100;

  Serial.println(tempC);

  delay(1000);  
}
