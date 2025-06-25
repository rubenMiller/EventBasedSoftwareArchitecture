#include "LightSensor.h"
#include <Arduino.h>

LightSensor::LightSensor(int digital, int analog, PubSubClient& mqttClient)
  : digitalPin(digital), analogPin(analog), client(mqttClient) {}

void LightSensor::begin() {
  pinMode(digitalPin, INPUT_PULLUP);
}

static unsigned long lastRead = 0;
int analogVal = 1023;
char buffer[10];

void LightSensor::readAndPublish() {
  analogVal = analogRead(analogPin);

  //Serial.print("Digital Read: ");
  //Serial.println(digitalVal);
  //Serial.print("Analog Read: ");
  //Serial.println(analogVal);

  itoa(analogVal, buffer, 10); // Bad things would happen without this
  client.publish("arduino/light_sensor", buffer);
  delay(1000);
}
