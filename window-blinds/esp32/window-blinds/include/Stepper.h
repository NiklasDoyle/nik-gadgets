#include <AccelStepper.h>

#define MOTOR_INTERFACE_TYPE 1

class Stepper {
public:
    Stepper(int dirPin, int stepPin, int msPinA, int msPinB, int msPinC, int sleepPin, int msInc);
    bool run();
    void setMicroStepIncrements(int inc);
    void setRotations(int rotations);

private:
    int dirPin;
    int stepPin;
    int msPinA;
    int msPinB;
    int msPinC;
    int sleepPin;

    int msInc;
    int rotations;

    AccelStepper* accelStepper;
};