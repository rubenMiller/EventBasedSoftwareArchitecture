// This is a more or less working example 
// connects to the server and sends messages
// The display does not work as intended

#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>


// Ethernet configuration
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 50);  // Arduino IP
IPAddress server(192, 168, 1, 100); // Your PC running Mosquitto

EthernetClient ethClient;
PubSubClient client(ethClient);


// Pin Configurations

// Servo
Servo myServo;
const int servoPin = 4;

// Ultrasonic sensor
const int trigPin = 2;  
const int echoPin = 3;

void reconnect() {
  // Loop until reconnected
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    if (client.connect("arduinoClient")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.println(client.state());
      delay(5000);
    }
  }
}

void setup() {

  Serial.println("Starting the Arduino");
  Serial.begin(9600);

  // Ethernet setup
  Ethernet.begin(mac, ip);
  client.setServer(server, 1883);


  // Ultrasonic sensor setup
  pinMode(trigPin, OUTPUT);  
  pinMode(echoPin, INPUT);  

  // Servomotor for door setup
  myServo.attach(servoPin);


  Serial.println("Finished setup");
}

void loop() {
  if (!client.connected()) {
    Serial.println("reconnecting...");
    reconnect();
  }
  client.loop();

  // Ultrasonic sensor logic
  float duration = pulseIn(echoPin, HIGH)
  if(duration == 0.0){
    float distance = (duration*.0343)/2;
    Serial.print("Distance: ");  
	Serial.println(distance);
    if(distance > 0 && distance < 10){
        Serial.println("Detected something close, publishing a message.");
        client.publish("arduino/ultrasonic_sensor", true);
        Serial.println("Published true to 'arduino/ultrasonic_sensor'.");
    }
  }


  // Publish message every 5 seconds
  // For the status
  static unsigned long lastMsg = 0;
  if (millis() - lastMsg > 5000) {
    lastMsg = millis();
    String payload = "Hello from Arduino at " + String(millis());
    client.publish("arduino/status", payload.c_str());
    Serial.println("Published: " + payload);
  }
}