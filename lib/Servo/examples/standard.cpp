#include <Arduino.h>

#include <servo.h>

/*

This sketch show how to control a standard servo which 
has a travel distance of 120°. Servo "Tower Pro Mg 995"
would be considered a standard servo.


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


Example connection when NO USB is connected: 

GND                    +5V
 │                       │                         
 │   ╔═════░░════╗       │     ╔═══════════╗
 │   ║  -ESP32-  ║       │     ║ - Servo - ║
 |   ║           ║       │     ║           ║
 │   ║ 3V3   VIN ╟──┬────┴─────╢ VCC       ║
 |   ║           ║  ┴ +        ║           ║
 |   ║           ║  ┬ -        ║           ║
 │   ║ GND   GND ╟──┴──────────╢ GND   GND ╟─┐
 |   ║ D5    D13 ╟─────────────╢ Signal    ║ │
 |   ╚═══════════╝             ╚═══════════╝ │
 └───────────────────────────────────────────┘

Best would be that the Esp32 would get it's own power source
but if that is not possible put a fairly big capacitor as 
close as you can, to the VIN and GND on the Esp32.

*/

//debugging
Servo towerProMg995(13, 120, 1, "mg995");

//not debugging
//Servo towerProMg995(13, 120, 1);

void showMenu()
{
    Serial.println("   ---------------------------------------------------- ");
    Serial.println("  | If you type the following numbers and press return |");
    Serial.println("  | you will give the servos the following commands.   |");
    Serial.println("   ---------------------------------------------------- ");
    Serial.println();
    Serial.println();
    Serial.println("     ----------------------------------------------- ");
    Serial.println("    |  Number  Command                              |");
    Serial.println("    | 0 - 360  change servo angle to n°             |");
    Serial.println("    |    1000  This command menu                    |");
    Serial.println("    |    2000  Print all servo properties           |");
    Serial.println("    |    3000  Disable servo and enable idle mode.  |");
    Serial.println("    |    3001  Enable servo and disable idle mode.  |");
    Serial.println("     ----------------------------------------------- ");
}

void setup()
{
    Serial.begin(115200);
    delay(1000);
    towerProMg995.setAngle(0);
    showMenu();
}

void loop()
{
    if (Serial.available() > 0)
    {
        int angle = Serial.parseInt();
        Serial.read();
        Serial.println(angle);
        switch (angle)
        {
        case 1000:
            showMenu();
            break;
        case 2000:
            towerProMg995.serialPrintInfo();
            break;
        case 3000:
                Serial.println("Setting servos to Idle");
                towerProMg995.setIdle(true);
                break;
        case 3001:
            Serial.println("Activating servos");
            towerProMg995.setIdle(false);
            break;

        default:
            towerProMg995.setAngle(angle);
        }
    }
}
