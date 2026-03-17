// tests/test_calculator.cpp
#include <catch2/catch_test_macros.hpp>
#include "calculator.h"
#include <cmath>
#include <sstream>
#include <string>

TEST_CASE("Addition funktioniert", "[add]") {
	Calculator calc;
	calc.setNumber1(5);
	calc.setNumber2(3);
	calc.setOperator('+');
	calc.chooseOperration();
	REQUIRE(calc.Result == 8);
}

TEST_CASE("Subtraktion funktioniert", "[subtract]") {
	Calculator calc;
	calc.setNumber1(5);
	calc.setNumber2(3);
	calc.setOperator('-');
	calc.chooseOperration();
	REQUIRE(calc.Result == 2);
}

TEST_CASE("Multiplikation funktioniert", "[multiply]") {
	Calculator calc;
	calc.setNumber1(5);
	calc.setNumber2(3);
	calc.setOperator('*');
	calc.chooseOperration();
	REQUIRE(calc.Result == 15);
}

TEST_CASE("Division funktioniert", "[divide]") {
	Calculator calc;
	calc.setNumber1(5);
	calc.setNumber2(2);
	calc.setOperator('/');
	calc.chooseOperration();
	REQUIRE(calc.Result == 2.5);
}

TEST_CASE("Division durch 0 wirft Fehler", "[divide]") {
	Calculator calc;
	calc.setNumber1(5);
	calc.setNumber2(0);
	calc.setOperator('/');
	REQUIRE_THROWS_AS(calc.chooseOperration(), std::invalid_argument);
}

TEST_CASE("Ergebniss wiederverwenden funktioniert", "[useResultForNextOperation]")
{
	Calculator calc;
	calc.Result = 34;
	std::string input = "+6";
	calc.useResultForNextOperation(input);
	REQUIRE(calc.Result == 40);
}
TEST_CASE("splitInput funktioniert", "[splitInput]")
{
	Calculator calc;
	std::string input = "5*7";
	calc.splitInput(input);
	int num1 =calc.getNumber1();
	int num2 = calc.getNumber2();
	int op = calc.getOperator();
	REQUIRE(num1 == 5);
	REQUIRE(num2 == 7);
	REQUIRE(op == '*');
}
TEST_CASE("setOperator invaild argument funktioniert", "[setOperator]")
{
	Calculator calc;
	char invalidOperator = 'c';
	REQUIRE_THROWS_AS(calc.setOperator(invalidOperator), std::invalid_argument);
}
TEST_CASE("checkInput invaild argument funktioniert", "[checkInput]")
{
	Calculator calc;
	std::string invalidInput = "5++7";
	REQUIRE(calc.checkForInvalidInput(invalidInput) == false);
}

TEST_CASE("checkForMultipleOperators funktioniert", "[checkForMultipleOperators]")
{
	Calculator calc;
	std::string input = "5+7*3-2";
	int operatorCount = calc.checkForMultipleOperators(input);
	REQUIRE(operatorCount == 3);
}
TEST_CASE("checkInput find double operators funktioniert", "[checkInput]")
{
	Calculator calc;
	std::string invalidInput = "5++7";
	REQUIRE(calc.checkForInvalidInput(invalidInput) == false);
}
TEST_CASE("calculateTerm funktioniert", "[calculateTerm]")
{
	Calculator calc;
	std::string input = "5+7*3-2";
	calc.calculateTerm(input);
	REQUIRE(calc.Result == 24);
}
TEST_CASE("Only + and - in calculateTerm funktioniert", "[calculateTerm]")
{
	Calculator calc;
	std::string input = "5+7-2";
	calc.calculateTerm(input);
	REQUIRE(calc.Result == 10);
}
TEST_CASE("Only * and / in calculateTerm funktioniert", "[calculateTerm]")
{
	Calculator calc;
	std::string input = "5*7/2";
	calc.calculateTerm(input);
	REQUIRE(calc.Result == 17.5);
}
TEST_CASE("findOperands funktioniert", "[findOperands]")
{
	Calculator calc;
	std::string input = "5+7*3-2";
	int operatorIndex = 3; // Position des '*' Operators
	ParsedOperation op = calc.findOperands(input, operatorIndex);
	REQUIRE(op.left == 7);
	REQUIRE(op.right == 3);
}
TEST_CASE("calculateExponentiation funktioniert", "[calculateExponentiation]")
{
	Calculator calc;
	std::string input = "2^3";
	double num1 = 2;
	double num2 = 3;
	double expectedResult = std::pow(num1, num2);
	std::string resultString = calc.calculateExponentiation(input);
	double result = std::stod(resultString);
	REQUIRE(result == expectedResult);
}
TEST_CASE("calculateExponentiation in calculateTerm funktioniert", "[calculateTerm]")
{
	Calculator calc;
	std::string input = "2^3+4";
	calc.calculateTerm(input);
	double expectedResult = std::pow(2, 3) + 4;
	REQUIRE(calc.Result == expectedResult);
}
TEST_CASE("calculateBracket funktioniert", "[calculateBracket]")
{
	Calculator calc;
	std::string input = "(3+4)";
	double expectedResult =3 + 4 ;
	double result = stod(calc.calculateBracket(input));
	REQUIRE(result == expectedResult);
}
TEST_CASE("calculateBracket with nested brackets funktioniert", "[calculateBracket]")
{
	Calculator calc;
	std::string input = "(3+(4*5))";
	double expectedResult = 3 + (4 * 5);
	double result = stod(calc.calculateBracket(input));
	REQUIRE(result == expectedResult);
}
TEST_CASE("checkForInvalidInput detects invalid characters", "[checkForInvalidInput]")
{
	Calculator calc;
	std::string invalidInput = "5+7a-2";
	REQUIRE(calc.checkForInvalidInput(invalidInput) == false);
}
TEST_CASE("checkForInvalidInput detects unbalanced brackets", "[checkForInvalidInput]")
{
	Calculator calc;
	std::string invalidInput = "5+(7-2";
	REQUIRE(calc.checkForInvalidInput(invalidInput) == false);
}
TEST_CASE("checkForInvalidInput detects consecutive operators", "[checkForInvalidInput]")
{
	Calculator calc; 
	std::string invalidInput = "5**7//2";
	REQUIRE(calc.checkForInvalidInput(invalidInput) == false);
}
TEST_CASE("checkForInvalidInput detects empty string", "[checkForInvalidInput]")
{
	Calculator calc;
	std::string invalidInput = "";
	REQUIRE(calc.checkForInvalidInput(invalidInput) == false);
}
TEST_CASE("checkForInvalidInput detects wrong decimal points", "[checkForInvalidInput]")
{
	Calculator calc;
	std::string invalidInput = "5..7+2";
	REQUIRE(calc.checkForInvalidInput(invalidInput) == false);
}
TEST_CASE("checkForInvalidInput detects last char is operator", "[checkForInvalidInput]")
{
	Calculator calc;
	std::string invalidInput = "5+7-";
	REQUIRE(calc.checkForInvalidInput(invalidInput) == false);
}
TEST_CASE("checkForInvalidInput detects single minus at the beginning", "[checkForInvalidInput]")
{
	Calculator calc;
	std::string validInput = "-5+7";
	REQUIRE(calc.checkForInvalidInput(validInput) == true);
}
TEST_CASE("checkForInvalidInput detects single minus in the middle", "[checkForInvalidInput]")
{
	Calculator calc;
	std::string validInput = "5+-7";
	REQUIRE(calc.checkForInvalidInput(validInput) == false);
}
TEST_CASE("checkForInvalidInput detects valid input", "[checkForInvalidInput]")
{
	Calculator calc;
	std::string validInput = "5+7-2*(3^2)";
	REQUIRE(calc.checkForInvalidInput(validInput) == true);
}