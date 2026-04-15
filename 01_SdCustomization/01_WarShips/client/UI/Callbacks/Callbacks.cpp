#include "Callbacks.h"
#include "GameMaster.h"
#include "Player_Window.h"
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
	
	
}

void shipSelect_cb(Fl_Widget *widget, void *data)
{
	auto *spd = static_cast<ShipPlacementData *>(data);
	spd->selectedShipSize = setSelectedShipSize(widget);
	
}
void fireInput_cb(Fl_Widget *widget, void *data)
{
	auto spd = static_cast<ShipPlacementData *>(data);
	cout << "Fire Input Callback triggered" << endl;
	
}

void createNameWindow_cb(Fl_Widget *widget, void *data)
{
	
	NameWindow *nameWindow = new NameWindow();
	nameWindow->show();
}
void getPlayerNames_cb(Fl_Widget *widget, void *data)
{
	
}
void finishTurn_cb(Fl_Widget *widget, void *data)
{
	cout << "Finish Turn Callback triggered" << endl;
	
}
void continue_cb(Fl_Widget *widget, void *data)
{
	
}
void playTurn_cb(Fl_Widget *widget, void *data)
{

}
