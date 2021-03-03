#include <Arduino.h>


#include "servo.h"

  Servo towerProSg90(12,  180, 0, 500, 2400, "sg90");
  Servo towerProMg995(13, 120, 1, "mg995");

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
  Serial.println("starting");
}


void loop() 
{
  if (Serial.available()>0)
  {      
    int angle=Serial.parseInt();
    Serial.read();
    Serial.println(angle);
    towerProSg90.setAngle(angle);
    towerProMg995.setAngle(angle);
  }
  
}
