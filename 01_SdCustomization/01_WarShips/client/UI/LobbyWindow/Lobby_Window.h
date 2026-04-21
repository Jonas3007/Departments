#pragma once
#include <Fl/Fl_Window.H>
#include <Fl/Fl_Input.H>
#include <Fl/Fl_Button.H>
#include "UIHandler.h"
class UIHandler;
class LobbyWindow : public Fl_Window
{
public:
	LobbyWindow(const UIHandler &uiHandler);

private:
	Fl_Input* nameInput;
};
