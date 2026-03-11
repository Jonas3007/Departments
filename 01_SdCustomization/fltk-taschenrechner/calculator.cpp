#include <sstream>
#include <cmath>
#include "calculator.h"
#include <stdexcept>
using namespace std;

// --- Getter/Setter ---
void Calculator::setNumber1(double value) { this->Number1 = value; }
void Calculator::setNumber2(double value) { this->Number2 = value; }

void Calculator::setOperator(char op)
{
	if (op != '+' && op != '-' && op != '*' && op != '/')
		throw std::invalid_argument("Invalid Operator!Permitted Operators: +, -, *, /.");
	Operator = op;
}

double Calculator::getNumber1() const { return Number1; }
double Calculator::getNumber2() const { return Number2; }
char Calculator::getOperator() const { return Operator; }

void Calculator::useResultForNextOperation(std::string inputString)
{

	setNumber1(Result);
	setOperator(inputString[0]);
	string subStringNum2 = inputString.substr(1, inputString.size());
	setNumber2(stod(subStringNum2));
	chooseOperration();
}

// --- Rechenmethoden ---
void Calculator::Add()
{
	Result = Number1 + Number2;
}

void Calculator::Subtract()
{
	Result = Number1 - Number2;
}

void Calculator::Multiply()
{
	Result = Number1 * Number2;
}

void Calculator::Divide()
{
	if (Number2 == 0.0)
		throw std::invalid_argument("Division through 0 zero is not permitted.");
	Result = Number1 / Number2;
}

// --- chooseOperator ---
void Calculator::chooseOperration()
{
	switch (Operator)
	{
	case '+':
		Add();
		break;
	case '-':
		Subtract();
		break;
	case '*':
		Multiply();
		break;
	case '/':
		Divide();
		break;
	default:
		// Diese Stelle sollte dank setOperator-Validierung kaum erreicht werden.
		throw std::logic_error("Internal Error: invalid Operator.");
	}
}

// --- splitInput ---
void Calculator::splitInput(std::string inputString)
{
	int operatorIndex= 0;
	int stringSize = inputString.size();
	for (int i = 0; i <= stringSize; i++)
	{
		if (inputString[i] == '+' || inputString[i] == '-' || inputString[i] == '*' || inputString[i] == '/')
		{
			operatorIndex = i;
		}
	}
	string subStringNum1 = inputString.substr(0, operatorIndex);
	string subStringNum2 = inputString.substr(operatorIndex + 1, stringSize);
	setNumber1(stod(subStringNum1));
	setNumber2(stod(subStringNum2));
	setOperator(inputString[operatorIndex]);
}
