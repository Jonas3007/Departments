#include "ShipFactory.h"
#include "Ship.h"
#include "Coordinates.h"
#include "SchlachtSchiff.h"
#include "Kreuzer.h"
#include "Zerstörer.h"
#include "U-Boot.h"
#include <iostream>
#include <vector>
#include "Coordinates.h"
using namespace std;

Ship ShipFactory::CreateShip(vector<Coordinates> coords, int shipSize)
{
	switch(shipSize)
	{
		case 2:
			return new U_Boot(coords);
		case 3:
			return Zerstörer(coords);
		case 4:
			return Kreuzer(coords);
		case 5:
			return SchlachtSchiff(coords);
		default:
			cout << "Invalid ship size. Returning default ship." << endl;
	}
}