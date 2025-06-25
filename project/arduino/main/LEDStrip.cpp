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

  bool shouldBeOn = value >= threshold;

  if (shouldBeOn != isOn) {
    isOn = shouldBeOn;
    digitalWrite(pin, isOn ? HIGH : LOW);
    Serial.println(isOn ? "LEDStrip: ON (above threshold)" : "LEDStrip: OFF (below threshold)");
  }
}