#pragma once
#include "Coordinates.h"
#include "PlayerIntel.h"
#include "ShipFactory.h"
#include "ShipConfig.h"
#include "Ship.h"
#include "UIContext.h"
#include <vector>
#include <string>
#include "GamePhase.h"





class GameMaster
{
	public:
		GamePhase CurrentPhase;
		vector<ShipConfig> ShipConfigs;
		vector<Ship> Player1Ships;
		vector<Ship> Player2Ships;
		
		//Main
		void InitializeGame();
		
		//Game Loops
		void PlaceShipsPhase(UIContext *UIctx, PlayerIntel player1Intel, PlayerIntel player2Intel);
		void MainLoop();
		void GameOver();
		//Helper
		vector<Coordinates> CalculateGridOccupancie(vector<Coordinates> initialCoords, int shipSize);
		bool placedInGrid(vector<Coordinates> coords, int shipSize);
		bool CheckForOverlap(vector<Coordinates> occupiedCoords, vector<Ship> existingShips);

		
};
