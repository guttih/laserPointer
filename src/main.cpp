#include <Arduino.h>

const int ledPin = 2;

#include "servo.h"
/*
  test servo
 */
 
//Servo *towerPro = new Servo(13,90, 1);

Servo towerPro(13, 90, 1);

void setup() 
{            
  pinMode(ledPin, OUTPUT);
   digitalWrite(ledPin, HIGH);
  Serial.begin(115200);
  delay(1000); 
  digitalWrite(ledPin, LOW);
  Serial.print("Type in a value from 0 to ");Serial.println(towerPro.getMaxAngle());
}


void loop() 
{
  if (Serial.available()>0)
  {      
    int angle=Serial.parseInt();
    Serial.read();
    Serial.print("got ");Serial.println(angle);
    towerPro.setAngle(angle);
  }
  
}
