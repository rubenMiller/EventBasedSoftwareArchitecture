#include "AnalogSensor.h"
#include <Arduino.h>

AnalogSensor::AnalogSensor(int digital, int analog, PubSubClient& mqttClient)
  : digitalPin(digital), analogPin(analog), client(mqttClient) {}

void AnalogSensor::begin() {
  pinMode(digitalPin, INPUT_PULLUP);
}

static unsigned long lastRead = 0;

void AnalogSensor::readAndPublish() {
  int digitalVal = digitalRead(digitalPin);
  int analogVal = analogRead(analogPin);

  Serial.print("Digital Read: ");
  Serial.println(digitalVal);
  Serial.print("Analog Read: ");
  Serial.println(analogVal);

  client.publish("arduino/light_sensor", analogVal);
}
