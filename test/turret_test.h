  
#include "arduino.h"
#include "servo.h"
#include "turret.h"
#include <unity.h>

void test_TurretConstructor(void)
{
    Servo    servoTilt(12, 270, 2, 500, 2500, "tilt-RDS3225");
    Servo    servoPan(13, 270, 3, 500, 2500, "pan-RDS3225");
    Turret turret(&servoTilt, &servoPan, 4, 4);
    turret.serialPrintInfo();
}

void test_TurretLaserMaxOnTime(void)
{
    Servo    servoTilt(50, 200, 2, 500, 2500, "tilt-servo");
    Servo    servoPan(60, 190, 3, 500, 2500, "pan-servo");
    Turret turret(&servoTilt, &servoPan, 4, 4);
    turret.updateTimers();
    turret.setLaserMaximumOnTime(500);
    turret.updateTimers();
    TEST_ASSERT_EQUAL(false, turret.isLaserOn());

    // powering on laser
    turret.powerLaser(true);
    turret.setBlink(200);
    
    TEST_ASSERT_EQUAL_MESSAGE(true, turret.isLaserOn(), "Laser should be ON");
    TEST_ASSERT_EQUAL_MESSAGE(255, turret.getLaserIntensity(), "Laser should be intensity 255");
    
    delay(100);

    // 100 ms passed 
    turret.updateTimers();
    TEST_ASSERT_EQUAL_MESSAGE(true, turret.isLaserOn(), "Laser should be ON");
    TEST_ASSERT_EQUAL_MESSAGE(255, turret.getLaserIntensity(), "Laser should be intensity 255");

    delay(101);
    //201 ms passed 
    turret.updateTimers();
    TEST_ASSERT_EQUAL_MESSAGE(true, turret.isLaserOn(), "Laser should be ON");
    TEST_ASSERT_EQUAL_MESSAGE(0, turret.getLaserIntensity(), "Laser should be intensity 0 because of blinking");

    delay(202);
    turret.updateTimers();
    //403 ms passed
    TEST_ASSERT_EQUAL_MESSAGE(true, turret.isLaserOn(), "Laser should be ON");
    TEST_ASSERT_EQUAL_MESSAGE(255, turret.getLaserIntensity(), "Laser should be intensity 255 again because of blinking");

    delay(50);
    // 453 ms passed
    turret.updateTimers();
    TEST_ASSERT_EQUAL_MESSAGE(true, turret.isLaserOn(), "Laser should be ON");
    TEST_ASSERT_EQUAL_MESSAGE(255, turret.getLaserIntensity(), "Laser should be intensity 255");
    
    delay(50);
    //503 ms passed
    turret.updateTimers();
    TEST_ASSERT_EQUAL_MESSAGE(false, turret.isLaserOn(), "after 503 millis passed, should laser intensity should be 0 but isLaserOn should return true, because max laser time on has not bee reached.");
    TEST_ASSERT_EQUAL_MESSAGE(0, turret.getLaserIntensity(), "Laser should be intensity 0 again because of blinking");

    // turn it on again
    turret.powerLaser(true);
    TEST_ASSERT_EQUAL_MESSAGE(true, turret.isLaserOn(), "Laser should be ON");
    TEST_ASSERT_EQUAL_MESSAGE(255, turret.getLaserIntensity(), "Laser should be intensity 255");
    turret.updateTimers();
    TEST_ASSERT_EQUAL_MESSAGE(true, turret.isLaserOn(), "Laser should be ON");
    TEST_ASSERT_EQUAL_MESSAGE(255, turret.getLaserIntensity(), "Laser should be intensity 255");

    delay(201);
    //201 ms passed 
    turret.updateTimers();
    TEST_ASSERT_EQUAL_MESSAGE(true, turret.isLaserOn(), "Laser should be ON");
    TEST_ASSERT_EQUAL_MESSAGE(0, turret.getLaserIntensity(), "Laser should be intensity 0 because of blinking");

    delay(300);
    //501 ms passed 
    turret.updateTimers();
    TEST_ASSERT_EQUAL_MESSAGE(false, turret.isLaserOn(true), "Laser should be OFF");
    TEST_ASSERT_EQUAL_MESSAGE(0, turret.getLaserIntensity(), "Laser should be intensity 0 because of blinking");

    delay(300);
    turret.updateTimers();
}

void test_TurretLaserMaxOnTimeSecondTest(void)
{
    Servo    servoTilt(50, 200, 2, 500, 2500, "tilt-servo");
    Servo    servoPan(60, 190, 3, 500, 2500, "pan-servo");
    Turret turret(&servoTilt, &servoPan, 4, 4);
    turret.setLaserMaximumOnTime(500);
    // Serial.println(String("Millis()")+String(millis()));
    // Serial.println(String("1 getLaserTunOffTime()")+String(turret.getLaserTunOffTime()));
    turret.powerLaser(true);
    // Serial.println(String("Millis()")+String(millis()));
    // Serial.println(String("2 getLaserTunOffTime()")+String(turret.getLaserTunOffTime()));
    delay(100);
    turret.updateTimers();
    // Serial.println(String("Millis()")+String(millis()));
    // Serial.println(String("3 getLaserTunOffTime()")+String(turret.getLaserTunOffTime()));
    TEST_ASSERT_EQUAL_MESSAGE(true, turret.isLaserOn(), "Laser should be ON");
    TEST_ASSERT_EQUAL_MESSAGE(255, turret.getLaserIntensity(), "Laser should be intensity 255");
    
    delay(600);
    turret.updateTimers();
    Serial.println(String("Millis()")+String(millis()));
    Serial.println(String("4 getLaserTunOffTime()")+String(turret.getLaserTunOffTime()));
    TEST_ASSERT_EQUAL_MESSAGE(false, turret.isLaserOn(true), "Laser should be OFF");
    TEST_ASSERT_EQUAL_MESSAGE(0, turret.getLaserIntensity(), "Laser should be intensity 0");
}
