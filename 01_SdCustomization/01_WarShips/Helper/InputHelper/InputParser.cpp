#include "InputParser.h"	
#include <vector>
#include <string>
#include "Coordinates.h"
#include <iostream>

using namespace std;	

bool InputParser::inputIsValid(string input)
{	

	if(input.find("-.!§$%&/()=?`´+*~#'\"|\\") != string::npos)
	{
		return false;
	}
	else if(input.find("KLMNOPQRSTUVWXYZ") != string::npos)
	{
		return false;
	}
	else if(input.find("klnopqrstuvwxyz") != string::npos)
	{
		return false;
	}
	else if (input.size() > 3 || input.size() < 2)
	{
		return false;
	}
	else if (input.empty())
	{
		return false;
	}
	else
	{
		return true;
	}
}
 
vector<Coordinates> InputParser::placeShipInputTokenizer(string input)
{
	vector<Coordinates> shipPlacementCoords;
	while(true)
	{
		
		int colPos = input.find(',');
		if(colPos == string::npos)
		{
			break;
		}
		string coordPart1 = input.substr(0, colPos);
		string coordPart2 = input.substr(colPos + 1);	
		if(inputIsValid(coordPart1) && inputIsValid(coordPart2))
		{
			char letter1 = toupper(coordPart1[0]);
			int number1 = stoi(coordPart1.substr(1));
			char letter2 = toupper(coordPart2[0]);
			int number2 = stoi(coordPart2.substr(1));
			if (number1 < 1 || number1 > 10 || number2 < 1 || number2 > 10)
			{
				cout << "Ungültige Zahl in Eingabe: " << input << endl;
				break;
			}
			Coordinates coords1 = {letter1, number1};
			Coordinates coords2 = {letter2, number2};
			shipPlacementCoords.push_back(coords1);
			shipPlacementCoords.push_back(coords2);
			break;
		}
		else
		{
			cout << "Ungültige Eingabe: " << input << endl;
			break;
		}
		
	
	}
	return shipPlacementCoords;
}

Coordinates InputParser::fireInputTokenizer(string input)
{
	if(!inputIsValid(input))
	{
		cout << "Ungültige Eingabe: " << input << endl;
		return {'X', -1};
	}
	char letter = toupper(input[0]);
	int number = stoi(input.substr(1));
	if (number < 1 || number > 10)
	{
		cout << "Ungültige Zahl in Eingabe: " << input << endl;
		return {'X', -1}; // Ungültige Koordinaten zurückgeben
	}
	Coordinates coords = {letter, number};
	return coords;
} 