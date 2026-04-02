#pragma once
#include <vector>
#include <string>
#include "Coordinates.h"
#include <iostream>
using namespace std;


class InputParser
{
public:
	
	vector<Coordinates> placeShipInputTokenizer(string input);
	Coordinates fireInputTokenizer(string input);
	bool inputIsValid(string input);
};

