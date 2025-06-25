#include "UltrasonicSensor.h"
#include <Arduino.h>

UltrasonicSensor::UltrasonicSensor(int trig, int echo, PubSubClient& mqttClient)
  : trigPin(trig), echoPin(echo), client(mqttClient) {}

void UltrasonicSensor::begin() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}



void UltrasonicSensor::checkDistance() {

  unsigned long now = millis();
  if(now - lastTest < timeDif){
    return;
  }
  lastTest = now;

  char buffer[10];

  // This is essential :)
  // The outgoing beam of the sensor
  digitalWrite(trigPin, LOW);  
	delayMicroseconds(2);  
	digitalWrite(trigPin, HIGH);  
	delayMicroseconds(10);  
	digitalWrite(trigPin, LOW);  

  // The measurement
  long duration = pulseIn(echoPin, HIGH);
  if (duration == 0) return;

  // distance equals duration times speed of sound in air (m/s), divided by two, as duration measures both ways (there and back again)
  // output should be comparable to cm
  float distance = (duration * 0.0343) / 2; 


  // sending the float values made strange errors occur
  dtostrf(distance, 4, 2, buffer); 

  Serial.print("Distance: ");
  Serial.println(distance);
  client.publish("arduino/ultrasonic_sensor", buffer);
}
