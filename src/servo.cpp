#include "servo.h"

Servo::Servo(uint8_t pin, uint16_t maxAngle, uint8_t channel)
{
  init(pin, maxAngle, channel);
}

void Servo::init(uint8_t pin, uint16_t maxAngle, uint8_t channel)
{
  _pin = pin;
  _maxAngle = maxAngle;
  _channel = channel;
  _angle = 0;
  pinMode(_pin, OUTPUT);
  ledcAttachPin(_pin, _channel);
  ledcSetup(_channel, 50, 16);
}

void Servo::setAngle(uint16_t angle) {
  _angle = min(angle, _maxAngle);
  Serial.print("setting angle ");Serial.println(_angle);
  ledcWrite(1, angleToDutyCycle(_angle));
  
}

int Servo::angleToDutyCycle(uint16_t angle) {
  int ms = 1000 + (angle * 1000) / _maxAngle;
  int duty = (65535 * ms) / 20000;
  return duty;
}
