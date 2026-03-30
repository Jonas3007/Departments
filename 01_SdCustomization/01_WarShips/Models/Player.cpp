#include "ShipFactory.h"
#include <iostream>
#include "Ship.h"
#include "Coordinates.h"
#include "Player.h"


void Player::setName(string name)
{
	Name = name;
}
bool Player::checkForHit(Coordinates coords)
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
	return false;
}

bool Player::checkIfShipSizeAvailable(int shipSize)
{
	for(ShipConfig config : ShipsToPlace)
	{
		if(config.ShipSize == shipSize && config.Count > 0)
		{
			return true;
		}
	}
	return false;
}

void Player::placeShip(vector<Coordinates> coords, int ShipSize)
{
	if(!checkIfShipSizeAvailable(ShipSize))
	{
		cout << "Ship of size " << ShipSize << " not available for placement." << endl;
		return;
	}
	ShipFactory shipFactory;
	Ship newShip = shipFactory.CreateShip(coords, ShipSize);
	ShipInventory.push_back(newShip);
	for(int i = 0; i < ShipsToPlace.size(); i++)
	{
		if(ShipsToPlace[i].ShipSize == ShipSize)
		{
			ShipsToPlace[i].Count--;
			break;
		}
	}
}

void Player::placeFlag(Coordinates coords)
{
	Flag.push_back(coords);
}


void Player::checkAllShipsDestroyed()
{
	for(Ship ship : ShipInventory)
	{
		if(!ship.Destroyed)
		{
			AllShipsDestroyed = false;
			return;
		}
	}
	AllShipsDestroyed = true;
}

void Player::updateShipStatus()
{
	for(Ship ship : ShipInventory)
	{
		ship.CheckDestroyed();
	}
}	

void Player::checkIfAllShipsPlaced()
{
	for(auto const config : ShipsToPlace)
	{
		if(config.Count > 0)
		{
			AllShipsPlaced = false;
			return;
		}
		else if (config.Count == 0	)
		{
			AllShipsPlaced = true;
		}
	}
}
