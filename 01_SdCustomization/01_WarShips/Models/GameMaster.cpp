#include <vector>
#include "GameMaster.h"
#include "Coordinates.h"
#include "PlayerIntel.h"
#include "ShipFactory.h"
#include "ShipConfig.h"
#include "Ship.h"
#include "UIContext.h"
#include <iostream>
#include <map>
struct xyCoordinates
{
	int x; // Letter
	int y; // Number
};
xyCoordinates coordsConverter(char letter, int number)
{
	xyCoordinates xyCoords;
	std::map<char, int> letterToX = {
		{'A', 1},
		{'B', 2},
		{'C', 3},
		{'D', 4},
		{'E', 5},
		{'F', 6},
		{'G', 7},
		{'H', 8},
		{'I', 9},
		{'J', 10}
	};
	xyCoords.x = letterToX[letter];
	xyCoords.y = number;
	return xyCoords;
}
Coordinates xyCoordsToCoords(xyCoordinates xyCoords)
{
	std::map<int, char> xToLetter = {
		{1, 'A'},
		{2, 'B'},
		{3, 'C'},
		{4, 'D'},
		{5, 'E'},
		{6, 'F'},
		{7, 'G'},
		{8, 'H'},
		{9, 'I'},
		{10, 'J'}
	};
	char letter = xToLetter[xyCoords.x];
	int number = xyCoords.y;
	return {letter, number};
}

vector<Coordinates> GameMaster::CalculateGridOccupancie(vector<Coordinates> initialCoords, int shipSize)
{

	vector<xyCoordinates> xyInitialCoordinates;
	for (Coordinates coords : initialCoords)
	{
		xyCoordinates xyCoord = coordsConverter(coords.Letter, coords.Number);
		xyInitialCoordinates.push_back(xyCoord);
	}
	vector<xyCoordinates>xyShipCoordinates;
	if(xyInitialCoordinates[0].x == xyInitialCoordinates[1].x )
	{ 	
		for(int i = 0; i < shipSize; i++)
		{
			xyShipCoordinates.push_back(xyInitialCoordinates[0]);
			xyInitialCoordinates[0].y ++;
		}
	}
	else if(xyInitialCoordinates[0].y == xyInitialCoordinates[1].y)
	{
		for(int i = 0; i > shipSize; i++)
		{
			xyShipCoordinates.push_back(xyInitialCoordinates[0]);
			xyInitialCoordinates[0].x ++;
		}
	}
	vector<Coordinates> exactShipCoordinates;
	for(xyCoordinates xyCoords : xyShipCoordinates)
	{
		Coordinates coords = xyCoordsToCoords(xyCoords);
		exactShipCoordinates.push_back(coords);
	}
	
	return exactShipCoordinates;
}
bool GameMaster::placedInGrid(vector<Coordinates> initialCoords, int shipSize)
{
	vector<xyCoordinates> xyIniCoords;
	for(Coordinates coords : initialCoords)
	{
		xyCoordinates xyCoords = coordsConverter(coords.Letter, coords.Number);
		xyIniCoords.push_back(xyCoords);
	}
	
	//Checking if ship is in Grid
	if(xyIniCoords[0].x == xyIniCoords[1].x && xyIniCoords[0].x + shipSize -1 <= 10 && xyIniCoords[0].x >= 1)
	{
		return true;
	}
	else if(xyIniCoords[0].y == xyIniCoords[1].y && xyIniCoords[0].y + shipSize -1 <= 10 && xyIniCoords[0].y >= 1)
	{
		return true;
	}
	return false;
}

bool GameMaster::CheckForOverlap(vector<Coordinates> occupiedCoords, vector<Ship> existingShips)
{
	for(Ship ship : existingShips)
	{
		for(Coordinates coords : ship.GridLocation)
		{
			for(Coordinates occupiedCoord : occupiedCoords)
			{
				if(coords.Letter == occupiedCoord.Letter && coords.Number == occupiedCoord.Number)
				{
					return true;
				}
			}
		}
	}
	return false;
}