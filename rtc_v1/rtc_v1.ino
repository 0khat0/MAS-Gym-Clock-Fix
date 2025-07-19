#include <Wire.h>
#include <RTClib.h>

RTC_PCF8523 rtc;

void setup() {
  Serial.begin(57600);
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));  // <-- Sets RTC to computer time

  Serial.println("RTC time has been reset.");
}

void loop() {}
