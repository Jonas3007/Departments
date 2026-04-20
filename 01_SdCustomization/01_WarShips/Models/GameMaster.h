#pragma once
#include "Coordinates.h"
#include "ShipFactory.h"
#include "ShipConfig.h"
#include "Ship.h"
#include <vector>
#include <string>
#include "GamePhase.h"
#include "Player.h"
#include "GameStateDTO.h"
#include "ShipPlacementData.h"


struct ShipPlacementData;

class GameMaster
{
	public:
		GamePhase CurrentPhase;
		Player Player1;
		Player Player2;
		Player ActivePlayer;
	
		
		//Getter and Setter
		void setActivePlayer();
		void SetPlayer1(Player* player);
		void SetPlayer2(Player* player);
		void setPlayerNames(string player1, string player2);
		
		// builds DTO that later can be sent to the client to update the game state on the client side / update ui
		GameStateDTO buildGameStateDTO(const string &playerName);		
		
		//Initialize Game
		void InitializeGame(string player1Name, string player2Name);
		
		// Update Playerattributes
		void updatePlayer(Player player);
		
		// Turn Helper
		void switchTurn();
		
		//Coordinate Helpers
		vector<Coordinates> CalculateGridOccupancie(vector<Coordinates> initialCoords, int shipSize); // calculates the coordinates which will be occuppied by a ship
		bool placedInGrid(vector<Coordinates> coords, int shipSize); // checks if the ship placement is within the grid boundaries
		bool CheckForOverlap(vector<Coordinates> occupiedCoords, vector<Ship> existingShips); // checks if the proposed ship placement overlaps with existing ships
		
		//Player Actions
		void checkPlayerHit(Coordinates targetCoords);
		void PlacePlayerShip(string data);
		void FireAtCoordinates(string input);
		
};
