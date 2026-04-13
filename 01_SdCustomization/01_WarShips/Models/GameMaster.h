#pragma once
#include "Coordinates.h"
#include "ShipFactory.h"
#include "ShipConfig.h"
#include "Ship.h"
#include <vector>
#include <string>
#include "GamePhase.h"
#include "Player.h"
#include "PlayerNames.h"

#include "ShipPlacementData.h"


struct ShipPlacementData;

class GameMaster
{
	public:
		GamePhase CurrentPhase;
		Player Player1;
		Player Player2;
		Player ActivePlayer;
	
		bool firedThisTurn; // Flag to track if the active player has fired during their turn
		
		
		//Getter and Setter
		void setActivePlayer();
		void SetPlayer1(Player* player);
		void SetPlayer2(Player* player);
		void setPlayerNames(PlayerNames names);
		
		
		//Initialize Game
		void InitializeGame();
		//check if Names have been entered 
		void checkNamesEntered();

		// Update Playerattributes
		void updatePlayer(Player player);
		// Turn Helper
		void switchTurn();
		void selectRandomPlayer();
		void finishTurn();	
		//Coordinate Helpers
		vector<Coordinates> CalculateGridOccupancie(vector<Coordinates> initialCoords, int shipSize); // calculates the coordinates which will be occuppied by a ship
		bool placedInGrid(vector<Coordinates> coords, int shipSize); // checks if the ship placement is within the grid boundaries
		bool CheckForOverlap(vector<Coordinates> occupiedCoords, vector<Ship> existingShips); // checks if the proposed ship placement overlaps with existing ships
		//PLace Ship Helper
		void checkShipsPlacedToUpdatePhase();
		//Attack Helpers
		void checkPlayerHit(Coordinates targetCoords);
		void PlacePlayerShip(string input, void* data);
		void FireAtCoordinates(string input, void* data);
		
		//GameOver Helper
		void createGameOverWindow();
};
