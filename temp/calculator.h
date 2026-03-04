#pragma once

class Calculator
{
public:
   // Setter
   void setNumber1(double value);
   void setNumber2(double value);
   void setOperator(char op);
   // Getter
   double getNumber1() const;
   double getNumber2() const;
   char getOperator() const;

   //Calculator-Methods
   double Add() const;
   double Subtract() const;
   double Multiply() const;
   double Divide() const;
   double chooseOperator() const;

//Attributes
private:
   double Number1;
   double Number2;
   char Operator;
};
