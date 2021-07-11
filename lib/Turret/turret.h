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
    unsigned long _blinkTime = 0;
    unsigned long _blinkTimerInterval = 0;
    unsigned long _blinkTimerCounter = 0;
    unsigned long _blinkTimerTempValue = 0;
    unsigned long _maxPowerOnTime = 5 * 60 * 1000; //Default max on time is 5 minutes
    unsigned long _laserTurnOffTime = 0;

    void setServoConstraint(Servo *pServo, uint16_t minAngle, uint16_t maxAngle);
    void ledcAnalogWrite(uint8_t channel, uint32_t value, uint32_t valueMax);
    void runUpdateBlinkTimerFunction();
    bool isValidNumber(String str);
    void setLaserIntensityBlink(uint16_t intensity);
    Point getCirclePoint(int radius, Point center, int angle);
public:
    Turret(Servo *servoForTilt, Servo *servoForPan, uint16_t laserPin, uint16_t laserChannel);
    void serialPrintInfo();
    void tilt(uint16_t angle);
    void pan(uint16_t angle);
    void panAndTilt(uint16_t panAngle, uint16_t tiltAngle, uint32_t delayMs = 0);
    uint16_t getLaserIntensity() { return _laserPinValue; }
    bool isLaserOn(bool debugPrint = false);
    void setLaserIntensity(uint16_t intensity);
    void setTiltConstraint(uint16_t minAngle, uint16_t maxAngle);
    void setPanConstraint(uint16_t minAngle, uint16_t maxAngle);
    void tiltPowerOn(bool powerOn);
    void panPowerOn(bool powerOn);
    void powerLaser(bool powerOn);
    void setLaserMaximumOnTime(unsigned long maxPowerOnTimeMs);
    unsigned long getLaserTunOffTime(){return _laserTurnOffTime; };
    
    bool parseSetUrlAndExecute(const char *url, bool removeTrailingHTTP);
    bool parseMoveUrlAndExecute(const char *url, bool removeTrailingHTTP);
    bool parseActivateUrlAndExecute(const char *url, bool removeTrailingHTTP);
    bool parseGridUrlAndExecute(const char *url, bool removeTrailingHTTP);
    String getQueryParameterValue(String url, String parameterName);
    void updateTimers();
    void setBlink(long intervalInMilliseconds);
    
};

#endif