#ifndef SERVO_H
#define SERVO_H
#include "arduino.h"

/**
 * @brief This library is for driving servos from the esp32 micro controller.
 * It will not work with other arduino boards like the UNO, nano mega ect.
 * It uses the 
 * 
 */
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
   bool _isIdle = false;
   const char *_name = NULL;
   bool _debugging = false;

   /**
     * @brief Converts angle in degrees to a PWM signal. 
     * 
     * @param angle - in degrees
     * @return int
     */
   int angleToDutyCycle(uint16_t angle);
   int angleToOnPeriod(uint16_t angle);
   void init(uint16_t pin, uint16_t maxAngle, uint16_t channel, uint16_t minUs, uint16_t maxUs, const char *name);

public:
   /**
     * @brief Construct a new Servo object and enable debugging.
     * 
     * @param pin - Signal pin of the microcontroller which the signal wire on the servo is connected to.
     * @param maxAngle - What is the maximum travel distance/rang in degrees of the servo.
     * @param channel - Choose the pulse width modulation channel (0-7) which should be used to generate the PWM signal for the servo pin.  
     * @param minUs - Mininum pulse width in micro seconds - for angle 0°.
     * @param maxUs - Maximum pulse width - for max angle.
     * @param strName - Gives the servo a name and activates the Servo debug mode, resulting an a Serial println statements when giving the servo a command.
     */
   Servo(uint16_t pin, uint16_t maxAngle, uint16_t channel, uint16_t minUs, uint16_t maxUs, const char *strName);

   /**
     * @brief Construct a new Servo object.
     * 
     * @param pin - Signal pin of the microcontroller which the signal wire on the servo is connected to.
     * @param maxAngle - What is the maximum travel distance/rang in degrees of the servo.
     * @param channel - Choose the pulse width modulation channel (0-7) which should be used to generate the PWM signal for the servo pin.  
     * @param minUs - Mininum pulse width in micro seconds - for angle 0°.
     * @param maxUs - Maximum pulse width - for max angle.
     */
   Servo(uint16_t pin, uint16_t maxAngle, uint16_t channel, uint16_t minUs, uint16_t maxUs);

   /**
     * @brief Construct a new Servo object and enable debugging.
     * 
     * Note, using this constructor will set the min and max pulse widths to the default, which are min=1000 (1ms) and max=2000(2ms).
     * 
     * @param pin - Signal pin of the microcontroller which the signal wire on the servo is connected to.
     * @param maxAngle - What is the maximum travel distance/rang in degrees of the servo.
     * @param channel - Choose the pulse width modulation channel (0-7) which should be used to generate the PWM signal for the servo pin.  
     * @param strName - Gives the servo a name and activates the Servo debug mode, resulting an a Serial println statements when giving the servo a command.
     */
   Servo(uint16_t pin, uint16_t maxAngle, uint16_t channel, const char *strName);

   /**
     * @brief Construct a new Servo object
     * 
     * Note, using this constructor will set the min and max pulse widths to the default, which are min=1000 (1ms) and max=2000(2ms).
     * 
     * @param pin - Signal pin of the microcontroller which the signal wire on the servo is connected to.
     * @param maxAngle - What is the maximum travel distance/rang in degrees of the servo.
     * @param channel - Choose the pulse width modulation channel (0-7) which should be used to generate the PWM signal for the servo pin.  
     */
   Servo(uint16_t pin, uint16_t maxAngle, uint16_t channel);

   /**
     * @brief Move the servo to a specified angle.
     * 
     * @param angle - angle in degrees
     */
   void setAngle(uint16_t angle);

   /**
     * @brief Get the current angle of the servo.
     * 
     * @return uint16_t 
     */
   uint16_t getAngle() { return _angle; }

   /**
     * @brief Set the server debugging mode on or off. setting it on 
     * will add print serial statements when executing commands.
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

   /**
    * @brief Get if the servo is set to idle or not.
    * 
    * @return true 
    * @return false 
    */
   bool getIdle() { return _isIdle; }

   /**
    * @brief Sets the servo to Idle state or not.
    * 
    * @param idle - If false, 
    *                 the servo will be set active and it will move to 
    *                 what ever angle it has been set to previously.
    *             If true the servo will be set to idle state.
    *                 This could result in a movement on the servo, 
    *                 but after that movement all jittering should stop.
    * 
    */
   void setIdle(bool idle);
   /**
    * @brief Prints out all properies of this object to the serial.
    * 
    */
   void serialPrintInfo();
};

#endif
