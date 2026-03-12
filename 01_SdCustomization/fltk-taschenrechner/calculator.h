#pragma once

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
	
	//Term calculation
	void calculateTerm(std::string inputString);
	//Precedence checks
	bool HigherPrecedence(std::string inputString);
	bool LowerPrecedence(std::string inputString);

	// Split input string
	void splitInput(std::string inputString);

private:

	// Attributes
	double Number1;
	double Number2;
	char Operator;
};
