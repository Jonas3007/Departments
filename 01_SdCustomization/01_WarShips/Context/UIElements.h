#pragma once
#include <Fl/Fl_Button.H>
#include <Fl/Fl_Input.H>
#include <Fl/Fl_Box.H>
#include <vector>

struct UIElements
{
	vector<Fl_Box *> gridCells;
	Fl_Box *playerTurnBox;
};