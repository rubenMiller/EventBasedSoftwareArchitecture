#pragma once
#include <Arduino.h>
#include <Servo.h>

class StepMotor {
  int servoPin;
  int threshold;
  Servo myServo;
  String state = "closed"; 
  unsigned long lastMovement = 0;
  const unsigned long cooldown = 2500;

void switchState();

public:
  StepMotor(int pin, int threshold = 10);
  void begin();
  void handleCommand(const String& message);  // To be implemented
};
