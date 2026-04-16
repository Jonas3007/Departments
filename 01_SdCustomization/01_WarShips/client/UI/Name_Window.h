#pragma once
#include <Fl/Fl_Window.H>
#include <Fl/Fl_Input.H>
#include <Fl/Fl_Button.H>
#include "GameMaster.h"	

class NameWindow : public Fl_Window
{
public:
	NameWindow();

private:
	Fl_Input* nameInput;
};
