#include "Name_Window.h"
#include "GameMaster.h"
#include "Callbacks.h"
#include <Fl/Fl_Window.H>
#include <Fl/Fl_Input.H>
#include <Fl/Fl_Button.H>
#include <string>
#include "PlayerNames.h"


NameWindow::NameWindow(GameMaster* gameMaster)
	: Fl_Window(200, 100, "PlayerNames"), pn(new PlayerNames())
{
	Fl_Input *nameInput = new Fl_Input(10, 10, 180, 30, "Player 1:");
	Fl_Button *submitBtn = new Fl_Button(10, 50, 180, 30, "Submit");
	pn->nameInput = nameInput;
	pn->gameMaster = gameMaster;
	submitBtn->box(FL_PLASTIC_UP_BOX);
	submitBtn->callback(getPlayerNames_cb, pn);
	

	end();
}