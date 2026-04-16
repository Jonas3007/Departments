#include "Name_Window.h"
#include "GameMaster.h"
#include "Callbacks.h"
#include <Fl/Fl_Window.H>
#include <Fl/Fl_Input.H>
#include <Fl/Fl_Button.H>
#include <string>



NameWindow::NameWindow()
	: Fl_Window(200, 100, "PlayerNames")
{
	Fl_Input *nameInput = new Fl_Input(10, 10, 180, 30);
	Fl_Button *submitBtn = new Fl_Button(10, 50, 180, 30, "Submit");

	submitBtn->box(FL_PLASTIC_UP_BOX);
	submitBtn->callback(getPlayerNames_cb, nullptr);
	

	end();
}