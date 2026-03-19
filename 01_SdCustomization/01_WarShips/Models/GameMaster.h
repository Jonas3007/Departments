#pragma once
#include "Coordinates.h"
#include "PlayerIntel.h"
#include "ShipFactory.h"
#include "ShipConfig.h"
#include "Ship.h"
#include "UIContext.h"
#include <vector>
#include <string>



enum GamePhase
{
	PlaceShips,
	Player1Turn,
	Player2Turn,
	GameOver
};


class GameMaster
{
	public:
		GamePhase CurrentPhase;
		vector<ShipConfig> ShipConfigs;
		vector<Ship> PlayerShips;
		vector<Ship> OpponentShips;

		void InitializeGame();
};