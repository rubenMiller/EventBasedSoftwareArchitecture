#pragma once
#include <PubSubClient.h>

class UltrasonicSensor {
  int trigPin;
  int echoPin;
  PubSubClient& client;

public:
  UltrasonicSensor(int trig, int echo, PubSubClient& mqttClient);
  void begin();
  void checkDistance();
};
