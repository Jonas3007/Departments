#pragma once
#include <Fl/Fl_Window.H>
#include <Fl/Fl_Input.H>
#include <Fl/Fl_Button.H>
#include "GameMaster.h"	
#include "PlayerNames.h"

class NameWindow : public Fl_Window
{
public:
	NameWindow(GameMaster *gameMaster);

private:
	Fl_Input* nameInput;
};
