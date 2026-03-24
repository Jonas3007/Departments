#include "InputParser.h"	
#include <vector>
#include <string>
#include "Coordinates.h"
#include <iostream>

using namespace std;	

bool inputIsValid(string input)
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
		string coordPart = input.substr(0, colPos);
		input.erase(0, colPos + 1);
		if(inputIsValid(coordPart))
		{
			char letter = toupper(coordPart[0]);
			int number = stoi(coordPart.substr(1));
			if (number < 1 || number > 10)
			{
				cout << "Ungültige Zahl in Eingabe: " << coordPart << endl;
				break;
			}
			Coordinates coords = {letter, number};
			shipPlacementCoords.push_back(coords);
		}
		else
		{
			cout << "Ungültige Eingabe: " << coordPart << endl;
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