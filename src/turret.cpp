#include "turret.h"

Turret::Turret(Servo *servoForTilt, Servo *servoForPan)
{
    pTilt = servoForTilt;
    pPan = servoForPan;
};

void Turret::serialPrintInfo()
{
    pTilt->serialPrintInfo();
    pPan->serialPrintInfo();
};

void Turret::tilt(uint16_t angle)
{
    pTilt->setAngle(angle);
}
void Turret::pan(uint16_t angle)
{
    pPan->setAngle(angle);
}
void Turret::tiltSetIdle(bool idle)
{
    pTilt->setIdle(idle);
}
void Turret::panSetIdle(bool idle)
{
    pPan->setIdle(idle);
}