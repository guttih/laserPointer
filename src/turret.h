#ifndef TURRET_H
#define TURRET_H
#include "arduino.h"
#include <servo.h>

class Turret
{
private:
    Servo *pTilt;
    Servo *pPan;
    uint16_t _laserPin;

public:
    Turret(Servo *servoForTilt, Servo *servoForPan, uint16_t laserPin);
    void serialPrintInfo();
    void tilt(uint16_t angle);
    void pan(uint16_t angle);
    void tiltPowerOn(bool powerOn);
    void panPowerOn(bool powerOn);
    void powerLaser(bool powerOn);
    bool parseUrlAndExecute(const char *url, bool removeTrailingHTTP);
    String getQueryParameterValue(String url, String parameterName);
    bool isValidNumber(String str);
    
};

#endif