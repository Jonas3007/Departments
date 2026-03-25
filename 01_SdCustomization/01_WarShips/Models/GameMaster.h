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
		
		
		//Initialize Game
		void InitializeGame();
		
		//----------------------
		// Helper Functions
		//----------------------
		// Update UIContext
		void updateUIContext(Player player);
		// Update Playerattributes
		void updatePlayer(Player player);
		// Turn Helper
		void switchTurn();
		void randomPlayerStart();
		//Coordinate Helpers
		vector<Coordinates> CalculateGridOccupancie(vector<Coordinates> initialCoords, int shipSize); // calculates the coordinates which will be occuppied by a ship
		bool placedInGrid(vector<Coordinates> coords, int shipSize); // checks if the ship placement is within the grid boundaries
		bool CheckForOverlap(vector<Coordinates> occupiedCoords, vector<Ship> existingShips); // checks if the proposed ship placement overlaps with existing ships
		//Attack Helpers
		bool checkIfAttackIsHit(Coordinates coords, PlayerIntel opponentIntel); // checks if the attack coordinates hit an opponent's ship
		//Place player ships
		void PlacePlayerShip(string input, void* data);
};
