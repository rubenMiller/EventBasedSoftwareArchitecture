#pragma once
#include <Arduino.h>

class LEDStrip {
  int pin;
  int threshold;

public:
  LEDStrip(int triggerPin, int threshold = 500);
  void begin();
  void handleCommand(const String& message);
};
