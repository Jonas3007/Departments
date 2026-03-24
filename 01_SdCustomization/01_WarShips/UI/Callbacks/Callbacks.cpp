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
//Helper
int setSelectedShipSize(Fl_Widget *widget)
{
	switch (widget->label()[0]) //Erste Buchstabe des Button-Labels
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

//Callbacks
void takeInput_cb(Fl_Widget *widget, void *data)
{
	InputParser parser;
	auto spd = static_cast<ShipPlacementData*>(data);	
	if(widget->label() == "Place Ship")
	{
		
		vector<Coordinates> shipCoords = parser.placeShipInputTokenizer(spd->coordsInput->value());
		std::cout << "Placing ship of size " << spd->selectedShipSize << " at coordinates: " << spd->coordsInput->value() << std::endl;
		
	}
	else if(widget->label() == "Fire!")
	{
		Coordinates fireCoords = parser.fireInputTokenizer(spd->coordsInput->value());
		std::cout << "Firing at coordinates: " << spd->coordsInput->value() << std::endl;
	}
}

void shipSelect_cb(Fl_Widget *widget, void *data)
{
	auto* spd = static_cast<ShipPlacementData*>(data);
	spd->selectedShipSize = setSelectedShipSize(widget);
	spd->selectedShipOutput->value(widget->label());
}
