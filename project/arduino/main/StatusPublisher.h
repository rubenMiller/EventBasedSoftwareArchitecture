#pragma once
#include <PubSubClient.h>

class StatusPublisher {
  PubSubClient& client;
  unsigned long lastMsg = 0;
  const unsigned long timeDif = 500;

public:
  StatusPublisher(PubSubClient& mqttClient);
  void publishStatus();
};
