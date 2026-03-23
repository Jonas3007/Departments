#include "ShipFactory.h"
#include <iostream>
#include "Ship.h"
#include "Coordinates.h"
#include "Player.h"

bool Player::CheckForHit(Coordinates coords)
{
	for (Ship ship: ShipInventory )
	{
		for (Coordinates shipcoords : ship.GridLocation)
		{
			if (shipcoords.Letter == coords.Letter && shipcoords.Number == coords.Number)
			{
				// ship.TakeHit(coords);
				hitsReceived.push_back(coords);
				return true;
			}
		}
	}
	return false;
}

void Player::placeShip(vector<Coordinates> coords, int ShipSize)
{
	ShipFactory shipFactory;
	Ship newShip = shipFactory.CreateShip(coords, ShipSize);
	ShipInventory.push_back(newShip);
	for(ShipConfig config : ShipsToPlace)
	{
		if(config.ShipSize == ShipSize)
		{
			config.Count --;
			break;
		}
	}
}