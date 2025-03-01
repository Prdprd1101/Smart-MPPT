
/* การสร้าง file .h .cpp 
  Objective 
    1. จัดระเบียบการเรียนใช้ ฟังก์ชัน หรือ class ให้มีระเบียบ
    2. เมื่อสร้าง lib ใช้งานหนึ่งงานสามารถนำไปใช้ต่อในโปรเจคอื่นได้โดยการ include

  Working method
    1. สร้างฟังก์ชันไว้ใน ไฟล์(Fcpp) include ไปที่ ไฟล์(h) เพื่อให้ 2 ไฟล์นี้เชื่อมต่อกัน
    2. เรียกใช้ ฟังก์ชันจากไฟล์ (Fcpp) มาใช้ที่ ไฟล์หลัก(main.cpp)ผ่านการ include

  file component
    Function.cpp (FunctionMethod) (Including)
    Function.h (Function name) (class name) (Defining)
    Main.cpp (including) (Using Function)

*/
// สร้างฟังก์ชัน คำนวน คำสั่ง และ คลาส

#include <Arduino.h>
#include "Function.h"

int power ;
int voltage ; 
TwoMathMethod math(12.5, 8.2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  float Resistance = 160.265;
  float Current = 1.2514;
  power = Power(Current,Resistance);
  voltage = Voltage(Current,Resistance);  
  
  
}

void loop() {
  
  Serial.print(power);
  Serial.print(voltage);
  print_value_readed(voltage, power);
  //เทสคลาส
  Serial.println("=== TwoMathMethod Demo ===");

    // ใช้ฟังก์ชันคำนวณค่าและแสดงผล
    math.print_sum();
    math.print_diff();
    math.print_AVG();
    math.print_multiply();

    Serial.println("=== คำนวณโดยใช้ return value ===");
    Serial.printf("Sum: %.2f\n", math.sum());
    Serial.printf("Diff: %.2f\n", math.diff());
    Serial.printf("Avg: %.2f\n", math.AVG());
    Serial.printf("Multiply: %.2f\n\n", math.multiply());
  delay(1000);
}

