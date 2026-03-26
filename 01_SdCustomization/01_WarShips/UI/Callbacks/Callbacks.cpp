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
void testforPlaceShipInput(Fl_Widget *widget, void *data)
{
	auto spd = static_cast<ShipPlacementData *>(data);
	cout << "Test for Place Ship Input Callback triggered, input was: " << spd->coordsInput->value() << endl;
}
void getPlayerNames_cb(Fl_Widget *widget, void *data)
{
	auto pn = static_cast<PlayerNames *>(data);
	string playerName = pn->nameInput->value();
	if (pn->Player1Name.empty())
	{
		pn->Player1Name = playerName;
		pn->nameInput->value("");
		pn->nameInput->label("Player 2:");
	}
	else if (pn->Player2Name.empty())
	{
		pn->Player2Name = playerName;
		pn->nameInput->value("");
		pn->nameInput->deactivate();
		pn->nameInput->hide();
		cout << "Player 1 Name: " << pn->Player1Name << endl;
		cout << "Player 2 Name: " << pn->Player2Name << endl;
	}
	if (!pn->Player1Name.empty() && !pn->Player2Name.empty())
	{
		pn->gameMaster->setPlayerNames(*pn);
		pn->gameMaster->updateUIContext(pn->gameMaster->Player1);
		pn->gameMaster->updateUIContext(pn->gameMaster->Player2);
		pn->gameMaster->selectRandomPlayer();
	}
}