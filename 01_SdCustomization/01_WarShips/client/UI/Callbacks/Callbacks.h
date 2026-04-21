#pragma once 
#include "GameMaster.h"
#include <Fl/Fl_Button.H>
#include <Fl/Fl_Input.H>
#include <Fl/Fl_Box.H>
#include <Fl/Fl_Output.H>	
#include "ShipPlacementData.h"
#include "ClientMessageHandler.h"
#include <memory>

static shared_ptr<ClientMessageHandler> messageHandler = nullptr;

void setClientMessageHandler(shared_ptr<ClientMessageHandler> handler);
void placeShip_cb(Fl_Widget *widget, void *data);
void shipSelect_cb(Fl_Widget *widget, void *data);
void fireInput_cb(Fl_Widget *widget, void *data);
void createNameWindow_cb(Fl_Widget *widget, void *data);
void getPlayerNames_cb(Fl_Widget *widget, void *data);	
void finishTurn_cb(Fl_Widget *widget, void *data);
void continue_cb(Fl_Widget *widget, void *data);
void playTurn_cb(Fl_Widget *widget, void *data);
