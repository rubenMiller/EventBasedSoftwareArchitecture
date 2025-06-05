#include <Servo.h>

Servo myServo;
const int servoPin = 4;

const int trigPin = 2;  
const int echoPin = 3; 
float duration, distance;  
bool test = true;


void setup() {  
	myServo.attach(servoPin);
	pinMode(trigPin, OUTPUT);  
	pinMode(echoPin, INPUT);  
	Serial.begin(9600);  
}  


void loop() {  
  if(test == true)
  {
    int distance = -120;
    Serial.println("Moving stepmotor");
    myServo.write(distance);
    Serial.print("Moved by: ");
    Serial.println(distance);
    test = false;
  }

}  
