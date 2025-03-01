#include "FS.h"
#include "SD.h"
#include "SPI.h"

#define SD_CS 2 // ขา CS ของ SD Card Module
/*
void setup() {
    Serial.begin(9600);
    if (!SD.begin(SD_CS)) {
        Serial.println("Card Mount Failed!");
        return;
    }
    Serial.println("SD Card Initialized.");

    // เขียนข้อมูลลงไฟล์
    File file = SD.open("/test.txt", FILE_WRITE);
    if (file) {
        file.println("Hello from ESP32!");
        file.close();
        Serial.println("File written successfully.");
    } else {
        Serial.println("Failed to open file for writing.");
    }

    // อ่านข้อมูลจากไฟล์
    file = SD.open("/test.txt");
    if (file) {
        Serial.println("Reading file...");
        while (file.available()) {
            Serial.write(file.read());
        }
        file.close();
    } else {
        Serial.println("Failed to open file for reading.");
    }
}

void loop() {
}
*/

#include <ArduinoJson.h>
#include "FS.h"
#include "SD.h"
#include "SPI.h"

#define SD_CS 2  

void setup() {
    Serial.begin(9600);
    if (!SD.begin(SD_CS)) {
        Serial.println("SD Card Mount Failed!");
        return;
    }

    StaticJsonDocument<200> jsonDoc;
    jsonDoc["temperature"] = 25.3;
    jsonDoc["humidity"] = 60;
    
    File file = SD.open("/data.json", FILE_WRITE);
    if (file) {
        serializeJson(jsonDoc, file);
        file.close();
        Serial.println("JSON file written.");
    }
}
/*

บันทึกข้อความง่าย ๆ	TXT
จัดเก็บข้อมูลเชิงตาราง (ใช้ Excel ได้)	CSV
บันทึกเหตุการณ์หรือ Debugging	LOG
จัดเก็บข้อมูลแบบโครงสร้าง ใช้ใน IoT	JSON

*/
void loop() {}
