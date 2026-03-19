#include <iostream>
#include <sstream>
#include <string>

using namespace std;
class Calculator
{
public:
    int Number1;
    int Number2;
    double Resolution;
    char Operator;

    void calculateOperation()
    {
        switch (Operator)
        {
        case '+':
            Resolution = Number1 + Number2;
            break;
        case '-':
            Resolution = Number1 - Number2;
            break;
        case '*':
            Resolution = Number1 * Number2;
            break;
        case '/': 
            Resolution = Number1 / Number2;
            break;
        }
    }

};
string GetInput()
{
    string input;
    cout << "Input: " << endl;
    cin >> input;
    return input;
}
bool IsNumber(string input)
{
    stringstream ss(input);
    int i;
    ss >> i;

    if (ss.fail() || !(ss >> std::ws).eof())
    {
        return false;
    }
    else
    {
        return true;
    };
}
bool IsOperator(string op)
{
    string trueOperators[] = {"+", "-", "*", "/"};
    string foundOperator;
    for (int i = 0; i < 4; i++)
    {
        if (trueOperators[i] == op)
        {
            foundOperator = trueOperators[i];
            return true;
        }
    }
    if (foundOperator.empty())
    {
        return false;
    }
}

int main()
{
    Calculator calculator;
    cout << "Number 1 " <<endl;
    string input = GetInput();
    if (IsNumber(input) == true){
        calculator.Number1 = stoi(input);
    } 
    cout << "Choose Operator (+, -, *, /)" << endl;
    input = GetInput();
    if (IsOperator(input) == true){
        calculator.Operator = input[0];
    }
    cout << "Number 2 "<< endl;
    input = GetInput();
    if(IsNumber(input) == true){
        calculator.Number2 = stoi(input);
    }
    calculator.calculateOperation();
    cout << "Ergebnis: "<< calculator.Resolution << endl;


    return 0;
}