#include <Arduino.h>

#include "servo.h"

//debugging
Servo towerProSg90(12, 180, 0, 500, 2400, "sg90");
Servo towerProMg995(13, 120, 1, "mg995");

//not debugging
//Servo towerProSg90(12, 180, 0, 500, 2400);
//Servo towerProMg995(13, 120, 1);

const int ledPin = 2;
const int laserPin = 15;

void showLaser(bool activate)
{
  digitalWrite(ledPin, activate);
  digitalWrite(laserPin, activate);
}

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
  Serial.println("    |    4000  Turn laser off.                      |");
  Serial.println("    |    4001  Turn laser on.                       |");
  Serial.println("     ----------------------------------------------- ");
}

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(laserPin, OUTPUT);
  showLaser(true);
  Serial.begin(115200);
  delay(1000);
  towerProSg90.setAngle(0);
  towerProMg995.setAngle(0);
  towerProSg90.setIdle(true);
  towerProMg995.setIdle(true);
  showLaser(false);
  showMenu();
}

void loop()
{
  if (Serial.available() > 0)
  {
    int angle = Serial.parseInt();
    Serial.read();
    Serial.println(angle);
    if (angle == 4000 || angle == 4001)
    {
      bool laserOn = (angle == 4001);
      Serial.println(laserOn ? "Turning laser on" : "Turning laser off");
      showLaser(laserOn);
    }
    else if (angle == 3000 || angle == 3001)
    {
      bool idleOn = (angle == 3000);
      Serial.println(idleOn ? "Setting servos to Idle" : "Activating servos");
      towerProSg90.setIdle(idleOn);
      towerProMg995.setIdle(idleOn);
    }
    
    else if (angle == 2000)
    {
      towerProSg90.serialPrintInfo();
      towerProMg995.serialPrintInfo();
    }
    else if (angle == 1000)
    {
      showMenu();
    }
    else
    {
      towerProSg90.setAngle(angle);
      towerProMg995.setAngle(angle);
    }
  }
}
