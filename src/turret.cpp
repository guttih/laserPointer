#include "turret.h"



Turret::Turret(Servo *servoForPan, Servo *servoForTilt) {
    pPan = servoForPan;
    pTilt = servoForTilt;
};

void Turret::serialPrintInfo() {
    pPan->serialPrintInfo();
    pTilt->serialPrintInfo();
};