#include <vector>
#include "GameMaster.h"
#include "Coordinates.h"
#include "PlayerIntel.h"
#include "ShipFactory.h"
#include "ShipConfig.h"
#include "Ship.h"
#include "UIContext.h"
#include <iostream>
#include <map>
#include "Player.h"
#include "Player_Window.h"
#include "Fl/Fl_Window.H"
#include "xyCoordinates.h"
#include "InputParser.h"
#include <FL/Fl.H>
//---------------------
// Getter and Setter
//---------------------
//Setter
void GameMaster::setActivePlayer()
{
	if (CurrentPhase == Player1Turn || CurrentPhase == PlaceShipsP1 || CurrentPhase == PickNamePlayer1)
	{
		ActivePlayer = Player1;
	}
	else if (CurrentPhase == Player2Turn || CurrentPhase == PlaceShipsP2 || CurrentPhase == PickNamePlayer2)
	{
		ActivePlayer = Player2;
	}	
}
void GameMaster::SetPlayer1(Player *player)
{
	Player1 = *player;
}
void GameMaster::SetPlayer2(Player *player)
{
	Player2 = *player;
}
//---------------------
//Update UIContext
//---------------------
void GameMaster::updateUIContext(Player player)
{
	if(CurrentPhase == Player1Turn || CurrentPhase == PlaceShipsP1)
	{
		UIctx.Player1Intel.PlayerName = player.Name;
		UIctx.Player1Intel.Alive = !player.AllShipsDestroyed;
		UIctx.Player1Intel.AllShipsPlaced = player.checkIfAllShipsPlaced();
		UIctx.Player1Intel.ShipsInventory = player.ShipInventory;
		UIctx.Player1Intel.Flag = player.Flag;
		UIctx.Player1Intel.ShotsFired = player.ShotsFired;
		UIctx.Player1Intel.hitsReceived = player.hitsReceived;
	}
	else if(CurrentPhase == Player2Turn || CurrentPhase == PlaceShipsP2)
	{
		UIctx.Player2Intel.PlayerName = player.Name;
		UIctx.Player2Intel.Alive = !player.AllShipsDestroyed;
		UIctx.Player2Intel.AllShipsPlaced = player.checkIfAllShipsPlaced();
		UIctx.Player2Intel.ShipsInventory = player.ShipInventory;
		UIctx.Player2Intel.Flag = player.Flag;
		UIctx.Player2Intel.ShotsFired = player.ShotsFired;
		UIctx.Player2Intel.hitsReceived = player.hitsReceived;
	}
}

void GameMaster::updatePlayer(Player player)
{
	if(CurrentPhase == Player1Turn || CurrentPhase == PlaceShipsP1)
	{
		Player1 = player;
	}
	else if(CurrentPhase == Player2Turn || CurrentPhase == PlaceShipsP2)
	{
		Player2 = player;
	}
}
//---------------------
// Helper Functions
//---------------------
// Turn Helper
void GameMaster::switchTurn()
{
	if (CurrentPhase == Player1Turn)
	{
		CurrentPhase = Player2Turn;
	}
	else if (CurrentPhase == Player2Turn)
	{
		CurrentPhase = Player1Turn;
	}
	setActivePlayer();
}
// Random Start
void GameMaster::randomPlayerStart()
{
	int randomNum = rand() % 2; // Generates a random number, either 0 or 1
	if (randomNum == 0)
	{
		CurrentPhase = PickNamePlayer1;
	}
	else
	{
		CurrentPhase = PickNamePlayer2;
	}
	setActivePlayer();
}
// Coordinate Helper
xyCoordinates coordsConverter(char letter, int number)
{
	xyCoordinates xyCoords;
	std::map<char, int> letterToX = {
		{'A', 1},
		{'B', 2},
		{'C', 3},
		{'D', 4},
		{'E', 5},
		{'F', 6},
		{'G', 7},
		{'H', 8},
		{'I', 9},
		{'J', 10}};
	xyCoords.x = letterToX[letter];
	xyCoords.y = number;
	return xyCoords;
}
Coordinates xyCoordsToCoords(xyCoordinates xyCoords)
{
	std::map<int, char> xToLetter = {
		{1, 'A'},
		{2, 'B'},
		{3, 'C'},
		{4, 'D'},
		{5, 'E'},
		{6, 'F'},
		{7, 'G'},
		{8, 'H'},
		{9, 'I'},
		{10, 'J'}};
	char letter = xToLetter[xyCoords.x];
	int number = xyCoords.y;
	return {letter, number};
}
// Placement Helper
vector<Coordinates> GameMaster::CalculateGridOccupancie(vector<Coordinates> initialCoords, int shipSize)
{

	vector<xyCoordinates> xyInitialCoordinates;
	for (Coordinates coords : initialCoords)
	{
		xyCoordinates xyCoord = coordsConverter(coords.Letter, coords.Number);
		xyInitialCoordinates.push_back(xyCoord);
	}
	vector<xyCoordinates> xyShipCoordinates;
	if (xyInitialCoordinates[0].x == xyInitialCoordinates[1].x)
	{
		for (int i = 0; i < shipSize; i++)
		{
			xyShipCoordinates.push_back(xyInitialCoordinates[0]);
			xyInitialCoordinates[0].y++;
		}
	}
	else if (xyInitialCoordinates[0].y == xyInitialCoordinates[1].y)
	{
		for (int i = 0; i > shipSize; i++)
		{
			xyShipCoordinates.push_back(xyInitialCoordinates[0]);
			xyInitialCoordinates[0].x++;
		}
	}
	vector<Coordinates> exactShipCoordinates;
	for (xyCoordinates xyCoords : xyShipCoordinates)
	{
		Coordinates coords = xyCoordsToCoords(xyCoords);
		exactShipCoordinates.push_back(coords);
	}

	return exactShipCoordinates;
}
bool GameMaster::placedInGrid(vector<Coordinates> initialCoords, int shipSize)
{
	vector<xyCoordinates> xyIniCoords;
	for (Coordinates coords : initialCoords)
	{
		xyCoordinates xyCoords = coordsConverter(coords.Letter, coords.Number);
		xyIniCoords.push_back(xyCoords);
	}

	// Checking if ship is in Grid
	if (xyIniCoords[0].x == xyIniCoords[1].x && xyIniCoords[0].x + shipSize - 1 <= 10 && xyIniCoords[0].x >= 1)
	{
		return true;
	}
	else if (xyIniCoords[0].y == xyIniCoords[1].y && xyIniCoords[0].y + shipSize - 1 <= 10 && xyIniCoords[0].y >= 1)
	{
		return true;
	}
	return false;
}
bool GameMaster::CheckForOverlap(vector<Coordinates> occupiedCoords, vector<Ship> existingShips)
{
	for (Ship ship : existingShips)
	{
		for (Coordinates coords : ship.GridLocation)
		{
			for (Coordinates occupiedCoord : occupiedCoords)
			{
				if (coords.Letter == occupiedCoord.Letter && coords.Number == occupiedCoord.Number)
				{
					return true;
				}
			}
		}
	}
	return false;
}
// Player Helperprocesses
void GameMaster::PlacePlayerShip(string input, void *data)
{
	auto spd = static_cast<ShipPlacementData *>(data);
	InputParser coordsParser;
	vector<Coordinates> initShipCoords = coordsParser.placeShipInputTokenizer(input);
	if (!placedInGrid(initShipCoords, spd->selectedShipSize))
	{
		cout << "Ship not placed: not in grid" << endl;
		return;
	}
	vector<Coordinates> fullShipCoords = CalculateGridOccupancie(initShipCoords, spd->selectedShipSize);
	vector<Ship> currentPlayerShips = ActivePlayer.ShipInventory;
	if(CheckForOverlap(fullShipCoords, currentPlayerShips))
	{
		cout<<"Ship not Placed: overlap"<<endl;
		return;
	}
	ActivePlayer.placeShip(fullShipCoords, spd->selectedShipSize);
	if(ActivePlayer.checkIfAllShipsPlaced())
	{
		updateUIContext(ActivePlayer);
		updatePlayer(ActivePlayer);
		switchTurn();
		spd->selectedShipSize = 0;
		spd->selectedShipOutput->value("");
		return;
	}
	updateUIContext(ActivePlayer);
	updatePlayer(ActivePlayer);
	spd->selectedShipOutput->value("");
}

void GameMaster::InitializeGame()
{
	Player player1;
	Player player2;

	SetPlayer1(&player1);
	SetPlayer2(&player2);
	
	CurrentPhase = PlaceShipsP1;
	UIctx.CurrentPhase = CurrentPhase;
	
}