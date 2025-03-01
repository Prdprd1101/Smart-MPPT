// value defining

#define Value1 1 
#define Value2 2
#define Value3 3



// defining function
int Voltage(float Current, float Resistance);
int Power(float Current, float Resistance);
void print_value_readed(int a, int b);
class TwoMathMethod{
    private:
    float value1;
    float value2;

public:

    TwoMathMethod(float a, float b);
    
    float sum();
    void print_sum();

    float diff();
    void print_diff();

    float AVG();
    void print_AVG();

    float multiply();
    void print_multiply();
};


