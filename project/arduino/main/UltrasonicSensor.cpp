#include "UltrasonicSensor.h"
#include <Arduino.h>

UltrasonicSensor::UltrasonicSensor(int trig, int echo, PubSubClient& mqttClient)
  : trigPin(trig), echoPin(echo), client(mqttClient) {}

void UltrasonicSensor::begin() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}



void UltrasonicSensor::checkDistance() {
  char buffer[10];

  long duration = pulseIn(echoPin, HIGH);
  if (duration == 0) return;

  float distance = (duration * 0.0343) / 2;
  Serial.print("Distance: ");
  Serial.println(distance);

  dtostrf(distance, 4, 2, buffer); 
  client.publish("arduino/ultrasonic_sensor", buffer);
}
