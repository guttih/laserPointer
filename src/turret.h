#ifndef TURRET_H
#define TURRET_H
#include "arduino.h"
#include <servo.h>

class Turret
{
private:
    Servo *pTilt;
    Servo *pPan;
    uint16_t panMinAngle = 0;
    uint16_t panMaxAngle = 0;
    uint16_t tiltMinAngle = 0;
    uint16_t tiltMaxAngle = 0;
    uint16_t _laserPin;

    bool setServoConstraint(Servo *pServo, uint16_t minAngle, uint16_t maxAngle);

public:
    Turret(Servo *servoForTilt, Servo *servoForPan, uint16_t laserPin);
    void serialPrintInfo();
    void tilt(uint16_t angle);
    void pan(uint16_t angle);
    bool setTiltConstraint(uint16_t minAngle, uint16_t maxAngle);
    bool setPanConstraint(uint16_t minAngle, uint16_t maxAngle);
    void tiltPowerOn(bool powerOn);
    void panPowerOn(bool powerOn);
    void powerLaser(bool powerOn);
    bool parseMoveUrlAndExecute(const char *url, bool removeTrailingHTTP);
    bool parseActivateUrlAndExecute(const char *url, bool removeTrailingHTTP);
    String getQueryParameterValue(String url, String parameterName);
    bool isValidNumber(String str);
    
};

#endif