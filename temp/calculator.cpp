
#include "calculator.h"
#include <stdexcept>

// --- Getter/Setter ---
void Calculator::setNumber1(double value) { Number1 = value; }
void Calculator::setNumber2(double value) { Number2 = value; }

void Calculator::setOperator(char op) {
    if (op != '+' && op != '-' && op != '*' && op != '/')
        throw std::invalid_argument("Invalid Operator!Permitted Operators: +, -, *, /.");
    Operator = op;
}

double Calculator::getNumber1() const { return Number1; }
double Calculator::getNumber2() const { return Number2; }
char   Calculator::getOperator() const { return Operator; }

// --- Rechenmethoden ---
double Calculator::Add() const {
    return Number1 + Number2;
}

double Calculator::Subtract() const {
    return Number1 - Number2;
}

double Calculator::Multiply() const {
    return Number1 * Number2;
}

double Calculator::Divide() const {
    if (Number2 == 0.0)
        throw std::invalid_argument("Division through 0 zero is not permitted.");
    return Number1 / Number2;
}

// --- chooseOperator ---
double Calculator::chooseOperator() const {
    switch (Operator) {
        case '+': return Add();
        case '-': return Subtract();
        case '*': return Multiply();
        case '/': return Divide();
        default:
            // Diese Stelle sollte dank setOperator-Validierung kaum erreicht werden.
            throw std::logic_error("Internal Error: invalid Operator.");
    }
}