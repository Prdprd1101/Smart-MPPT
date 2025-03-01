#include <Arduino.h>
//สร้างคลาส
class Cubic{
  private :
    int X;
    int Y;
    int Z;

  public :
    Cubic(int x,int y,int z){
      X = x;
      Y = y;
      Z = z;
    }

    void print(){
      Serial.println(X);
      Serial.println(Y);
      Serial.println(Z);
    }
      
};

  Cubic cb(8,9,5);
void setup() {
  Serial.begin(9600);
 
}

void loop() {
    cb.print();
    delay(2000);
} 


