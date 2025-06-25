#pragma once
#include <PubSubClient.h>

class LightSensor {
  int digitalPin;
  int analogPin;
  PubSubClient& client;
  unsigned long lastTest = 0;
  const unsigned long timeDif = 500;

public:
  LightSensor(int digitalPin, int analogPin, PubSubClient& mqttClient);
  void begin();
  void readAndPublish();
};
