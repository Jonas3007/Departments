#pragma once

#include "Coordinates.h"
#include "ShipConfig.h"
#include "GamePhase.h"
#include <vector>
#include <string>

struct GameStateDTO
{
	string player1Name;
	bool player1AllShipsDestroyed;
	vector<ShipConfig> player1ShipsToPlace;
	vector<Coordinates> player1Hits;
	vector<Coordinates> player1Misses;
	vector<Coordinates> player1Hitsreceived;

	string player2Name;
	bool player2AllShipsDestroyed;
	vector<ShipConfig> player2ShipsToPlace;
	vector<Coordinates> player2Hits;
	vector<Coordinates> player2Misses;
	vector<Coordinates> player2Hitsreceived;
	GamePhase currentPhase;
};