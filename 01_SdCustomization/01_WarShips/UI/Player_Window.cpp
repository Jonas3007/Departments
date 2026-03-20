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
#include <string>
using namespace std;	


void createOceanGrid(Fl_Group* group, int gridSize, int cellSize)
{
	if (!group) {
		return;
	}

	const int leftAxisWidth = 30;
	const int bottomAxisHeight = 30;
	const int gridPixelSize = gridSize * cellSize;

	const int gridStartX = group->x() + leftAxisWidth;
	const int gridStartY = group->y();

	for (int row = 0; row < gridSize; ++row) {
		char rowLabel = static_cast<char>('A' + row);

		for (int col = 1; col <= gridSize; ++col) {
			int x = gridStartX + (col - 1) * cellSize;
			int y = gridStartY + (gridSize - 1 - row) * cellSize;

			string cellLabel = string(1, rowLabel) + to_string(col);
			Fl_Box* cell = new Fl_Box(x, y, cellSize, cellSize);
			cell->copy_label(cellLabel.c_str());
			cell->box(FL_BORDER_BOX);
			cell->color(FL_CYAN);
			cell->labelsize(12);
			cell->labelfont(FL_BOLD);
			cell->align(FL_ALIGN_CENTER);
		}

		int axisY = gridStartY + (gridSize - 1 - row) * cellSize;
		string yLabel = string(1, rowLabel);
		Fl_Box* yAxisLabel = new Fl_Box(group->x(), axisY, leftAxisWidth, cellSize);
		yAxisLabel->copy_label(yLabel.c_str());
		yAxisLabel->box(FL_NO_BOX);
		yAxisLabel->labelsize(14);
		yAxisLabel->labelfont(FL_BOLD);
		yAxisLabel->align(FL_ALIGN_CENTER);
	}

	for (int col = 1; col <= gridSize; ++col) {
		int axisX = gridStartX + (col - 1) * cellSize;
		string xLabel = to_string(col);
		Fl_Box* xAxisLabel = new Fl_Box(axisX, gridStartY + gridPixelSize, cellSize, bottomAxisHeight);
		xAxisLabel->copy_label(xLabel.c_str());
		xAxisLabel->box(FL_NO_BOX);
		xAxisLabel->labelsize(14);
		xAxisLabel->labelfont(FL_BOLD);
		xAxisLabel->align(FL_ALIGN_CENTER);
	}

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
	// fireButton->callback(shotFiredCallback);
	
	
	
	Fl_Group* oceanGrid = new Fl_Group(50, 200, 450, 450);
	oceanGrid->begin();
	createOceanGrid(oceanGrid, 10, 35);
	oceanGrid->end();
	return window;
}