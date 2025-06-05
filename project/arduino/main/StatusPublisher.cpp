#include "StatusPublisher.h"
#include <Arduino.h>

StatusPublisher::StatusPublisher(PubSubClient& mqttClient)
  : client(mqttClient), lastMsg(0) {}

void StatusPublisher::publishStatus() {
  if (millis() - lastMsg > 5000) {
    lastMsg = millis();
    String msg = "Hello from Arduino at " + String(millis());
    client.publish("arduino/status", msg.c_str());
    Serial.println("Published: " + msg);
  }
}
