#pragma once
#include <PubSubClient.h>

class AnalogSensor {
  int digitalPin;
  int analogPin;
  PubSubClient& client;

public:
  AnalogSensor(int digitalPin, int analogPin, PubSubClient& mqttClient);
  void begin();
  void readAndPublish();
};
