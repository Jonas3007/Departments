#pragma once
#include <vector>
#include <string>
#include "Coordinates.h"
#include <iostream>
#include "ShipPlacementData.h"
using namespace std;


class InputParser
{
public:
	
	ShipPlacementData placeShipInputTokenizer(string input);
	Coordinates fireInputTokenizer(string input);
	bool inputIsValid(string input);
};

