// This is a more or less working example 
// connects to the server and sends messages
// The display does not work as intended

#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Ethernet configuration
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 50);  // Arduino IP
IPAddress server(192, 168, 1, 100); // Your PC running Mosquitto

EthernetClient ethClient;
PubSubClient client(ethClient);

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
  lcd.begin(16, 2); // Initializes the LCD with 16 columns and 2 rows
  lcd.setCursor(0,0);
  lcd.print("starting ...");
  delay(1000);  

  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  client.setServer(server, 1883);


  lcd.setCursor(0,0);
  lcd.print("finished setup.");
  delay(100);  
}

void loop() {
  if (!client.connected()) {
    reconnect();
    lcd.setCursor(0,0);
    lcd.println("reconnecting ...");
  }
  client.loop();


  // Publish message every 5 seconds
  static unsigned long lastMsg = 0;
  if (millis() - lastMsg > 5000) {
    lastMsg = millis();
    String payload = "Hello from Arduino at " + String(millis());
    client.publish("arduino/status", payload.c_str());
    Serial.println("Published: " + payload);

    lcd.setCursor(0,0);
    lcd.print("Published");

  }
}