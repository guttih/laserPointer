#ifndef TURRET_H
#define TURRET_H
#include "arduino.h"
#include <servo.h>

#define TURRET_LEDC_TIMER_13_BIT  13
#define TURRET_LEDC_BASE_FREQ  8100


struct Point {
     int x = 0;
     int y = 0;
};

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
    uint16_t _laserPinValue;
    uint16_t _laserChannel;
    unsigned long _timer = 0;
    unsigned long _timerInterval = 0;
    unsigned long _timerTempValue = 0;
    unsigned long _timerCounter = 0;

    bool setServoConstraint(Servo *pServo, uint16_t minAngle, uint16_t maxAngle);
    void ledcAnalogWrite(uint8_t channel, uint32_t value, uint32_t valueMax);
    void runUpdateTimerFunction();
public:
    Turret(Servo *servoForTilt, Servo *servoForPan, uint16_t laserPin, uint16_t laserChannel);
    void serialPrintInfo();
    void tilt(uint16_t angle);
    void pan(uint16_t angle);
    void setLaserIntensity(uint16_t intensity);
    bool setTiltConstraint(uint16_t minAngle, uint16_t maxAngle);
    bool setPanConstraint(uint16_t minAngle, uint16_t maxAngle);
    void tiltPowerOn(bool powerOn);
    void panPowerOn(bool powerOn);
    void powerLaser(bool powerOn);
    bool parseSetUrlAndExecute(const char *url, bool removeTrailingHTTP);
    bool parseMoveUrlAndExecute(const char *url, bool removeTrailingHTTP);
    bool parseActivateUrlAndExecute(const char *url, bool removeTrailingHTTP);
    String getQueryParameterValue(String url, String parameterName);
    bool isValidNumber(String str);
    void updateTimer();
    void setBlink(long intervalInMilliseconds);
    
};

#endif