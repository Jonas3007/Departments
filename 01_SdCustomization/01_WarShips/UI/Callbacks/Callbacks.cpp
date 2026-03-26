#include "Callbacks.h"
#include "PlayerIntel.h"
#include "GameMaster.h"
#include "Player_Window.h"
#include "UIContext.h"
#include <Fl/Fl_Button.H>
#include <Fl/Fl_Input.H>
#include <iostream>
#include <vector>
#include <string>
#include "Coordinates.h"
#include "InputParser.h"
#include "ShipPlacementData.h"
#include "Name_Window.h"
// Helper
int setSelectedShipSize(Fl_Widget *widget)
{
	switch (widget->label()[0]) // Erste Buchstabe des Button-Labels
	{
	case 'B': // Battleship
		return 5;
		break;
	case 'C': // Cruiser
		return 4;
		break;
	case 'D': // Destroyer
		return 3;
		break;
	case 'S': // Submarine
		return 2;
		break;
	default:
		return 0; // Unbekannter Button
	}
}

// Callbacks
void takeInput_cb(Fl_Widget *widget, void *data)
{
	auto spd = static_cast<ShipPlacementData *>(data);
	std::cout << "Placing ship of size " << spd->selectedShipSize << " at coordinates: " << spd->coordsInput->value() << std::endl;
	spd->gameMaster->PlacePlayerShip(spd->coordsInput->value(), spd);
	bool P1ShipsPlaced = spd->gameMaster->Player1.checkIfAllShipsPlaced();
	bool P2ShipsPlaced = spd->gameMaster->Player2.checkIfAllShipsPlaced();
	if (P1ShipsPlaced && P2ShipsPlaced)
	{		
		spd->gameMaster->selectRandomPlayer();
		spd->gameMaster->uiHandler->toggleShipPlacementElements(spd->gameMaster);
		spd->gameMaster->uiHandler->updatePlayerTurnBox(spd->gameMaster);
		spd->gameMaster->uiHandler->updatePhaseBox(spd->gameMaster);
		spd->gameMaster->uiHandler->updatePlayerWindows(spd->gameMaster);
	}
}

void shipSelect_cb(Fl_Widget *widget, void *data)
{
	auto *spd = static_cast<ShipPlacementData *>(data);
	spd->selectedShipSize = setSelectedShipSize(widget);
	spd->selectedShipOutput->value(widget->label());
}
void fireInput_cb(Fl_Widget *widget, void *data)
{
	auto spd = static_cast<ShipPlacementData *>(data);
	
	cout << "Fire Input Callback triggered" << endl;
	spd->gameMaster->FireAtCoordinates(spd->coordsInput->value(), spd);
}

void createNameWindow_cb(Fl_Widget *widget, void *data)
{
	auto spd = static_cast<ShipPlacementData *>(data);
	(new NameWindow(spd->gameMaster))->show();
}
void getPlayerNames_cb(Fl_Widget *widget, void *data)
{
	auto gameMaster = static_cast<GameMaster *>(data);	
	string playerName = gameMaster->uiHandler->getPlayerName();
	if (gameMaster->Player1.Name.empty())
	{
		gameMaster->Player1.setName(playerName);
		gameMaster->uiHandler->nameInput->value(""); // Clear input field after setting name
	}
	else if (gameMaster->Player2.Name.empty())
	{
		gameMaster->Player2.setName(playerName);
		gameMaster->uiHandler->nameInput->value(""); // Clear input field after setting name	
		
		cout << "Player 1 Name: " << gameMaster->Player1.Name << endl;
		cout << "Player 2 Name: " << gameMaster->Player2.Name << endl;
	}
	if (!gameMaster->Player1.Name.empty() && !gameMaster->Player2.Name.empty())
	{
		gameMaster->updateUIContext(gameMaster->Player1);
		gameMaster->updateUIContext(gameMaster->Player2);
		gameMaster->CurrentPhase = PlaceShipsP1;
		gameMaster->ActivePlayer = gameMaster->Player1;
		gameMaster->uiHandler->updatePhaseBox(gameMaster);
		gameMaster->uiHandler->updatePlayerTurnBox(gameMaster);
		gameMaster->uiHandler->toggleShipPlacementElements(gameMaster);
	}
}