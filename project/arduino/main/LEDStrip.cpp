#include "LEDStrip.h"

LEDStrip::LEDStrip(int triggerPin, int thresholdVal)
  : pin(triggerPin), threshold(thresholdVal) {}

void LEDStrip::begin() {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);  // default to off
}

void LEDStrip::handleCommand(const String& message) {
  int value = message.toInt();
  Serial.print("LEDStrip received value: ");
  Serial.println(value);

  if (value >= threshold) {
    digitalWrite(pin, HIGH);
    Serial.println("LEDStrip: ON (above threshold)");
  } else {
    digitalWrite(pin, LOW);
    Serial.println("LEDStrip: OFF (below threshold)");
  }
}