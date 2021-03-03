#include <Arduino.h>

#include "servo.h"

//debugging
Servo towerProSg90(12, 180, 0, 500, 2400, "sg90");
Servo towerProMg995(13, 120, 1, "mg995");

//not debugging
//Servo towerProSg90(12, 180, 0, 500, 2400);
//Servo towerProMg995(13, 120, 1);

const int ledPin = 2;

void setup()
{
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  Serial.begin(115200);
  delay(1000);
  towerProSg90.setAngle(0);
  towerProMg995.setAngle(0);
  digitalWrite(ledPin, LOW);
  Serial.println("   ---------------------------------------------------- ");
  Serial.println("  | If you type the following numbers and press return |");
  Serial.println("  | you will give the servos the following commands.   |");
  Serial.println("   ---------------------------------------------------- ");
  Serial.println();
  Serial.println();
  Serial.println("     ----------------------------------------------- ");
  Serial.println("    |  Number  Command                              |");
  Serial.println("    | 0 - 360  change servo angle to n°             |");
  Serial.println("    |    1000  Print all servo properties           |");
  Serial.println("    |    2000  Disable servo and enable idle mode.  |");
  Serial.println("    |    2001  Enable servo and disable idle mode.  |");
  Serial.println("     ----------------------------------------------- ");
}

void loop()
{
  if (Serial.available() > 0)
  {
    int angle = Serial.parseInt();
    Serial.read();
    Serial.println(angle);
    if (angle == 2000 || angle == 2001)
    {
      bool idleOn = (angle == 2000);
      Serial.println(idleOn ? "Setting servos to Idle" : "Activating servos");
      towerProSg90.setIdle(idleOn);
      towerProMg995.setIdle(idleOn);
    }
    else if (angle == 1000)
    {
      towerProSg90.serialPrintInfo();
      towerProMg995.serialPrintInfo();
    }
    else
    {
      towerProSg90.setAngle(angle);
      towerProMg995.setAngle(angle);
    }
  }
}
