#ifndef SERVO_H
#define SERVO_H
#include "arduino.h"
class Servo
{
  public:
    Servo(uint8_t pin, uint16_t maxAngle, uint8_t channel);
    void setAngle(uint16_t angle);
    uint8_t  getPin(){ return _pin;}
    uint8_t  getChannel(){ return _channel;}
    uint16_t getMaxAngle(){ return _maxAngle;}
    uint16_t getAngle(){ return _angle;}
  private:
    uint8_t  _pin;
    uint8_t _channel;
    uint16_t _angle;
    uint16_t _maxAngle;
    int angleToDutyCycle(uint16_t angle);
    void init (uint8_t pin, uint16_t maxAngle, uint8_t channel);
};

#endif
