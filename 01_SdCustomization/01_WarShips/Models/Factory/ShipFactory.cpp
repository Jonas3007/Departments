#include "ShipFactory.h"
#include "Ship.h"
#include "Coordinates.h"
#include <iostream>
#include <vector>

using namespace std;

Ship ShipFactory::CreateShip(vector<Coordinates> coords, int shipSize)
{
	Ship newShip(coords, shipSize);
	return newShip;	
}
Ship ShipFactory::ExistingShip(vector<Coordinates> coords, int shipSize, vector<Coordinates> hitsReceived)
{
	Ship existingShip(coords, shipSize, hitsReceived);
	return existingShip;	
}
