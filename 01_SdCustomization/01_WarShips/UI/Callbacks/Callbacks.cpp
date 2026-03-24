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
//Helper
void setSelectedShipSize(Fl_Widget *widget, ShipPlacementData *spd)
{
	switch (widget->label()[0]) //Erste Buchstabe des Button-Labels
	{
		case 'B': // Battleship
			spd->selectedShipSize = 5;
			break;
		case 'C': // Cruiser
			spd->selectedShipSize = 4;
			break;
		case 'D': // Destroyer
			spd->selectedShipSize = 3;
			break;
		case 'S': // Submarine
			spd->selectedShipSize = 2;
			break;
		default:
			spd->selectedShipSize = 0;
	}
}
void takeInput_cb(Fl_Widget *widget, void *data)
{
	
}

void shipSelect_cb(Fl_Widget *widget, void *data)
{
	auto* spd = static_cast<ShipPlacementData*>(data);
	setSelectedShipSize(widget, spd);
	
}
