#include <sstream>
#include <cmath>
#include <string.h>
#include "calculator.h"
#include <stdexcept>
using namespace std;

// Structs

struct OperatorCount
{
	int count;
	int index[20];
};

// --- Getter/Setter ---
void Calculator::setNumber1(double value) { this->Number1 = value; }
void Calculator::setNumber1(string value) { this->Number1 = stod(value); }
void Calculator::setNumber2(double value) { this->Number2 = value; }
void Calculator::setNumber2(string value) { this->Number2 = stod(value); }

void Calculator::setOperator(char op)
{
	if (op != '+' && op != '-' && op != '*' && op != '/')
		throw std::invalid_argument("Invalid Operator!Permitted Operators: +, -, *, /.");
	Operator = op;
}

double Calculator::getNumber1() const { return Number1; }
double Calculator::getNumber2() const { return Number2; }
char Calculator::getOperator() const { return Operator; }

// check functions
// checks for invalid inputs
bool Calculator::checkForInvalidInput(std::string inputString)
{
	
	if (inputString.size() < 2)
	{
		return false;
	}
	// checks for division through zero
	char div = '/';
	int divIndex = inputString.find(div);
	double num2 = stod(inputString.substr(divIndex + 1, inputString.size()));
	if (num2 == 0)
	{
		return false;
	}
	//Check for double operators
	for(int i = 0; i < inputString.size(); i++)
	{
		if(inputString[i] != '+' && inputString[i] != '-' && inputString[i] != '*' && inputString[i] != '/')
		{
			if(inputString[i-1] == '+' || inputString[i-1] == '-' || inputString[i-1] == '*' || inputString[i-1] == '/')
			{
				return false;
			}
			else if(inputString[i+1] == '+' || inputString[i+1] == '-' || inputString[i+1] == '*' || inputString[i+1] == '/')
			{
				return false;
			}
		}
	}
	if (inputString.empty())
	{
		return false;
	}
	return true;
}

int Calculator::checkForMultipleOperators(std::string inputString)
{
	int operatorCount = 0;
	for (char c : inputString)
	{
		if (c == '+' || c == '-' || c == '*' || c == '/')
		{
			operatorCount++;
		}
	}
	return operatorCount;
}

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

bool Calculator::HigherPrecedence(std::string inputString)
{
	for(int i = 0; i < inputString.size(); i++)
	{
		if(inputString[i] == '*' || inputString[i] == '/')
		{
			return true;
		}	
	}
}
bool Calculator::LowerPrecedence(std::string inputString)
{
	for(int i = 0; i < inputString.size(); i++)
	{
		if(inputString[i] == '+' || inputString[i] == '-')
		{
			return true;
		}	
	}
}	
// --- calculateTerm ---
void Calculator::calculateTerm(string inputString)
{

	while (true)
	{
		int mulpos = inputString.find('*');
		int divpos = inputString.find('/');
		
		if (mulpos == string::npos && divpos == string::npos )
		{
			break;
		}
		
		if (mulpos != string::npos )
		{
			setOperator(inputString[mulpos]);
			int leftNum = mulpos - 1;
			while (leftNum >= 0 && isdigit(inputString[leftNum]) || inputString[leftNum] == '.')
			{
				leftNum--;
			}
			leftNum++;
			int rightNum = mulpos + 1;
			while (rightNum < inputString.size() && isdigit(inputString[rightNum]) || inputString[rightNum] == '.')
			{
				rightNum++;
			}
			setNumber1(stod(inputString.substr(leftNum, mulpos - leftNum)));
			setNumber2(stod(inputString.substr(mulpos + 1, rightNum - (mulpos + 1))));
			chooseOperration();
			inputString.replace(leftNum, rightNum - leftNum, to_string(Result));
		}
		else if (divpos != string::npos )
		{
			setOperator(inputString[divpos]);
			int leftNum = divpos - 1;
			while (leftNum >= 0 && isdigit(inputString[leftNum]) || inputString[leftNum] == '.')
			{
				leftNum--;
			}
			leftNum++;
			int rightNum = divpos + 1;
			while (rightNum < inputString.size() && isdigit(inputString[rightNum]) || inputString[rightNum] == '.')
			{
				rightNum++;
			}
			setNumber1(stod(inputString.substr(leftNum, divpos - leftNum)));
			setNumber2(stod(inputString.substr(divpos + 1, rightNum - (divpos + 1))));
			chooseOperration();
			inputString.replace(leftNum, rightNum - leftNum, to_string(Result));
		}
		
	}
	while (true)
	{
		int pluspos = inputString.find('+');
		int minuspos = inputString.find('-');
		if (pluspos == string::npos && minuspos == string::npos )
		{
			break;
		}
		if (pluspos != string::npos )
		{
			setOperator(inputString[pluspos]);
			int leftNum = pluspos - 1;
			while (leftNum >= 0 && isdigit(inputString[leftNum]) || inputString[leftNum] == '.')
			{
				leftNum--;
			}
			leftNum++;
			int rightNum = pluspos + 1;
			while (rightNum < inputString.size() && isdigit(inputString[rightNum]) || inputString[rightNum] == '.')
			{
				rightNum++;
			}
			setNumber1(stod(inputString.substr(leftNum, pluspos - leftNum)));
			setNumber2(stod(inputString.substr(pluspos + 1, rightNum - (pluspos + 1))));
			chooseOperration();
			inputString.replace(leftNum, rightNum - leftNum, to_string(Result));
		}
		else if (minuspos != string::npos )
		{
			setOperator(inputString[minuspos]);
			int leftNum = minuspos - 1;
			while (leftNum >= 0 && isdigit(inputString[leftNum]) || inputString[leftNum] == '.')
			{
				leftNum--;
			}
			leftNum++;
			int rightNum = minuspos + 1;
			while (rightNum < inputString.size() && isdigit(inputString[rightNum]) || inputString[rightNum] == '.')
			{
				rightNum++;
			}
			setNumber1(stod(inputString.substr(leftNum, minuspos - leftNum)));
			setNumber2(stod(inputString.substr(minuspos + 1, rightNum - (minuspos + 1))));
			chooseOperration();
			inputString.replace(leftNum, rightNum - leftNum, to_string(Result));
		}
		
	}
	if (inputString.find('+') == string::npos && inputString.find('-') == string::npos && inputString.find('*') == string::npos && inputString.find('/') == string::npos)
	{
		Result = stod(inputString);
	}
}

// --- splitInput ---
void Calculator::splitInput(std::string inputString)
{
	int operatorIndex = 0;
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