#pragma once 
#include "PlayerIntel.h"
#include "GameMaster.h"
#include "Player_Window.h"
#include "UIContext.h"
#include <Fl/Fl_Button.H>
#include <Fl/Fl_Input.H>
#include <Fl/Fl_Box.H>
#include <Fl/Fl_Output.H>	

struct CallbackData
{
	UIContext *UIctx;
	PlayerIntel *player1Intel;
	PlayerIntel *player2Intel;
	GameMaster *gameMaster;
	Fl_Input *coordsInput;
	Fl_Button *takeInput_btn;
};

struct GridCellData
{
	vector<Fl_Box*> gridCells;
};
struct ShipPlacementData
{
	int selectedShipSize;
	Fl_Output *selectedShipOutput;
	Fl_Input *coordsInput;
	GameMaster *gameMaster;
};
void takeInput_cb(Fl_Widget *widget, void *data);
void shipSelect_cb(Fl_Widget *widget, void *data);
void fireInput_cb(Fl_Widget *widget, void *data);
void reColorGridCell(GridCellData gridData,string cellPos, Fl_Color color);
void testforPlaceShipInput(Fl_Widget *widget, void *data);	
