#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include "UltrasonicSensor.h"
#include "StatusPublisher.h"
#include "StepMotor.h"
#include "LightSensor.h"
#include "LEDStrip.h"
#include <Servo.h>

// Network configuration
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 50);
IPAddress server(192, 168, 1, 100);

EthernetClient ethClient;
PubSubClient client(ethClient);

UltrasonicSensor sensor(2, 6, client); // trigger pin, echo pin
StatusPublisher statusPublisher(client);
StepMotor stepMotor(4, 10);  // Set Pin, distance threshold
LightSensor lightSensor(3, A0, client); // digital pin, analog pin
LEDStrip ledStrip(13, 500); // Trigger pin, threshold to toggle LEDs



void mqttCallback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.print("Received message on topic: ");
  Serial.print(topic);
  Serial.print(" -> ");
  Serial.println(String(message));

  if (String(topic) == "arduino/ultrasonic_sensor") {
    // No message gets delivered here, only command to toggle the door
    stepMotor.handleCommand(message);
  } else if (String(topic) == "arduino/light_sensor") {
    ledStrip.handleCommand(message);
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    if (client.connect("arduinoClient")) {
      Serial.println("Connected to MQTT broker");
      client.subscribe("arduino/ultrasonic_sensor");
      client.subscribe("arduino/light_sensor");
      Serial.println("Subscribed to topics");
    } else {
      Serial.print("Connection failed, rc=");
      Serial.println(client.state());
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  client.setServer(server, 1883);
  client.setCallback(mqttCallback);

  sensor.begin();
  lightSensor.begin();
  stepMotor.begin();
  ledStrip.begin();
  Serial.println("Setup completed");
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  sensor.checkDistance();
  lightSensor.readAndPublish();
  statusPublisher.publishStatus();
}
