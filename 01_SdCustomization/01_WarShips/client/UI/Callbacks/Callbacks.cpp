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
#include "Lobby_Window.h"
#include "inputData.h"
#include "UIHandler.h"
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

void setClientMessageHandler(shared_ptr<ClientMessageHandler> handler)
{
	messageHandler = std::move(handler);
}
// Callbacks
void placeShip_cb(Fl_Widget *widget, void *data)
{
	auto iData = static_cast<inputData *>(data);
	cout << "Take Input Callback triggered" << endl;
	string input = iData->coordsInput->value();
	std::string outgoingMessage="PLACE:"+  input + "," + to_string(iData->ShipSize);
	messageHandler->setOutgoingMessage(outgoingMessage); 
	
}

void shipSelect_cb(Fl_Widget *widget, void *data)
{
	auto iData = static_cast<inputData *>(data);	
	iData->ShipSize = setSelectedShipSize(widget);
}
void fireInput_cb(Fl_Widget *widget, void *data)
{
	auto spd = static_cast<ShipPlacementData *>(data);
	cout << "Fire Input Callback triggered" << endl;
	
}

void createNameWindow_cb(Fl_Widget *widget, void *data)
{
	auto uiHandler = static_cast<UIHandler *>(data);
	LobbyWindow *lobbyWindow = new LobbyWindow(*uiHandler);
	lobbyWindow->show();
}
void getPlayerNames_cb(Fl_Widget *widget, void *data)
{
	
}

void continue_cb(Fl_Widget *widget, void *data)
{
	
}
void playTurn_cb(Fl_Widget *widget, void *data)
{

}
