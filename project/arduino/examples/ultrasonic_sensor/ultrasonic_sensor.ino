#include <Servo.h>

Servo myServo;
const int servoPin = 4;

const int trigPin = 2;  
const int echoPin = 6; 
float duration, distance;  


void setup() {  
	myServo.attach(servoPin);
	pinMode(trigPin, OUTPUT);  
	pinMode(echoPin, INPUT);  
	Serial.begin(9600);  
}  


void loop() {  
	digitalWrite(trigPin, LOW);  
	delayMicroseconds(2);  
	digitalWrite(trigPin, HIGH);  
	delayMicroseconds(10);  
	digitalWrite(trigPin, LOW);  
  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;  
  Serial.print("Distance: ");  
	Serial.println(distance);


}  
