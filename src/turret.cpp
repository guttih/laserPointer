#include "turret.h"

Turret::Turret(Servo *servoForTilt, Servo *servoForPan, uint16_t laserPin)
{
    pTilt = servoForTilt;
    pPan = servoForPan;
    _laserPin = laserPin;
    pinMode(_laserPin, OUTPUT);
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
void Turret::tiltPowerOn(bool powerOn)
{
    pTilt->setIdle(!powerOn);
}
void Turret::panPowerOn(bool powerOn)
{
    pPan->setIdle(!powerOn);
}

void Turret::powerLaser(bool powerOn)
{
    
    Serial.print("Setting laser on pin ");Serial.print(_laserPin); Serial.println(powerOn? " ON" : " OFF");
    digitalWrite(_laserPin, powerOn);
}

//  returns:
//    success:
//        A string containing the value of the given parameterName.
//    fail:
//        Empty string if
//         - if url did not include the '?'
//         - parameter name was not found after the '?'
//         - character or had no value
String Turret::getQueryParameterValue(String url, String parameterName)
{
    int start = url.lastIndexOf('?');
    //if there is no ? in the url, there are not parameters
    if (start < 0)
        return "";

    //check if parameter name exits
    start = url.indexOf(parameterName + '=', start + 1);
    if (start < 0)
        return "";
    start += parameterName.length() + 1; //let start point to what comes after =
    int end = url.indexOf('&', start + 1);
    if (end < 0)
    {
        //this parameter is the last one in the url
        return url.substring(start);
    }
    //This parameter is not the last one in the url
    return url.substring(start, end);
}

bool Turret::isValidNumber(String str)
{
    int len = str.length();
    if (len < 1)
        return false;

    for (byte i = 0; i < str.length(); i++)
    {
        if (!isDigit(str.charAt(i)))
            return false;
    }
    return true;
}

bool Turret::parseUrlAndExecute(const char *url, bool removeTrailingHTTP)
{
    String parseUrl = url;
    if (removeTrailingHTTP)
    {
        int i = parseUrl.indexOf(" HTTP");
        if (i > 0)
        {
            parseUrl = parseUrl.substring(0, i);
        }
    }

    String tiltString = getQueryParameterValue(parseUrl, "tilt");
    String panString = getQueryParameterValue(parseUrl, "pan");
    String laserString = getQueryParameterValue(parseUrl, "laser");

    Serial.print("\" tilt:\"");
    Serial.print(tiltString);
    Serial.print("\" pan:\"");
    Serial.print(panString);
    Serial.print("\" laser:\"");
    Serial.print(laserString);
    Serial.println("\".");
    long tilt = isValidNumber(tiltString) ? atol(tiltString.c_str()) : -1;
    long pan = isValidNumber(panString) ? atol(panString.c_str()) : -1;
    long laser = isValidNumber(laserString) ? atol(laserString.c_str()) : -1;
    Serial.print("\" xtilt:\"");
    Serial.print(tilt);
    Serial.print("\" xpan:\"");
    Serial.print(pan);
    Serial.print("\" xlaser:\"");
    Serial.print(laser);
    Serial.println("\".");
    bool bRet = false;
    if (tilt < 0 && pan < 0 && laser < 0 ) {
        return false;
    }
    if (tilt > -1) {
        this->tilt(tilt);
        bRet = true;
    }
    if (pan > -1) {
        this->pan(pan);
        bRet = true;
    }

    if (laser == 0 || laser == 1) {
        powerLaser(laser);
        bRet = true;
    }
    return bRet;
}