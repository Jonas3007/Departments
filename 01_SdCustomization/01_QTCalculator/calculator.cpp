#include "calculator.h" 
class Calculator{
    public:
    int Number1;
    int Number2;
    char Operator;

    double Add(int number1, int number2){
        return number1 + number2;
    }
    double Subtract(int number1, int number2){
        return number1 - number2;
    }
    double Multiply(int number1, int number2){
        return number1 * number2;
    }
    double Divide(int number1, int number2){
        return number1 / number2;
    }
    
};