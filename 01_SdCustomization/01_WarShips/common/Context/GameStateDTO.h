#pragma once

#include "Coordinates.h"
#include "ShipConfig.h"
#include "GamePhase.h"
#include <vector>
#include <string>

using namespace std;
struct GameStateDTO
{
	GamePhase currentPhase;
	int playerIndex;
	string playerName;
	string opponentName;
	bool playerAllShipsDestroyed;
	vector<ShipConfig> playerShipsToPlace;
	vector<Coordinates> playerHits;
	vector<Coordinates> playerMisses;
	vector<Coordinates> playerHitsreceived;
	vector<Coordinates> shipsPlaced;
};