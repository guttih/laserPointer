#include "turret.h"

Turret::Turret(Servo *servoForTilt, Servo *servoForPan, uint16_t laserPin, uint16_t laserChannel)
{
    pTilt = servoForTilt;
    pPan = servoForPan;
    tiltMaxAngle = pTilt->getMaxAngle();
    panMaxAngle = pPan->getMaxAngle();
    _laserPin = laserPin;
    _laserPinValue = 0;
    _laserChannel = laserChannel;
    ledcSetup(_laserChannel, TURRET_LEDC_BASE_FREQ, TURRET_LEDC_TIMER_13_BIT);
    ledcAttachPin(_laserPin, _laserChannel); 
};

void Turret::serialPrintInfo()
{
    Serial.println("---------------------");
    Serial.println(String(" laserChannel  : ") + _laserChannel);
    Serial.println(String(" laserPin      : ") + _laserPin);
    Serial.println(String(" laserPinValue : ") + _laserPinValue);
    Serial.println("---------------------");
    pTilt->serialPrintInfo();
    pPan->serialPrintInfo();
};

void Turret::tilt(uint16_t angle)
{
    if (angle < tiltMinAngle) {
        angle = tiltMinAngle;
    } else if (angle > tiltMaxAngle) {
        angle = tiltMaxAngle;
    }
    pTilt->setAngle(angle);
}
void Turret::pan(uint16_t angle)
{
    if (angle < panMinAngle) {
        angle = panMinAngle;
    } else if (angle > panMaxAngle) {
        angle = panMaxAngle;
    }
    pPan->setAngle(angle);
}


bool Turret::isLaserOn(bool debugPrint)
{
    bool ret = getLaserIntensity() > 0 || (_blinkTimerTempValue > 0 && _laserTurnOffTime > 0);

    if (debugPrint){
         unsigned long blinkTimerTempValue =  _blinkTimerTempValue;
         unsigned long laserTurnOffTime = _laserTurnOffTime;
         uint16_t laserIntensity = getLaserIntensity();
        Serial.print(String("getLaserIntensity:")+String(laserIntensity));
        Serial.print(String(" _blinkTimerTempValue:")+String(blinkTimerTempValue));
        Serial.print(String(" _laserTurnOffTime:")+String(laserTurnOffTime));
        Serial.println(String(" ret:")+String(ret));
    }
    return ret;
}

void Turret::ledcAnalogWrite(uint8_t channel, uint32_t value, uint32_t valueMax) {
    // calculate duty
 
    uint32_t duty = (TURRET_LEDC_BASE_FREQ / valueMax) * ((value) < (valueMax) ? (value) : (valueMax));
    //Serial.println("duty " + String(duty) + " on channel " + String(channel));
    if (duty == 0) {
        //sometimes ledcAnalogWrite duty = 0 will not have any effect pins D0 - D7 seem to be ok, but others will have no effect
        ledcAnalogWrite(channel, 1, valueMax);
    }
    // write duty to LEDC
    ledcWrite(channel, duty);
}

void Turret::setServoConstraint(Servo *pServo, uint16_t minAngle, uint16_t maxAngle) {
    uint16_t max = maxAngle < pServo->getMaxAngle()? maxAngle : pServo->getMaxAngle();
    uint16_t min = minAngle < maxAngle? minAngle : 0;
    if (pServo == pTilt) {
        tiltMinAngle = min;
        tiltMaxAngle = max;
    } else {
        panMinAngle = min;
        panMaxAngle = max;
    }
    if (pServo->getAngle() < min)
        pServo->setAngle(min);
    else if (pServo->getAngle() > max)
        pServo->setAngle(max);

}
void Turret::setTiltConstraint(uint16_t minAngle, uint16_t maxAngle) {
    setServoConstraint(pTilt, minAngle, maxAngle);
}
void Turret::setPanConstraint(uint16_t minAngle, uint16_t maxAngle) {
    setServoConstraint(pPan, minAngle, maxAngle);
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
    //Serial.print("Setting laser on pin ");Serial.print(_laserPin); Serial.println(powerOn? " ON" : " OFF");
    setLaserIntensity(powerOn? 255: 0);
}

/**
 * @brief Sets the maximum time the laser is allowed to be turned on.
 * In other words, when should it be turned off after it was last turned on.
 * 
 * @param _maxPowerOnTimeMs maximum time in milliseconds.
 */
void Turret::setLaserMaximumOnTime(unsigned long maxPowerOnTimeMs){
    _maxPowerOnTime = maxPowerOnTimeMs;
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

bool Turret::parseSetUrlAndExecute(const char *url, bool removeTrailingHTTP)
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

    String laserString = getQueryParameterValue(parseUrl, "laser");
    String blinkString = getQueryParameterValue(parseUrl, "blink");


    long laser = isValidNumber(laserString) ? atol(laserString.c_str()) : -1;
    long blink = isValidNumber(blinkString) ? atol(blinkString.c_str()) : -1;


    Serial.print(" laser:");Serial.print(laser);
    Serial.print(" blink:");Serial.print(blink);
    Serial.println(".");
    bool bRet = false;

    if (laser > -1) {
        //powerLaser(laser);
        setLaserIntensity(laser);
        bRet = true;
    }

    if (blink > -1)
        setBlink(blink); //only changing blinking values if valid values extracted from query string
   
    return bRet;
}
bool Turret::parseGridUrlAndExecute(const char *url, bool removeTrailingHTTP)
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

    long tilt = isValidNumber(tiltString) ? atol(tiltString.c_str()) : -1;
    long pan = isValidNumber(panString) ? atol(panString.c_str()) : -1;

    String str = String(" tilt:") + String(tilt) +
                 String(" pan:") + String(pan);
    Serial.println(str);

    if (tilt < 0 || pan < 0)
    {
        return false;
    }

    tiltPowerOn(true);
    panPowerOn(true);

    setLaserIntensity(100);
    setBlink(0);

    Point center;
    center.x = pan;
    center.y = tilt;
    Point current = getCirclePoint(6, center, 0);
    this->pan(current.x);
    this->tilt(current.y);
    delay(200);

    for (int x = 0; x < 2; x++)
    {
        for (int i = 0; i < 360; i++)
        {
            current = getCirclePoint(6, center, i);
            this->pan(current.x);
            this->tilt(current.y);
            delay(2);
        }
    }

    this->pan(pan);
    this->tilt(tilt);
    delay(2000);

    for (int i = 0; i < 3; i++)
    {
        this->pan(pan - 10);this->tilt(tilt);
        delay(150);
        this->pan(pan + 10);this->tilt(tilt);
        delay(150);
    }

    this->tilt(tilt);
    this->pan(pan);
    delay(1000);

    setLaserIntensity(100);
    setBlink(150);

    return true;
}

bool Turret::parseMoveUrlAndExecute(const char *url, bool removeTrailingHTTP)
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
    String blinkString = getQueryParameterValue(parseUrl, "blink");


    long tilt  = isValidNumber(tiltString) ? atol(tiltString.c_str()) : -1;
    long pan   = isValidNumber(panString) ? atol(panString.c_str()) : -1;
    long laser = isValidNumber(laserString) ? atol(laserString.c_str()) : -1;
    long blink = isValidNumber(blinkString) ? atol(blinkString.c_str()) : -1;


    Serial.print(" tilt:"); Serial.print(tilt);
    Serial.print(" pan:");  Serial.print(pan);
    Serial.print(" laser:");Serial.print(laser);
    Serial.print(" blink:");Serial.print(blink);
    Serial.println(".");
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

    if (laser > -1) {
        setLaserIntensity(laser);
        bRet = true;
    }

    if (blink > -1)
        setBlink(blink); //only changing blinking values if valid values extracted from query string
   
    return bRet;
}

/**
 * @brief Makes the laser blink.
 * 
 * @param intervalInMilliseconds 
 */
void Turret::setBlink(long intervalInMilliseconds) {

    if (intervalInMilliseconds < 1 ) {
        _blinkTimerInterval = 0;
        _blinkTime = 0;
        _blinkTimerTempValue = 0;
        _blinkTimerCounter = 0;
    } else {
        _blinkTimerInterval = intervalInMilliseconds;
        _blinkTime = millis() + _blinkTimerInterval;

        _blinkTimerCounter = 0;
        if (_laserPinValue > 0)
            _blinkTimerTempValue = _laserPinValue;
    } 
}

bool Turret::parseActivateUrlAndExecute(const char *url, bool removeTrailingHTTP)
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

    String active = getQueryParameterValue(parseUrl, "active");
    Serial.print("\" active:\"");
    Serial.print(active);
    Serial.println("\".");
    bool powerOn;
    
    if (active == "true" ||  active == "1") {
        powerOn = true;
    } else if (active == "false" ||  active == "0") {
        powerOn = false;
    } else return false;
    
    tiltPowerOn(powerOn);
    panPowerOn(powerOn);
    powerLaser(powerOn);
    
    return true;
}


void Turret::setLaserIntensity(uint16_t intensity)
{
    _laserPinValue = min(intensity, (uint16_t)255);
    
    if (_laserPinValue > 0) {
        _blinkTimerTempValue = _laserPinValue;
        _laserTurnOffTime = millis() + _maxPowerOnTime;
    }

    ledcAnalogWrite(_laserChannel, _laserPinValue, 255);
}

void Turret::setLaserIntensityBlink(uint16_t intensity)
{
    _laserPinValue = min(intensity, (uint16_t)255);
    ledcAnalogWrite(_laserChannel, _laserPinValue, 255);
}

void Turret::updateTimers()
{

    unsigned long now = millis();
    if (_blinkTime == 0 && _laserTurnOffTime == 0)
        return;

    if (now >= _laserTurnOffTime) {
        _laserTurnOffTime = 0;
        setLaserIntensity(0);
        return;
    }

    if (now >= _blinkTime && _blinkTime > 0) {
        _blinkTimerCounter++;
        runUpdateBlinkTimerFunction();
        _blinkTime = now + _blinkTimerInterval;
    }
}

void Turret::runUpdateBlinkTimerFunction(){
    
    bool isEven = _blinkTimerCounter % 2 == 0;
    setLaserIntensityBlink(isEven * _blinkTimerTempValue);
}

Point Turret::getCirclePoint(int radius, Point center, int angle) {
    Point ret;
    double x = radius * sin(angle * PI/180);
    double y = radius * cos(angle * PI/180);
    ret.x = center.x + round(x);
    ret.y = center.y + round(y);
    return ret;
}