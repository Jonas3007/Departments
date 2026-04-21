#include "Lobby_Window.h"
#include "UIHandler.h"
#include "Callbacks.h"
#include <Fl/Fl_Window.H>
#include <Fl/Fl_Input.H>
#include <Fl/Fl_Button.H>
#include <Fl/Fl_Output.H>
#include <Fl/Fl_Multiline_Output.H>
#include <string>



LobbyWindow::LobbyWindow(const UIHandler &uiHandler)
	: Fl_Window(230, 300, "Join Game")
{
	Fl_Input *nameInput = new Fl_Input(10, 10, 180, 30);
	Fl_Button *submitBtn = new Fl_Button(10, 50, 180, 30, "Submit");
	Fl_Output *nameOutput = new Fl_Output(10, 10, 180, 30);
	
	Fl_Button *joinGame_btn = new Fl_Button(10, 85, 90, 30, "Join Game");
	Fl_Button *hostGame_btn = new Fl_Button(105, 85, 85, 30, "Host Game" );
	Fl_Input *lobbyInput = new Fl_Input(105,85, 85, 30);
	Fl_Button *check_btn = new Fl_Button (195, 85, 30, 30, "@->" );
	
	Fl_Output *lobbyOutput = new Fl_Output (60, 115, 130, 30, "Lobby:");
	Fl_Multiline_Output *infoOutput = new Fl_Multiline_Output (10, 150, 180, 90);
	
	//Callbacks
	submitBtn->callback(getPlayerNames_cb, nullptr);
	
	//Styles
	submitBtn->box(FL_PLASTIC_UP_BOX);
	joinGame_btn->box(FL_PLASTIC_UP_BOX);
	hostGame_btn->box(FL_PLASTIC_UP_BOX);
	check_btn->box(FL_PLASTIC_UP_BOX);
	
	

	end();
}