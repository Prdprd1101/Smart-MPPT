#include "Function.h"
#include <Esp.h>
// calculating function
    int Voltage(float Current, float Resistance){
        return (Current*Resistance) ;
    }

    int Power(float Current, float Resistance){
        return Current*Current*Resistance ;
    }

// ordering function

    void print_value_readed(int a, int b){

        Serial.printf(" Voltage value = %d V \n" ,a );
        Serial.printf(" Power value = %d W \n" ,b );
        Serial.println("All of this printing is working under Function.Lib");
        
    }

// ordering class
    TwoMathMethod::TwoMathMethod(float a, float b) {
        value1 = a;
        value2 = b;
    }

    float TwoMathMethod::sum() {
        return value1 + value2;
    }

    void TwoMathMethod::print_sum() {
        Serial.printf("ค่าผลรวมจากการสั่ง: %.2f\n", value1 + value2);
    }

    float TwoMathMethod::diff() {
        return fabs(value1 - value2);
    }

    void TwoMathMethod::print_diff() {
        Serial.printf("ค่าผลต่างจากการสั่ง: %.2f\n", fabs(value1 - value2));
    }

    float TwoMathMethod::AVG() {
        return (value1 + value2) / 2;
    }

    void TwoMathMethod::print_AVG() {
        Serial.printf("ค่าเฉลี่ยจากการสั่ง: %.2f\n", (value1 + value2) / 2);
    }

    float TwoMathMethod::multiply() {
        return value1 * value2;
    }

    void TwoMathMethod::print_multiply() {
        Serial.printf("ค่าคูณจากการสั่ง: %.2f\n", value1 * value2);
    }