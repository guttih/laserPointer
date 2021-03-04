#ifndef TURRET_H
#define TURRET_H
#include "arduino.h"
#include <servo.h>

class Turret
{
private:
    Servo *pPan;
    Servo *pTilt;

public:
    Turret(Servo *servoForPan, Servo *servoForTilt);
    void serialPrintInfo();
};

#endif