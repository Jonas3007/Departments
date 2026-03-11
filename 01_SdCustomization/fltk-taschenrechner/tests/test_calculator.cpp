// tests/test_calculator.cpp
#include <catch2/catch_test_macros.hpp>
#include "calculator.h"

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