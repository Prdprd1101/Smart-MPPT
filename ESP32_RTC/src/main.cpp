#include <Wire.h>
#include <RTClib.h>
// 32k pin ใช้กับวงจรที่ต้องการสัญญาณนาฬิกาคงที่
// SQW pin ใช้กับ Alarm หรือให้สัญญาณ 1Hz, 4kHz, 8kHz, 32kHz
RTC_DS3231 rtc;

void setup() {
    Serial.begin(9600);
    Wire.begin(); // ใช้ขา GPIO21(SCL) GPIO22(SDA) 
    
    if (!rtc.begin()) {
        Serial.println("Couldn't find RTC");
        while (1);
    }
    
    if (rtc.lostPower()) {
        Serial.println("RTC lost power, setting the time!");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
}

void loop() {
    DateTime now = rtc.now();
    
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    
    delay(1000);
    
}
