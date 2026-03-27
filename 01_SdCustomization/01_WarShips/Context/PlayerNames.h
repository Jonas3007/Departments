#pragma once
#include <string>
#include <Fl/Fl_Input.H>
#include "GameMaster.h"

class GameMaster;	

struct PlayerNames
{
	Fl_Input *nameInput;
	string Player1Name;
	string Player2Name;
	GameMaster *gameMaster;	
};