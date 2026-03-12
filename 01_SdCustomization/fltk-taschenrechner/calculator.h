#pragma once
#include <string>

class Calculator
{
public:
	// Attributes
	double Result;
	// Setter
	void setNumber1(double value);
	void setNumber1(std::string value);
	void setNumber2(double value);
	void setNumber2(std::string value);
	void setResult(double value);
	void setOperator(char op);
	// Getter
	double getNumber1() const;
	double getNumber2() const;
	char getOperator() const;
	
	//Inputchecks
	bool checkForInvalidInput(std::string inputString);
	int checkForMultipleOperators(std::string inputString);

	// title is self-explanatory
	void useResultForNextOperation(std::string inputString);

	// Calculator-Methods
	void Add();
	void Subtract();
	void Multiply();
	void Divide();
	void chooseOperration();
	
	// Calculate Higher Precedence Operations
	std::string calculateHigherPrecedence(std::string inputString);
	// Calculate Lower Precedence Operations
	std::string calculateLowerPrecedence(std::string inputString);
	// calculte Bracketed Expressions
	std::string calculateBracket(std::string inputString);
	// calculate Exponentiation
	std::string calculateExponentiation(std::string inputString);
	
	//Term calculation
	void calculateTerm(std::string inputString);
	void calculateSimpleTerm(std::string inputString);
	
	

	
	// Split input string
	void splitInput(std::string inputString);

private:
	
	// Attributes
	double Number1;
	double Number2;
	char Operator;
};
