#pragma once
#include <PubSubClient.h>

class StatusPublisher {
  PubSubClient& client;
  unsigned long lastMsg;

public:
  StatusPublisher(PubSubClient& mqttClient);
  void publishStatus();
};
