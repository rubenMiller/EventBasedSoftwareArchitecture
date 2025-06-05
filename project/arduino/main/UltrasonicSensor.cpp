#include "UltrasonicSensor.h"
#include <Arduino.h>

UltrasonicSensor::UltrasonicSensor(int trig, int echo, PubSubClient& mqttClient)
  : trigPin(trig), echoPin(echo), client(mqttClient) {}

void UltrasonicSensor::begin() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void UltrasonicSensor::checkDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  if (duration == 0) return;

  float distance = (duration * 0.0343) / 2;
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance > 0 && distance < 10) {
    client.publish("arduino/ultrasonic_sensor", "true");
    Serial.println("Published true to 'arduino/ultrasonic_sensor'.");
  }
}
