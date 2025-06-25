#pragma once
#include <PubSubClient.h>

class LightSensor {
  int digitalPin;
  int analogPin;
  PubSubClient& client;

public:
  LightSensor(int digitalPin, int analogPin, PubSubClient& mqttClient);
  void begin();
  void readAndPublish();
};
