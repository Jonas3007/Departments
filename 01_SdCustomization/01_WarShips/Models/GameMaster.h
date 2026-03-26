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
#include "Player.h"
#include "PlayerNames.h"
#include "UIElements.h"
#include "UIHandler.h"
#include "ShipPlacementData.h"


struct ShipPlacementData;

class GameMaster
{
	public:
		GamePhase CurrentPhase;
		Player Player1;
		Player Player2;
		Player ActivePlayer;
		UIContext UIctx;
		
		
		//Getter and Setter
		void setActivePlayer();
		void SetPlayer1(Player* player);
		void SetPlayer2(Player* player);
		void setPlayerNames(PlayerNames names);
		
		
		//Initialize Game
		void InitializeGame();
		
		//----------------------
		// Helper Functions
		//----------------------
		// Update UIContext
		void updateP1UIContext(Player player);
		void updateP2UIContext(Player player);
		void updateUIContext(Player player);
		//Update UI
		void reColorGridCell(UIElements uiData, string cellPos);
		void updatePlayerTurnBox(UIElements uiData, ShipPlacementData *spd);
		// Update Playerattributes
		void updatePlayer(Player player);
		// Turn Helper
		void switchTurn();
		void selectRandomPlayer();
		//Coordinate Helpers
		vector<Coordinates> CalculateGridOccupancie(vector<Coordinates> initialCoords, int shipSize); // calculates the coordinates which will be occuppied by a ship
		bool placedInGrid(vector<Coordinates> coords, int shipSize); // checks if the ship placement is within the grid boundaries
		bool CheckForOverlap(vector<Coordinates> occupiedCoords, vector<Ship> existingShips); // checks if the proposed ship placement overlaps with existing ships
		//Attack Helpers
		void PlacePlayerShip(string input, void* data);
		void FireAtCoordinates(string input, void* data);
};
