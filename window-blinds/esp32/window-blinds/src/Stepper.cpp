#include <Arduino.h>
#include <Stepper.h>

  // Set Micro Stepper Mode 
  //  Full Step | Low Low Low 
  //  Half Step | High Low Low 
  //  Quarter Step | Low High Low 
  //  Eighth Step | High High Low 
  //  Sixteenth Step | High High High
  const int msConfigs[5][3] = {
      {LOW,  LOW,  LOW},  // Full Step
      {HIGH, LOW,  LOW},  // Half Step
      {LOW,  HIGH, LOW},  // Quarter Step
      {HIGH, HIGH, LOW},  // Eigth Step
      {HIGH, HIGH, HIGH}   // Sixteenth Step
  };

  Stepper::Stepper(int dirPin, int stepPin, int msPinA, int msPinB, int msPinC, int sleepPin, int msInc)
  {
    this->dirPin = dirPin;
    this->stepPin = stepPin;
    this->msPinA = msPinA;
    this->msPinB = msPinB;
    this->msPinC = msPinC;
    this->sleepPin = sleepPin;

    accelStepper = new AccelStepper(MOTOR_INTERFACE_TYPE, stepPin, dirPin);

    rotations = 2;

    accelStepper->setMaxSpeed(1000);
    accelStepper->setAcceleration(800);
    accelStepper->setSpeed(800);
    accelStepper->moveTo(800 * rotations); // 200 x 4

    setMicroStepIncrements(msInc); // Quarter Step
  }

void Stepper::setRotations(int rotations) {
    this->rotations = rotations;
}

bool Stepper::run() {
    if (accelStepper->distanceToGo() == 0) {
        accelStepper->moveTo(-accelStepper->currentPosition());
        return false;
    }

    accelStepper->run();

    return true;
}

void Stepper::setMicroStepIncrements(int inc) {
    msInc = inc;
    Serial.printf("Microstep mode set to: %d %d %d", msConfigs[inc][0], msConfigs[inc][1], msConfigs[inc][2]);
    digitalWrite(msPinA, msConfigs[inc][0]);
    digitalWrite(msPinB, msConfigs[inc][1]);
    digitalWrite(msPinC, msConfigs[inc][2]);
}