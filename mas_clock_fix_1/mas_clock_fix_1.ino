#define SER_PIN 7
#define CLK_PIN 6
#define LAT_PIN 5

// Segment patterns for 7-segment display (common cathode)
// Format: DP-G-F-E-D-C-B-A (MSB to LSB)
// You may need to flip these with LSBFIRST later if segments are miswired

// Standard 7-segment binary font
byte digitSegments[10] = {
  B01110111, // 0
  B00001010, // 1
  B01011101, // 2
  B01110101, // 3
  B01100110, // 4
  B00110111, // 5
  B00111111, // 6
  B01100001, // 7
  B01111111, // 8
  B01100111  // 9
};


void setup() {
  pinMode(SER_PIN, OUTPUT);
  pinMode(CLK_PIN, OUTPUT);
  pinMode(LAT_PIN, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  displayTestDigits();
  delay(2000);
}

void displayTestDigits() {
  // Digits: [1][2][5][8]
  byte digits[4] = {
    digitSegments[5],
    digitSegments[6],
    digitSegments[7],
    digitSegments[9]
  };

  digitalWrite(LAT_PIN, LOW);

  // Shift out rightmost first → leftmost last
  for (int i = 3; i >= 0; i--) {
    shiftOut(SER_PIN, CLK_PIN, MSBFIRST, digits[i]);
    // ↳ Try LSBFIRST if segments look wrong or scrambled
  }

  digitalWrite(LAT_PIN, HIGH);
}
