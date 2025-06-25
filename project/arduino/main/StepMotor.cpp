#include "StepMotor.h"
#include <Arduino.h>

StepMotor::StepMotor(int pin, int thresholdVal) 
: servoPin(pin), threshold(thresholdVal) {}


void StepMotor::begin() {
  myServo.attach(servoPin);
}

void StepMotor::switchState() {
    // negative values move the servo against the clock (at least in this setup)
    // positive values move with the clock
  if (state == "open") {
    myServo.write(120); // Adjust angle as needed, this works well with a little overshoot
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


  if(distance > 0 && distance < threshold){ // Zero values indicate wrong measurements and should not get here
    if (now - lastMovement > cooldown) { 
      switchState();
      lastMovement = now;
    } else {
      Serial.println("StepMotor: Cooldown active, ignoring command.");
    }
  }
}