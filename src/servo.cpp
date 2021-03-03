#include "servo.h"

/**
 * @brief Construct a new Servo:: Servo object
 * 
 * @param pin 
 * @param maxAngle 
 * @param channel 
 */
Servo::Servo(uint16_t pin, uint16_t maxAngle, uint16_t channel)
{
  init(pin, maxAngle, channel);
}

/**
 * @brief Construct a new Servo object and give it a name for debugging purposes.
 * Using this constructor will automatically enable debugging which will print out
 * to the serial the angle, when it changes.  
 * 
 * @param pin 
 * @param maxAngle 
 * @param channel 
 * @param strName 
 */
Servo::Servo(uint16_t pin, uint16_t maxAngle, uint16_t channel, const char *strName)
{
  _name = strName;
  init(pin, maxAngle, channel);
  setDebugMode(true);
}

Servo::Servo(uint16_t pin, uint16_t maxAngle, uint16_t channel, uint16_t minUs, uint16_t maxUs, const char *strName)
{
  _name = strName;
  _minUs = minUs;
  _maxUs = maxUs;
  init(pin, maxAngle, channel);
  setDebugMode(true);
}

void Servo::setDebugMode(bool activate)
{
  _debugging = activate;
}

void Servo::init(uint16_t pin, uint16_t maxAngle, uint16_t channel)
{
  _pin = pin;
  _maxAngle = maxAngle;
  _channel = channel;
  _angle = 0;
  setDebugMode(false);
  pinMode(_pin, OUTPUT);
  ledcAttachPin(_pin, _channel);
  ledcSetup(_channel, 50, 16);
}

void Servo::setAngle(uint16_t angle)
{
  _angle = min(angle, _maxAngle);
  if (_debugging)
  {
    if (_name)
      Serial.print(_name);

    Serial.print(" setting angle ");
    Serial.println(_angle);
  }

  ledcWrite(_channel, angleToDutyCycle(_angle));
}

int Servo::angleToDutyCycle(uint16_t angle)
{
  float tickLength = (_maxUs - _minUs) / _maxAngle;
  int us = _minUs + (angle * tickLength);
  int duty = (65535 * us) / _periodUs;
  return duty;
}
