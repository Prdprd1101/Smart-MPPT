#include <Arduino.h>
#include <WiFi.h>

// กำหนดค่าการเชื่อมต่อ WiFi
#define WIFI_NETWORK "ppethh"
#define WIFI_PASSWORD "123456789"
#define WIFI_TIMEOUT_MS 20000  // 20 วินาที
#define WIFI_RECONNECT_DELAY 10000  // 10 วินาที (ถ้าเชื่อมต่อไม่สำเร็จ)

TaskHandle_t wifiTaskHandle = NULL;  // ตัวแปรเก็บ Task Handle

// ฟังก์ชันแปลงค่า WiFi.status() เป็นข้อความ
String translateWiFiStatus(wl_status_t status) {
  switch (status) {
    case WL_IDLE_STATUS:    return "Idle";
    case WL_NO_SSID_AVAIL:  return "No SSID Available";
    case WL_SCAN_COMPLETED: return "Scan Completed";
    case WL_CONNECTED:      return "Connected";
    case WL_CONNECT_FAILED: return "Connect Failed";
    case WL_CONNECTION_LOST:return "Connection Lost";
    case WL_DISCONNECTED:   return "Disconnected";
    default:                return "Unknown";
  }
}

// Task ตรวจสอบและเชื่อมต่อ WiFi
void KeepWifiAlive(void * parameters) {
  for (;;) {
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("[WiFi] Connecting...");
      WiFi.disconnect();  // ตัดการเชื่อมต่อเก่าก่อน
      WiFi.mode(WIFI_STA);
      WiFi.begin(WIFI_NETWORK, WIFI_PASSWORD);

      unsigned long startAttemptTime = millis();
      
      while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < WIFI_TIMEOUT_MS) {
        Serial.print(".");
        vTaskDelay(500 / portTICK_PERIOD_MS);
      }

      if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\n[WiFi] Connected: " + WiFi.localIP().toString());
      } else {
        Serial.println("\n[WiFi] Connection Failed! Retrying in " + String(WIFI_RECONNECT_DELAY / 1000) + " sec...");
        vTaskDelay(WIFI_RECONNECT_DELAY / portTICK_PERIOD_MS);
      }
    } else {
      Serial.println("[WiFi] Still Connected - IP: " + WiFi.localIP().toString());
    }

    Serial.println("[WiFi] Status: " + translateWiFiStatus(WiFi.status()));
    vTaskDelay(5000 / portTICK_PERIOD_MS);  // ตรวจสอบทุก 5 วินาที
  }
}

void setup() {
  Serial.begin(9600);

  // สร้าง Task สำหรับจัดการ WiFi
  xTaskCreatePinnedToCore(
    KeepWifiAlive,       // ฟังก์ชัน Task
    "Keep Wifi Alive",   // ชื่อ Task
    5000,               // ขนาด Stack
    NULL,               // ไม่มีพารามิเตอร์
    1,                  // Priority
    &wifiTaskHandle,    // เก็บ Task Handle
    CONFIG_ARDUINO_RUNNING_CORE  // รันบน Core ปัจจุบัน
  );
}

void loop() {
  Serial.println("Waiting...");
  delay(700);
}
