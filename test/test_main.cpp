  
//#include "arduino.h"
#include "turret_test.h"
#include <unity.h>

String repeat(String s, unsigned int count) {
    String str ="";
    for(unsigned int ui = 0; ui < count; ui++) {
        str.concat(s);
    }
    return str;
}
String concat(String str1, String str2, String str3) {
    String str = str1;
    str.concat(str2);
    str.concat(str3);
    return str;
}
void header(const char *strHeader) {
    String text = String(" - ") + String(strHeader) + String(" - ");
    int textLen = text.length();
    //frame length default is 50
    const int len = textLen > 46? (textLen+4) : 50;
    const int spaces = (len - textLen)-2;

    Serial.println(concat("┌", repeat("─", len-2), "┐"));
    Serial.println(concat("│", repeat(" ", len-2), "│"));
    int spaceLeft = spaces/2;
    int spaceRight = spaces - spaceLeft;    
    String frameLeft = concat("│", repeat(" ", spaceLeft), text);
    Serial.println(concat(frameLeft, repeat(" ", spaceRight), "│"));
    Serial.println(concat("│", repeat(" ", len-2), "│"));
    Serial.println(concat("└", repeat("─", len-2), "┘"));
}

void testTurret() {
    header("Testing Turret");
    test_TurretConstructor();
    test_TurretLaserMaxOnTime();
    test_TurretLaserMaxOnTimeSecondTest();
}
void setup() {
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);
    UNITY_BEGIN();    
        testTurret();
    UNITY_END();
}

void loop() {
}