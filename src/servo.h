#ifndef SERVO_H
#define SERVO_H
#include "arduino.h"

class Servo
{
private:
  uint16_t _pin;
  uint16_t _channel;
  uint16_t _angle;
  uint16_t _maxAngle;
  uint16_t _minUs = 1000;
  uint16_t _maxUs = 2000;
  uint16_t _periodUs = 20000;
  const char *_name = NULL;
  bool _debugging = false;

  /**
     * @brief Converts angle in degrees to a PWM signal.
     * 
     * @param angle - in degrees
     * @return int 
     */
  int angleToDutyCycle(uint16_t angle);
  void init(uint16_t pin, uint16_t maxAngle, uint16_t channel);

public:
  /**
     * @brief Construct a new Servo object
     * 
     * Note when you are testing your application you can #define debugging above the #include "servo.h" to get extra debugging information.
     * 
     * @param pin - Signal pin of the microcontroller which the signal wire on the servo is connected to.
     * @param maxAngle - What is the maximum travel distance/rang in degrees of the servo.
     * @param minUs - Mininum pulse width in micro seconds - for angle 0°.
     * @param maxUs - Maximum pulse width - for max angle.
     * @param channel - Choose the pulse width modulation channel (0-7) which should be used to generate the PWM signal for the servo pin.  
     */
  Servo(uint16_t pin, uint16_t maxAngle, uint16_t channel, uint16_t minUs, uint16_t maxUs, const char *strName);
  Servo(uint16_t pin, uint16_t maxAngle, uint16_t channel, const char *strName);
  Servo(uint16_t pin, uint16_t maxAngle, uint16_t channel);

  /**
     * @brief Move the servo to a specified angle.
     * 
     * @param angle - angle in degrees
     */
  void setAngle(uint16_t angle);

  /**
     * @brief Set the server debugging mode on or off
     *  setting it on will add print serial statements when executing commands.
     * 
     * @param activate 
     */
  void setDebugMode(bool activate);
  /**
     * @brief Get the Pin number this servo is connected to.
     * 
     * @return uint8_t 
     */
  uint8_t getPin() { return _pin; }
  /**
     * @brief Get the PWM Channel this pin is connected to.
     * 
     * @return uint8_t 
     */
  uint8_t getChannel() { return _channel; }
  /**
     * @brief Get the maximum travel Angle of the servo.
     * 
     * @return uint16_t 
     */
  uint16_t getMaxAngle() { return _maxAngle; }
  /**
     * @brief Get the current angle of the servo.
     * 
     * @return uint16_t 
     */
  uint16_t getAngle() { return _angle; }

  /**
     * @brief Sets the PWM period length in micro seconds.
     * Default is 20000 which is 20ms which is 20000µs.
     * 
     * @param period 
     */
  void setPWMPeriod(uint16_t period) { _periodUs = period; };

  /**
   * @brief Gets the PWM period length in micro seconds
   * 
   * @return uint16_t 
   */
  uint16_t getPWMPeriod() { return _periodUs; }
};

#endif
