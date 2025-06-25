#pragma once
#include <PubSubClient.h>

class UltrasonicSensor {
  int trigPin;
  int echoPin;
  PubSubClient& client;
  unsigned long lastTest = 0;
  const unsigned long timeDif = 500;

public:
  UltrasonicSensor(int trig, int echo, PubSubClient& mqttClient);
  void begin();
  void checkDistance();
};
