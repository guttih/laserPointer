#include "servo.h"

/**
 * @brief Construct a new Servo:: Servo object
 * 
 * @param pin 
 * @param maxAngle 
 * @param channel 
 */
Servo::Servo(uint8_t pin, uint16_t maxAngle, uint8_t channel)
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
Servo::Servo(uint8_t pin, uint16_t maxAngle, uint8_t channel, const char *strName)
{
  _name = strName;
  setDebugMode(true);
  init(pin, maxAngle, channel);
}

void Servo::setDebugMode(bool activate)
{
  _debugging = activate;
}

void Servo::init(uint8_t pin, uint16_t maxAngle, uint8_t channel)
{
  _pin = pin;
  _maxAngle = maxAngle;
  _channel = channel;
  _angle = 0;
  _debugging = false;
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
  int ms = 1000 + (angle * 1000) / _maxAngle;
  int duty = (65535 * ms) / 20000;
  return duty;
}
