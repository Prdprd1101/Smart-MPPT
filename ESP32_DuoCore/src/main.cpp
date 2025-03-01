#include <Arduino.h>

int count1 = 0 ;
int count2 = 0 ;

TaskHandle_t task1_handle = NULL;

void task1(void * parameters){
  for(;;){
    Serial.print("Task 1 counter :");
    Serial.println( count1++ );
    vTaskDelay(700/portTICK_PERIOD_MS);

    //if(count1 > 2){vTaskSuspend(NULL);}
  }
}

void task2(void * parameters){
  for(;;){
    Serial.print("Task 2 counter :");
    Serial.println( count2++ );
    vTaskDelay(700/portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(9600);
    xTaskCreate(
      task1,
      "Task 1",
      1000,
      NULL,
      1,
      &task1_handle
    );

    xTaskCreate(
      task2,    // ฟังก์ชัน Task
      "Task 2", // ชื่อ Task
      1000,     // ขนาดไบต์ ที่เก็บฟังก์ชันไว้บนแรม
      NULL,     // พารามาเตอร์ที่ส่ง ให้Task
      1,        // ลำดับความสำคัญ 1 น้อยสุด
      NULL      // ไม่ต้องใช้ TaskHandle
    );
}
void loop() {
  if(count1>2){
    vTaskSuspend(task1_handle);
  }

  if(count2>10){
    vTaskResume(task1_handle);
  }

}
