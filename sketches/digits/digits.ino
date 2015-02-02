int photoDiodePin1 = 0;
int photoDiodeValue1 = 0;

int photoDiodePin2 = 1;
int photoDiodeValue2 = 1;

int score1 = 0;
int score2 = 0;

// segments as pins array
int segments1[] = {9, 8, 2, 1, 0, 10, 11};
int segments2[] = {12, 13, 5, 4, 3, 7, 6};

// paterns or segments array
int patterns[][8] = {
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

int incomingByte = 0;

void setup() {
  // set pin modes
  
  for (int i=0; i<7; i++){
    pinMode(segments1[i], OUTPUT);
  }
  for (int i=0; i<7; i++){
    pinMode(segments2[i], OUTPUT);
  }
  
  for (int i=0; i<13; i++) {
    digitalWrite(i, HIGH);
  }
  
//  Serial.begin(9600);
}

void loop() {
  photoDiodeValue1 = analogRead(photoDiodePin1);
  photoDiodeValue2 = analogRead(photoDiodePin2);
  
//  Serial.println(photoDiodeValue1);
  
  // fine tune these values :S
  if (photoDiodeValue1 <= 63) {
    score1 = (score1 + 1) % 10;
    delay(1000);
  }
  if (photoDiodeValue2 == 0) {
    score2 = (score2 + 1) % 10;
    delay(1000);
  }
  
  // clear display
  for (int i=0; i<13; i++) {
    digitalWrite(i, HIGH);
  }
  
  // draw digit
  for (int i=0; i<8; i++) {
    if (patterns[score1][i] == 1) {
      digitalWrite(segments1[i], LOW);
    }
  }
  
  for (int i=0; i<8; i++) {
    if (patterns[score2][i] == 1) {
      digitalWrite(segments2[i], LOW);
    }
  }
  
  delay(100);
}

