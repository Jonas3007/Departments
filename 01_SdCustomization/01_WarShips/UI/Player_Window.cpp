#include "Player_Window.h"
#include "Coordinates.h"
#include "UIContext.h"
#include "PlayerIntel.h"
#include <iostream>

#include <Fl/Fl_Window.H>
#include <Fl/Fl_Button.H>
#include <Fl/Fl_Box.H>
#include <Fl/Fl_Input.H>
#include <Fl/Fl_Group.H>
#include <Fl/Fl_Output.H>
using namespace std;	


void createOceanGrid(Fl_Group* group, int gridSize, int cellSize)
{
	
}



Fl_Window* CreatePlayerWindow()
{
	Fl_Window* window = new Fl_Window(1000,1000);
	
	Fl_Box* title = new Fl_Box(-25,-1,1050,50, "WarShips");
	title->labelfont(FL_BOLD+FL_ITALIC);
	title->labelsize(24);
	title->box(FL_BORDER_BOX);
	
	Fl_Input* CoordsInput = new Fl_Input(500,450, 100,30, "Enter Coordinates:");
	CoordsInput->box(FL_BORDER_BOX);
	
	Fl_Button* fireButton = new Fl_Button(610,450, 80,30, "Fire!");
	fireButton->box(FL_BORDER_BOX);
	fireButton->callback(shotFiredCallback);
	
	
	
	Fl_Group* oceanGrid = new Fl_Group(50, 200, 450, 450);
	oceanGrid->end();
	return window;
}