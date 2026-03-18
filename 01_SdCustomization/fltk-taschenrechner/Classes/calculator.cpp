#include <sstream>
#include <cmath>
#include <string.h>
#include "calculator.h"
#include <stdexcept>
using namespace std;


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
bool Calculator::checkForInvalidInput(const std::string s)
{
	if (s.empty())
		return false;

	auto isOp = [](char c)
	{
		return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
	};

	int bracketDepth = 0;
	bool lastWasOperator = false;
	bool lastWasDecimal = false;

	for (size_t i = 0; i < s.size(); ++i)
	{
		char c = s[i];

		// --- Gültige Zeichen ---
		if (!isdigit(c) && !isOp(c) && c != '(' && c != ')' && c != '.')
			return false;

		// --- Klammern prüfen ---
		if (c == '(')
			bracketDepth++;
		if (c == ')')
		{
			bracketDepth--;
			if (bracketDepth < 0)
				return false;
		}

		// --- Zwei Operatoren hintereinander ---
		if (isOp(c))
		{
			if (lastWasOperator && !(c == '-' && i == 0)) // einzelnes Minus am Anfang ok
				return false;
			lastWasOperator = true;
			lastWasDecimal = false;
			continue;
		}

		// --- Dezimalpunkt prüfen ---
		if (c == '.')
		{
			if (lastWasDecimal)
				return false;
			lastWasDecimal = true;
			lastWasOperator = false;
			continue;
		}

		// --- Ziffer ---
		if (isdigit(c))
		{
			lastWasOperator = false;
			lastWasDecimal = false;
		}
	}

	// --- Letztes Zeichen darf kein Operator sein ---
	if (isOp(s.back()))
		return false;

	// --- Klammern müssen ausgeglichen sein ---
	if (bracketDepth != 0)
		return false;

	// --- Division durch 0 prüfen ---
	size_t divPos = s.find('/');
	while (divPos != std::string::npos)
	{
		// finde Zahl rechts vom '/'
		size_t i = divPos + 1;

		// optionales Minus
		if (i < s.size() && s[i] == '-')
			i++;

		std::string number;
		while (i < s.size() && (isdigit(s[i]) || s[i] == '.'))
		{
			number += s[i];
			i++;
		}

		if (!number.empty() && stod(number) == 0.0)
			return false;

		divPos = s.find('/', divPos + 1);
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
std::string Calculator::calculateHigherPrecedence(std::string inputString)
{
	while (true)
	{
		int divpos = inputString.find('/');
		int mulpos = inputString.find('*');
		

		if (mulpos == string::npos && divpos == string::npos)
		{
			break;
		}

		
		if (divpos != string::npos)
		{
			setOperator(inputString[divpos]);

			ParsedOperation operands = findOperands(inputString, divpos);

			setNumber1(operands.left);
			setNumber2(operands.right);
			chooseOperration();
			inputString.replace(operands.leftIndex, operands.rightIndex - operands.leftIndex, to_string(Result));
		}
		else if (mulpos != string::npos)
		{
			setOperator(inputString[mulpos]);

			ParsedOperation operands = findOperands(inputString, mulpos);

			setNumber1(operands.left);
			setNumber2(operands.right);
			chooseOperration();

			inputString.replace(operands.leftIndex, operands.rightIndex - operands.leftIndex, to_string(Result));
		}
	}
	return inputString;
}
std::string Calculator::calculateLowerPrecedence(string inputString)
{
	while (true)
	{
		int pluspos = inputString.find('+');
		int minuspos = inputString.find('-');
		if (pluspos == string::npos && minuspos == string::npos)
		{
			break;
		}
		if (pluspos != string::npos)
		{
			setOperator(inputString[pluspos]);

			ParsedOperation operands = findOperands(inputString, pluspos);

			setNumber1(operands.left);
			setNumber2(operands.right);
			chooseOperration();
			inputString.replace(operands.leftIndex, operands.rightIndex - operands.leftIndex, to_string(Result));
		}
		else if (minuspos != string::npos)
		{
			setOperator(inputString[minuspos]);

			ParsedOperation operands = findOperands(inputString, minuspos);

			setNumber1(operands.left);
			setNumber2(operands.right);
			chooseOperration();
			inputString.replace(operands.leftIndex, operands.rightIndex - operands.leftIndex, to_string(Result));
		}
	}
	return inputString;
}
std::string Calculator::calculateExponentiation(string inputString)
{
	while (true)
	{
		// findExponentiation char
		int atIndex = inputString.find('^');
		if (atIndex == string::npos)
		{
			break;
		}

		ParsedOperation operands = findOperands(inputString, atIndex);

		string sBaseNumber = inputString.substr(operands.leftIndex, atIndex - operands.leftIndex);
		double baseNumber = stod(sBaseNumber);
		string sExponent = inputString.substr(atIndex + 1, operands.rightIndex - (atIndex + 1));

		if (!isdigit(inputString[atIndex - 1]))
		{
			// only return the exponentiation part of the string, the rest will be handled in calculateTerm
			return sExponent;
		}
		double exponent = stod(sExponent);

		// exponentiation of the baseNumber
		double result = std::pow(baseNumber, exponent);

		inputString.replace(operands.leftIndex, operands.rightIndex - operands.leftIndex, to_string(result));
	}

	// returns the whole string with the exponentiation calculated
	return inputString;
}
ParsedOperation Calculator::findOperands(std::string inputString, int operatorIndex)
{
	int leftNum = operatorIndex - 1;
	while (leftNum >= 0 && (isdigit(inputString[leftNum])) || inputString[leftNum] == '.')
	{
		leftNum--;
	}
	leftNum++;
	int rightNum = operatorIndex + 1;
	while (rightNum < inputString.size() && (isdigit(inputString[rightNum])) || inputString[rightNum] == '.')
	{
		rightNum++;
	}
	ParsedOperation op;
	op.left = stod(inputString.substr(leftNum, operatorIndex - leftNum));
	op.right = stod(inputString.substr(operatorIndex + 1, rightNum - (operatorIndex + 1)));
	op.leftIndex = leftNum;
	op.rightIndex = rightNum;
	return op;
}
std::string Calculator::calculateBracket(string inputString)
{
	while (true)
	{
		int openBracketPos = inputString.find_last_of('(');
		int closeBracketPos = inputString.find_first_of(')', openBracketPos);
		if (openBracketPos == string::npos || closeBracketPos == string::npos)
		{
			break;
		}
		string subString = inputString.substr(openBracketPos + 1, closeBracketPos - (openBracketPos + 1));
		calculateTerm(subString);
		inputString.replace(openBracketPos, closeBracketPos - openBracketPos + 1, to_string(Result));
	}
	return inputString;
}

// --- calculateTerm ---
void Calculator::calculateTerm(string inputString)
{
	string bracketCalculated = calculateBracket(inputString);
	string expCalculated = calculateExponentiation(bracketCalculated);
	string higherCalculated = calculateHigherPrecedence(expCalculated);
	Result = stod(calculateLowerPrecedence(higherCalculated));
}
void Calculator::calculateSimpleTerm(string inputString)
{
	string expCalculated = calculateExponentiation(inputString);
	string higherCalculated = calculateHigherPrecedence(expCalculated);
	Result = stod(calculateLowerPrecedence(higherCalculated));
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