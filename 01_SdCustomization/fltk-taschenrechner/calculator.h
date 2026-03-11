#pragma once

class Calculator
{
public:
	// Attributes
	double Result;
	// Setter
	void setNumber1(double value);
	void setNumber2(double value);
	void setResult(double value);
	void setOperator(char op);
	// Getter
	double getNumber1() const;
	double getNumber2() const;
	char getOperator() const;
	
	void useResultForNextOperation(std::string inputString);

	//Calculator-Methods
	void Add();
	void Subtract();
	void Multiply();
	void Divide();
	void chooseOperration();
	
	//Split input string 
	void splitInput(std::string inputString);

//Attributes
private:
	double Number1;
	double Number2;
	char Operator;
};
