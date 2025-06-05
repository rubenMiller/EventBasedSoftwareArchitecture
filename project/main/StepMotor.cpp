#include "StepMotor.h"
#include <Arduino.h>

StepMotor::StepMotor(int pin) : servoPin(pin) {}

String state = "closed";

void StepMotor::begin() {
  myServo.attach(servoPin);
}

void StepMotor::handleCommand() {
    // -120 moves 120 degree against the clock
    // 120 moves with the clock
  if (state == "open") {
    myServo.write(120); // Adjust angle as needed
    Serial.println("StepMotor: Command received, state: " + state + ", therfore door gets closed.");
    state = "closed";
    delay(3000);
} else if (state == "closed") {
    myServo.write(-120); // opening our door is against the clock
    Serial.println("StepMotor: Command received, state: " + state + ", therfore door gets opened.");
    state = "open";
    delay(3000);
} else {
    Serial.print("StepMotor: Unknown state -> ");
    Serial.println(state);
  }
}