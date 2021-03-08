#ifndef TURRET_H
#define TURRET_H
#include "arduino.h"
#include <servo.h>

class Turret
{
private:
    Servo *pTilt;
    Servo *pPan;

public:
    Turret(Servo *servoForTilt, Servo *servoForPan);
    void serialPrintInfo();
    void tilt(uint16_t angle);
    void pan(uint16_t angle);
    void tiltSetIdle(bool idle);
    void panSetIdle(bool idle);
};

#endif