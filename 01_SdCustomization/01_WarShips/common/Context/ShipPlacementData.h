#pragma once 
#include "GameMaster.h"	
#include <Fl/Fl_Input.H>
#include <Fl/Fl_Output.H>

struct ShipPlacementData
{
	int selectedShipSize;
	Fl_Output *selectedShipOutput;
	Fl_Input *coordsInput;
	GameMaster *gameMaster;
};