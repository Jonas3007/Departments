#include <vector>
#include "GameMaster.h"
#include "Coordinates.h"
#include "ShipFactory.h"
#include "ShipConfig.h"
#include "Ship.h"
#include <iostream>
#include <map>
#include "Player.h"
#include "Player_Window.h"
#include "Fl/Fl_Window.H"
#include "xyCoordinates.h"
#include "InputParser.h"
#include <FL/Fl.H>
#include "Callbacks.h"
#include "ShipPlacementData.h"
#include "UIHandler.h"
#include "GameOver_Window.h"
//---------------------
// Getter and Setter
//---------------------
// Setter
void GameMaster::setActivePlayer()
{
	if (CurrentPhase == Player1Turn || CurrentPhase == PlaceShipsP1)
	{
		ActivePlayer = Player1;
	}
	else if (CurrentPhase == Player2Turn || CurrentPhase == PlaceShipsP2)
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
void GameMaster::setPlayerNames(PlayerNames names)
{
	Player1.setName(names.Player1Name);
	Player2.setName(names.Player2Name);
}

// Update Player -> ActivePlayer to either update Player1 or Player2 depending on the current phase
void GameMaster::updatePlayer(Player player)
{
	if (CurrentPhase == Player1Turn || CurrentPhase == PlaceShipsP1)
	{
		Player1 = player;
	}
	else if (CurrentPhase == Player2Turn || CurrentPhase == PlaceShipsP2)
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
	if (CurrentPhase == PlaceShipsP1)
	{
		CurrentPhase = PlaceShipsP2;
	}
	else if (CurrentPhase == PlaceShipsP2)
	{
		if (Player1.AllShipsPlaced && Player2.AllShipsPlaced)
		{
			CurrentPhase = Player1Turn; // Default to Player 1 starting, can be randomized if desired
			uiHandler->toggleFinishTurnBtn(this);
			uiHandler->toggleFireBtn(this); // Enable the fire button for the first player's turn
		}
		else
		{
			CurrentPhase = PlaceShipsP2;
		}
	}
	else if (CurrentPhase == Player1Turn)
	{

		CurrentPhase = Player2Turn;
		firedThisTurn = false; // Reset the flag for the next player's turn
		uiHandler->toggleFinishTurnBtn(this);
		uiHandler->toggleFireBtn(this); // Enable the fire button for the next player's turn
	}
	else if (CurrentPhase == Player2Turn)
	{
		CurrentPhase = Player1Turn;
		firedThisTurn = false;
		uiHandler->toggleFinishTurnBtn(this);
		uiHandler->toggleFireBtn(this); // Enable the fire button for the next player's turn
	}
	setActivePlayer();
}
void GameMaster::selectRandomPlayer()
{
	int randomNum = rand() % 2; // Generates a random number, either 0 or 1
	if (randomNum == 0)
	{
		CurrentPhase = Player1Turn;
	}
	else
	{
		CurrentPhase = Player2Turn;
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
		for (int i = 0; i < shipSize; i++)
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
	if (xyIniCoords[0].x == xyIniCoords[1].x && xyIniCoords[0].y + shipSize - 1 <= 10 && xyIniCoords[0].x >= 1)
	{
		return true;
	}
	else if (xyIniCoords[0].y == xyIniCoords[1].y && xyIniCoords[0].x + shipSize - 1 <= 10 && xyIniCoords[0].y >= 1)
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
void GameMaster::checkPlayerHit(Coordinates targetCoords)
{
	if (CurrentPhase == Player1Turn)
	{
		if (Player2.checkForHit(targetCoords))
		{
			Player1.hits.push_back(targetCoords);
			cout << "Hit at " << targetCoords.Letter << targetCoords.Number << endl;
		}
		else
		{
			Player1.miss(targetCoords);
		}
		Player2.checkAllShipsDestroyed();
		uiHandler->updatePlayerWindows(this);
	}
	else
	{
		if (Player1.checkForHit(targetCoords))
		{
			Player2.hits.push_back(targetCoords);
			cout << "Hit at " << targetCoords.Letter << targetCoords.Number << endl;
		}
		else
		{
			Player2.miss(targetCoords);
		}
		Player1.checkAllShipsDestroyed();
		uiHandler->updatePlayerWindows(this);
	}
	if (Player1.AllShipsDestroyed || Player2.AllShipsDestroyed)
	{
		CurrentPhase = GameOver;
		createGameOverWindow();
		uiHandler->updatePhaseBox(this);
		return;
	}
	firedThisTurn = true;
	uiHandler->toggleFireBtn(this);
}
void GameMaster::PlacePlayerShip(string input, void *data)
{
	cout << "Current Player: " << ActivePlayer.Name << endl;
	uiHandler->updatePlayerWindows(this);
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
	if (CheckForOverlap(fullShipCoords, currentPlayerShips))
	{
		cout << "Ship not Placed: overlap" << endl;
		return;
	}

	if (!ActivePlayer.checkIfShipSizeAvailable(spd->selectedShipSize))
	{
		cout << "Ship of size " << spd->selectedShipSize << " not available for placement." << endl;
		return;
	}
	// ActivePlayer places Ship
	ActivePlayer.placeShip(fullShipCoords, spd->selectedShipSize);
	updatePlayer(ActivePlayer);
	uiHandler->updatePlayerWindows(this);
}

void GameMaster::FireAtCoordinates(string input, void *data)
{
	auto spd = static_cast<ShipPlacementData *>(data);
	InputParser coordsParser;
	Coordinates targetCoords = coordsParser.fireInputTokenizer(input);
	checkPlayerHit(targetCoords);
	uiHandler->toggleFinishTurnBtn(this); // Enable the finish turn button after firing
	uiHandler->updatePlayerWindows(this);
}
void GameMaster::checkShipsPlacedToUpdatePhase()
{
	Player1.checkIfAllShipsPlaced();
	Player2.checkIfAllShipsPlaced();
	if (Player1.AllShipsPlaced && !Player2.AllShipsPlaced)
	{
		updatePlayer(ActivePlayer);
		uiHandler->resetPlayerInputs();
		switchTurn();
		uiHandler->updatePlayerWindows(this);
		uiHandler->toggleTransitionScreen(this, true);
		
	}
	else if (Player1.AllShipsPlaced && Player2.AllShipsPlaced)
	{	
		uiHandler->resetPlayerInputs();
		switchTurn(); 
		uiHandler->toggleShipPlacementElements(this);
		uiHandler->toggleFinishTurnBtn(this);
		uiHandler->updatePlayerTurnBox(this);
		uiHandler->updatePhaseBox(this);
		uiHandler->updatePlayerWindows(this);
		uiHandler->toggleTransitionScreen(this, true);
	}
}

void GameMaster::InitializeGame()
{
	SetPlayer1(new Player());
	SetPlayer2(new Player());

	CurrentPhase = PickNamePhase;
}

void GameMaster::checkNamesEntered()
{
	if (!Player1.Name.empty() && !Player2.Name.empty())
	{
		uiHandler->toggleEnterNamesBtn(this);
	}
}
void GameMaster::finishTurn()
{
	uiHandler->toggleTransitionScreen(this, true);
	switchTurn();
	uiHandler->updatePlayerWindows(this);
}

void GameMaster::createGameOverWindow()
{
	(new GameOverWindow(this))->show();
}
