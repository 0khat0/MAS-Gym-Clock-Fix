#include <Wire.h>
#include "RTClib.h"

#define SER_PIN 7
#define CLK_PIN 6
#define LAT_PIN 5

RTC_DS1307 rtc;

// Your custom segment mapping (A-F-G-E-D-C-B)
byte digitSegments[10] = {
  B01111011, // 0
  B01100000, // 1
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
  Serial.begin(57600);

  Wire.begin();
  if (!rtc.begin()) {
    Serial.println("RTC not found!");
    while (1);
  }

//   Serial.println("Manually setting time...");
// rtc.adjust(DateTime(2025, 7, 17, 17, 52, 0)); // ← year, month, day, hour, minute, second

if (!rtc.isrunning()) {
  Serial.println("RTC not running — starting it now.");
  rtc.adjust(DateTime(__DATE__, __TIME__));  // Or set manually again
}

}

void loop() {
  DateTime now = rtc.now();

  int hours = now.hour();
  if (hours > 12) hours -= 12;  // Convert to 12-hour format
  if (hours == 0) hours = 12;   // Handle midnight as 12

  int minutes = now.minute();

  Serial.print("Hour: "); Serial.print(hours);
  Serial.print(" | Minute: "); Serial.println(minutes);

  int timeNumber = hours * 100 + minutes;
  displayNumber(timeNumber);

  delay(1000);
}


void displayNumber(int number) {
  byte digits[4];

  // Break number into 4 digits: thousands, hundreds, tens, ones
  digits[0] = digitSegments[(number / 1000) % 10];
  digits[1] = digitSegments[(number / 100) % 10];
  digits[2] = digitSegments[(number / 10) % 10];
  digits[3] = digitSegments[number % 10];

  digitalWrite(LAT_PIN, LOW);
  for (int i = 3; i >= 0; i--) {
    shiftOut(SER_PIN, CLK_PIN, MSBFIRST, digits[i]);
  }
  digitalWrite(LAT_PIN, HIGH);
}
