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
				ship.TakeHit(coords);
				hitsReceived.push_back(coords);
				return true;
			}
		}
	}
}

void Player::placeShip(vector<Coordinates> coords, int ShipSize)
{
	
}