#include <Arduino.h>

#include <servo.h>

/*

This sketch show how to control a standard servo which 
has a travel distance of 120°. 


Connecting the ESP32 to a servo.

Note, use separate power supply for the servo motor, the
Esp32 will not be able to power the servo from it's VIN pin.


Example connection when a USB is connected:

GND        USB           +5V
 │                       │                         
 │   ╔═════░░════╗       │     ╔═══════════╗
 │   ║  -ESP32-  ║       │     ║ - Servo - ║
 |   ║           ║       │     ║           ║
 │   ║ 3V3   VIN ║       └─────╢ VCC       ║
 |   ║           ║             ║           ║
 |   ║           ║             ║           ║
 │   ║ GND   GND ╟─────────────╢ GND   GND ╟─┐
 |   ║ D5    D13 ╟─────────────╢ Signal    ║ │
 |   ╚═══════════╝             ╚═══════════╝ │
 └───────────────────────────────────────────┘        

*/
const int maxAngle = 120;
Servo servo(13, maxAngle, 0);
int angle = 0;

void setup()
{
    delay(1000);
    servo.setAngle(0);
}

void loop()
{
    delay(1000);
    angle = angle + 30;
    if (angle > maxAngle)
        angle = 0;
    servo.setAngle(angle);
}
