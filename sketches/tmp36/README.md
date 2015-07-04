Measures the temperature using a TMP36 high acuracy temperature sensor.
Facing flat side of sensor:
  left => 5V
  middle => analogue pin 0
  right => ground
Get computer to read out temperatuer every 5 seconds using espeak:
  while [ "true" ]; do espeak "the temperature is $(cat /dev/ttyUSB0) degrees celcius"; sleep 5; done