#include "StepMotor.h"
#include <Arduino.h>

StepMotor::StepMotor(int pin, int thresholdVal) 
: servoPin(pin), threshold(thresholdVal) {}


void StepMotor::begin() {
  myServo.attach(servoPin);
}

void StepMotor::switchState() {
    // -120 moves 120 degree against the clock
    // 120 moves with the clock
  if (state == "open") {
    myServo.write(120); // Adjust angle as needed
    Serial.println("StepMotor: Command received, state: " + state + ", therfore door gets closed.");
    state = "closed";

  } else if (state == "closed") {
    myServo.write(-120); // opening our door is against the clock
    Serial.println("StepMotor: Command received, state: " + state + ", therfore door gets opened.");
    state = "open";

  } else {
    Serial.print("StepMotor: Unknown state -> ");
    Serial.println(state);
  }
}

void StepMotor::handleCommand(const String& message) {
  int distance = message.toInt();
  unsigned long now = millis();


  if(distance > 0 && distance < threshold){
    if (now - lastMovement > cooldown) {
      switchState();
      lastMovement = now;
    } else {
      Serial.println("StepMotor: Cooldown active, ignoring command.");
    }
  }
}