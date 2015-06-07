Controller for Sojourner RC rover.

Passes on instructions from 6ch receiver (rx) to servo motors (HK-T6A V2).

Turn off transmitter (tx) to run in 'roving' mode.
In roving mode rover cecks for obstacles with ultrasonic sensor (HC-SR04)

*Pins 2 & 3 are servo signal outputs.
*Pins 4 & 5 are rx signal input.
*Pin 6 is SR04 trig pin
*Pin 7 is SR04 echo pin

*5V goes to Vcc on rx, both servos and SR04.
*Gnd goes to Gnd on rx, both servos and SR04.
