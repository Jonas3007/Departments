#pragma once 
#include "PlayerIntel.h"
#include "GameMaster.h"
#include "Player_Window.h"
#include "UIContext.h"
#include <Fl/Fl_Button.H>
#include <Fl/Fl_Input.H>
#include <Fl/Fl_Box.H>
#include <Fl/Fl_Output.H>	
#include "ShipPlacementData.h"




void takeInput_cb(Fl_Widget *widget, void *data);
void shipSelect_cb(Fl_Widget *widget, void *data);
void fireInput_cb(Fl_Widget *widget, void *data);
void createNameWindow_cb(Fl_Widget *widget, void *data);
void getPlayerNames_cb(Fl_Widget *widget, void *data);	
