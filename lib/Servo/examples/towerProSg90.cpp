#include <Arduino.h>

#include <servo.h>

/*

This sketch show how to control Tower Pro Sg 90 
which has a travel distance of 180°. 

Servo "Tower Pro Sg 90" characteristics.
      0°   is about  500 micro seconds duty cycle on 20 ms. PMW period.
    180°   is about 2400 micro seconds duty cycle on 20 ms. PMW period.


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
const int maxAngle = 180;
Servo towerProSg90(13, 180, 0, 500, 2400);
int angle = 0;

void setup()
{
    delay(1000);
    towerProSg90.setAngle(0);
}

void loop()
{
    delay(1000);
    angle = angle + 30;  // 6 changes, then reset
    if (angle > maxAngle)
        angle = 0;
    towerProSg90.setAngle(angle);
}
