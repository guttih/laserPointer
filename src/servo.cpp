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
  //use the defaults
  init(pin, maxAngle, channel, _minUs, _maxUs, _name);
}

/**
 * @brief Construct a new Servo object and give it a name for debugging purposes.
 * Using this constructor will automatically enable debugging which will print out
 * to the serial the angle, when it changes.  
 * 
 * @param pin 
 * @param maxAngle 
 * @param channel 
 * @param name 
 */
Servo::Servo(uint16_t pin, uint16_t maxAngle, uint16_t channel, const char *name)
{
  //use the defaults
  init(pin, maxAngle, channel, _minUs, _maxUs, name);
}

Servo::Servo(uint16_t pin, uint16_t maxAngle, uint16_t channel, uint16_t minUs, uint16_t maxUs, const char *name)
{
  init(pin, maxAngle, channel, minUs, maxUs, name);
}

void Servo::setDebugMode(bool activate)
{
  _debugging = activate;
}

void Servo::init(uint16_t pin, uint16_t maxAngle, uint16_t channel, uint16_t minUs, uint16_t maxUs, const char *name)
{
  _angle = 0;
  _pin = pin;
  _maxAngle = maxAngle;
  _channel = channel;
  _minUs = minUs;
  _maxUs = maxUs;
  _name = name;
  setDebugMode(_name != NULL);
  pinMode(_pin, OUTPUT);
  ledcAttachPin(_pin, _channel);
  ledcSetup(_channel, 50, 16);
}

void Servo::setAngle(uint16_t angle)
{
  _angle = min(angle, _maxAngle);
  if (_debugging)
  {
    if (_isIdle)
      Serial.print("Servo is set to Idle, ");
    if (_name)
      Serial.print(_name);

    Serial.print(" setting angle ");
    Serial.println(_angle);
  }

  ledcWrite(_channel, angleToDutyCycle(_angle));
}

int Servo::angleToOnPeriod(uint16_t angle)
{
  float tickLength = (_maxUs - _minUs) / (float)_maxAngle;
  int us = _minUs + ((angle * tickLength) + 0.5); //+0.5 for rounding
  return us;
}
int Servo::angleToDutyCycle(uint16_t angle)
{
  if (_isIdle)
    return 0; // The servo motor has been set to idle.

  int us = angleToOnPeriod(angle);
  int duty = (65535 * us) / _periodUs;
  return duty;
}

void Servo::setIdle(bool idle)
{
  _isIdle = idle;
  if (_debugging)
  {
    if (_name)
      Serial.print(String(_name) + ": ");
    Serial.print("Setting idle to ");
    Serial.println(_isIdle);
  }

  if (_isIdle)
  {
    ledcWrite(_channel, 0);
  }
  else
    setAngle(_angle);
};
void Servo::serialPrintInfo()
{
  Serial.println("-------------------");
  if (_name)
    Serial.println(String(" name     : ") + _name);
  Serial.println(String(" pin       : ") + _pin);
  Serial.println(String(" channel   : ") + _channel);
  Serial.println(String(" angle     : ") + _angle);
  Serial.println(String(" dutyCycle : ") + angleToDutyCycle(_angle));
  Serial.println(String(" onPeriodUs: ") + angleToOnPeriod(_angle));
  Serial.println(String(" maxAngle  : ") + _maxAngle);
  Serial.println(String(" minUs     : ") + _minUs);
  Serial.println(String(" maxUs     : ") + _maxUs);
  Serial.println(String(" periodUs  : ") + _periodUs);
  Serial.println(String(" isIdle    : ") + (_isIdle ? "true" : "false"));
  Serial.println(String(" debugging : ") + (_debugging ? "true" : "false"));
  Serial.println("-------------------");
}