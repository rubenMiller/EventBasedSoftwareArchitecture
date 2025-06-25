#include "LightSensor.h"
#include <Arduino.h>

LightSensor::LightSensor(int digital, int analog, PubSubClient& mqttClient)
  : digitalPin(digital), analogPin(analog), client(mqttClient) {}

void LightSensor::begin() {
  pinMode(digitalPin, INPUT_PULLUP);
}

void LightSensor::readAndPublish() {

  unsigned long now = millis();
  if(now - lastTest < timeDif){
    return;
  }
  lastTest = now;

  char buffer[10];
  int analogVal = analogRead(analogPin);

  //Serial.print("Digital Read: ");
  //Serial.println(digitalVal);
  //Serial.print("Analog Read: ");
  //Serial.println(analogVal);

  itoa(analogVal, buffer, 10); // Bad things would happen without this
  client.publish("arduino/light_sensor", buffer);
}
