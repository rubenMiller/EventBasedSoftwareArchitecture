#pragma once
#include <Servo.h>

class StepMotor {
  int servoPin;
  Servo myServo;

public:
  StepMotor(int pin);
  void begin();
  void handleCommand();  // To be implemented
};
