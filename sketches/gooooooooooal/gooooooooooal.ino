// sketch to read values from a Photodiode

int Photo_diode_Value = 0;

int score = 0;

const int Photo_diode_Pin = 0;  // arduino pin that sensor happens to be hooked up to
const int IR_LED_pin = 11;

void setup() 
{
    Serial.begin(9600);    // open serial port to laptop to print values
    analogWrite(IR_LED_pin, 255);
}

void loop() 
{
    Photo_diode_Value = analogRead(Photo_diode_Pin);            // Read analog Pin 
//    Serial.print("   Photo diode reads = ");      // print text string 
//    Serial.println(Photo_diode_Value, DEC);       // print value of variable
    
    Serial.println(score);
    if (Photo_diode_Value == 0) {
      goal();
    }

    delay(30);        // delay so the program does not run too fast
}

void goal() {
  score++;
  delay(500);
}
