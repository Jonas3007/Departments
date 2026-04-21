#include "Player_Window.h"
#include "Coordinates.h"
#include <iostream>
#include "Callbacks.h"
#include "Name_Window.h"
#include "GameOver_Window.h"
#include "GameMaster.h"
#include "ShipPlacementData.h"
#include "UIHandler.h"
#include "inputData.h"	

#include <Fl/Fl_Window.H>
#include <Fl/Fl_Button.H>
#include <Fl/Fl_Box.H>
#include <Fl/Fl_Input.H>
#include <Fl/Fl_Group.H>
#include <Fl/Fl_Output.H>
#include <Fl/Fl_Multiline_Output.H>
#include <string>

void createOceanGrid(Fl_Group *group, int gridSize, int cellSize, ShipPlacementData *spd)
{
	if (!group)
	{
		return;
	}
	bool isShipGrid;
	if (group->label() == "PlayerShipGrid")
	{
		isShipGrid = false;
	}
	else
	{
		isShipGrid = true;
	}

	const int leftAxisWidth = 30;
	const int topAxisHeight = 30;
	const int gridPixelSize = gridSize * cellSize;

	const int gridStartX = group->x() + leftAxisWidth;
	const int gridStartY = group->y() + topAxisHeight;

	for (int row = 0; row < gridSize; ++row)
	{
		int rowLabel = row + 1;

		for (int col = 0; col < gridSize; ++col)
		{
			int x = gridStartX + col * cellSize;
			int y = gridStartY + row * cellSize;

			// Zell-Label erzeugen (A1, B1, ... A2, B2, ...)
			char colChar = 'A' + col;
			std::string cellLabel = std::string(1, colChar) + std::to_string(rowLabel);

			Fl_Box *cell = new Fl_Box(x, y, cellSize, cellSize);
			cell->box(FL_BORDER_BOX);
			cell->color(FL_BLUE);

			// Label setzen, aber unsichtbar machen
			cell->copy_label(cellLabel.c_str());
			cell->labeltype(FL_NO_LABEL);

		}

		int axisY = gridStartY + row * cellSize;
		string yLabel = to_string(rowLabel);
		Fl_Box *yAxisLabel = new Fl_Box(group->x(), axisY, leftAxisWidth, cellSize);
		yAxisLabel->copy_label(yLabel.c_str());
		yAxisLabel->box(FL_NO_BOX);
		yAxisLabel->labelsize(14);
		yAxisLabel->labelfont(FL_BOLD);
		yAxisLabel->align(FL_ALIGN_CENTER);
	}

	for (int col = 0; col < gridSize; ++col)
	{
		int axisX = gridStartX + col * cellSize;
		char xLabelChar = static_cast<char>('A' + col);
		string xLabel(1, xLabelChar);
		Fl_Box *xAxisLabel = new Fl_Box(axisX, group->y(), cellSize, topAxisHeight);
		xAxisLabel->copy_label(xLabel.c_str());
		xAxisLabel->box(FL_NO_BOX);
		xAxisLabel->labelsize(14);
		xAxisLabel->labelfont(FL_BOLD);
		xAxisLabel->align(FL_ALIGN_CENTER);
	}
}

void shipPlacementElements(Fl_Input *coordsInput, inputData *iData)
{

	// Output to Display Selected Ship
	Fl_Output *selectedShipOutput = new Fl_Output(325, 600, 130, 40, "Selected Ship:");
	selectedShipOutput->box(FL_PLASTIC_UP_BOX);
	// Output for ship size and the amount of ships of this size left to place
	Fl_Multiline_Output *shipSizeOutput = new Fl_Multiline_Output(325, 650, 130, 90);
	shipSizeOutput->box(FL_PLASTIC_UP_BOX);


	Fl_Button *placeShip_btn = new Fl_Button(730, 600, 90, 40, "Place Ship");
	placeShip_btn->box(FL_PLASTIC_UP_BOX);
	placeShip_btn->callback(takeInput_cb, iData);
	// Buttons for selecting ships to place
	Fl_Button *ship5_btn = new Fl_Button(600, 650, 90, 40, "Battleship");
	Fl_Button *ship4_btn = new Fl_Button(700, 650, 90, 40, "Cruiser");
	Fl_Button *ship3_btn = new Fl_Button(600, 700, 90, 40, "Destroyer");
	Fl_Button *ship2_btn = new Fl_Button(700, 700, 90, 40, "Submarine");
	// Button Style
	ship5_btn->box(FL_PLASTIC_UP_BOX);
	ship4_btn->box(FL_PLASTIC_UP_BOX);
	ship3_btn->box(FL_PLASTIC_UP_BOX);
	ship2_btn->box(FL_PLASTIC_UP_BOX);
	// Callbacks for ship selection
	ship5_btn->callback(shipSelect_cb, iData);
	ship4_btn->callback(shipSelect_cb, iData);
	ship3_btn->callback(shipSelect_cb, iData);
	ship2_btn->callback(shipSelect_cb, iData);

}

Fl_Window *CreatePlayerWindow()
{
	// Initialize DataStructs
	inputData iData;

	// Create Main Window
	Fl_Window *window = new Fl_Window(1050, 850);

	// Title Box
	Fl_Box *title = new Fl_Box(0, 0, 1050, 50, "WarShips");
	title->labelfont(FL_BOLD + FL_ITALIC);
	title->align(FL_ALIGN_CENTER);
	title->labelsize(24);

	// Player Turn Box
	Fl_Box *playerTurnBox = new Fl_Box(400, 80, 250, 40);
	playerTurnBox->labelfont(FL_BOLD);
	playerTurnBox->labelsize(16);
	playerTurnBox->copy_label("Player: ");
	playerTurnBox->align(FL_ALIGN_CENTER);
	

	// Phase Box
	Fl_Box *phaseBox = new Fl_Box(400, 140, 250, 40);
	phaseBox->labelfont(FL_BOLD);
	phaseBox->labelsize(16);
	phaseBox->copy_label("Phase: ");
	phaseBox->align(FL_ALIGN_CENTER);

	// Enter names Button
	Fl_Button *enterNamesBtn = new Fl_Button(80, 80, 150, 40, "Enter Player Names");
	enterNamesBtn->box(FL_PLASTIC_UP_BOX);
	enterNamesBtn->callback(createNameWindow_cb, nullptr);


	// Finish Turn Button
	Fl_Button *finishTurnBtn = new Fl_Button(825, 600, 120, 40, "Finish Turn");
	finishTurnBtn->box(FL_PLASTIC_UP_BOX);
	finishTurnBtn->callback(finishTurn_cb, nullptr);

	finishTurnBtn->hide();

	// Input for Coordinates and Button to confirm input
	Fl_Input *coordsInput = new Fl_Input(600, 600, 120, 40, "Coordinates:");
	Fl_Button *takeInput_btn = new Fl_Button(730, 600, 90, 40, "Fire!");

	iData.coordsInput = coordsInput;

	// Styling Input and Button
	coordsInput->box(FL_PLASTIC_UP_BOX);
	takeInput_btn->box(FL_PLASTIC_UP_BOX);
	// Callbacks for Input and Button
	takeInput_btn->callback(fireInput_cb, nullptr);
	// Buttons and ui elements for ship placement
	shipPlacementElements(coordsInput, &iData);

	// ocean grid creation
	Fl_Group *oceanGrid = new Fl_Group(75, 200, 450, 450);
	oceanGrid->begin();
	createOceanGrid(oceanGrid, 10, 35, nullptr);
	oceanGrid->end();

	Fl_Group *shipGrid = new Fl_Group(575, 200, 450, 450);
	shipGrid->begin();
	createOceanGrid(shipGrid, 10, 35, nullptr);
	shipGrid->end();
	
	
	//Playturn button that toggles the transition screen for the next player
	Fl_Button *playTurn_btn = new Fl_Button(450, 350, 150, 50, "Play Turn");
	playTurn_btn->box(FL_PLASTIC_UP_BOX);
	playTurn_btn->callback(playTurn_cb, nullptr);

	playTurn_btn->hide();
	

	window->end();
	window->show();

	return window;
}