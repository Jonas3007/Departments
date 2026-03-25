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
}

void shipSelect_cb(Fl_Widget *widget, void *data)
{
	auto *spd = static_cast<ShipPlacementData *>(data);
	spd->selectedShipSize = setSelectedShipSize(widget);
	spd->selectedShipOutput->value(widget->label());
}
void fireInput_cb(Fl_Widget *widget, void *data)
{
	cout << "Fire Input Callback triggered" << endl;
}
void testforPlaceShipInput(Fl_Widget *widget, void *data)
{
	auto spd = static_cast<ShipPlacementData *>(data);
	cout << "Test for Place Ship Input Callback triggered, input was: " << spd->coordsInput->value() << endl;
}