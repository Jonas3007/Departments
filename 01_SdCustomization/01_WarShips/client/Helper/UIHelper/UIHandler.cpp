#include "UIHandler.h"
#include "GameMaster.h"
#include "ShipPlacementData.h"
#include "Fl/Fl_Box.H"
#include "Fl/Fl.H"
#include <vector>
#include "Ship.h"
void updateUIAccordingToGameState()
{
	
}
//---------------------
// Helper
//---------------------
void UIHandler::onGameStateUpdate(const GameStateDTO &newState)
{
	this->currentGameState = newState;
	void updateUIAccordingToGameState();
	
}
string coordsToCellPos(Coordinates coords)
{
	return coords.Letter + to_string(coords.Number);
}
//---------------------
// Setter for UI elements
//---------------------
void UIHandler::setPlayTurnBtn(Fl_Button *btn)
{
	this->playTur_btn = btn;
}	
void UIHandler::setGridGroups(Fl_Group *playerShipGrid, Fl_Group *oceanGrid)
{
	this->PlayerShipGrid = playerShipGrid;
	this->oceanGrid = oceanGrid;
}
void UIHandler::setNameInput(Fl_Input *input)
{
	nameInput = input;
}
void UIHandler::setPlayerTurnBox(Fl_Box *box)
{
	playerTurnBox = box;
}
void UIHandler::setPhaseBox(Fl_Box *box)
{
	phaseBox = box;
}
void UIHandler::setPlayerShipGridCells(Fl_Box *cell)
{
	PlayerShipGridCells.push_back(cell);
}
void UIHandler::setGridCells(Fl_Box *cell)
{
	gridCells.push_back(cell);
}
void UIHandler::setShipPlacementElements(Fl_Button *placeShipbtn, Fl_Button *battleshipBtn, Fl_Button *cruiserBtn, Fl_Button *destroyerBtn, Fl_Button *submarineBtn, Fl_Output *selectedShipOutput, Fl_Input *coordsInput, Fl_Multiline_Output *shipSizeOutput)
{
	this->placeShipBtn = placeShipbtn;
	this->battleshipBtn = battleshipBtn;
	this->cruiserBtn = cruiserBtn;
	this->destroyerBtn = destroyerBtn;
	this->submarineBtn = submarineBtn;
	this->selectedShipOutput = selectedShipOutput;
	this->coordsInput = coordsInput;
	this->shipSizeOutput = shipSizeOutput;
}
void UIHandler::setNameWindow(NameWindow *window)
{
	this->nameWindow = window;
}
string UIHandler::getPlayerName()
{
	return nameInput->value();
}

//---------------------
// Update UI
//---------------------
void UIHandler::resetPlayerInputs()
{
	coordsInput->value("");
	selectedShipOutput->value("");
}
void UIHandler::reColorGridCell(string cellPos, Fl_Color color)
{

	for (Fl_Box *cell : gridCells)
	{
		if (cell->label() == cellPos)
		{
			cell->color(color);
			cell->redraw();
			break;
		}
	}
}
void UIHandler::reColorPlayerShipGridCell(string cellPos, Fl_Color color)
{
	for (Fl_Box *cell : PlayerShipGridCells)
	{
		if (cell->label() == cellPos)
		{
			cell->color(color);
			cell->redraw();
			break;
		}
	}
}
void UIHandler::resetGridColors()
{
	for (Fl_Box *cell : gridCells)
	{
		cell->color(FL_BLUE);
		cell->redraw();
	}

	for (Fl_Box *cell : PlayerShipGridCells)
	{
		cell->color(FL_BLUE);
		cell->redraw();
	}
}
void UIHandler::updatePlayerTurnBox()
{

}
void UIHandler::updatePhaseBox()
{
	string phaseName;
	switch (currentGameState.currentPhase)
	{
	case GamePhase::PlaceShipsP1:
		phaseName = "Place Ships - Player 1";
		break;
	case GamePhase::PlaceShipsP2:
		phaseName = "Place Ships - Player 2";
		break;
	case GamePhase::Player1Turn:
		phaseName = "Player 1's Turn";
		break;
	case GamePhase::Player2Turn:
		phaseName = "Player 2's Turn";
		break;
	case GamePhase::GameOver:
		phaseName = "Game Over";
		break;
	case GamePhase::PickNamePhase:
		phaseName = "Pick Name Phase";
		break;
	default:
		phaseName = "Unknown Phase";
		break;
	}
}
void UIHandler::setFinishTurnBtn(Fl_Button *btn)
{
	this->finishTurnBtn = btn;
}
void UIHandler::setEnterNamesBtn(Fl_Button *btn)
{
	this->enterNamesBtn = btn;
}
void UIHandler::setFireBtn(Fl_Button *btn)
{
	this->firebtn = btn;
}

void UIHandler::updatePlayerGrid()
{
	Fl_Color color;
	vector<Ship> P1Inventory;
	// Show ships in grid
	for (Ship ship : P1Inventory)
	{
		for (Coordinates coord : ship.GridLocation)
		{
			color = FL_BLACK;
			string cellPos = coordsToCellPos(coord);
			reColorPlayerShipGridCell(cellPos, color);
		}
	}
	// Show hits received
	vector<Coordinates> hitsReceived = currentGameState.player1Hitsreceived;
	for (Coordinates hit : hitsReceived)
	{
		color = FL_RED;
		string cellPos = coordsToCellPos(hit);
		reColorPlayerShipGridCell(cellPos, color);
	}
	// show hits on opponent
	vector<Coordinates> hits = currentGameState.player1Hits;
	for (Coordinates hit : hits)
	{
		color = FL_GREEN;
		string cellPos = coordsToCellPos(hit);
		reColorGridCell(cellPos, color);
	}
	// show misses on opponent
	vector<Coordinates> misses = currentGameState.player1Misses;	
	for (Coordinates miss : misses)
	{
		color = FL_WHITE;
		string cellPos = coordsToCellPos(miss);
		reColorGridCell(cellPos, color);
	}
}

void UIHandler::updateShipSizeOutput()
{
	Player activePlayer;
	string outputText;
	for (ShipConfig config : activePlayer.ShipsToPlace)
	{
		switch (config.ShipSize)
		{
		case 5:
			outputText += "Battleship (5): " + to_string(config.Count) + "\n";
			break;
		case 4:
			outputText += "Cruiser (4): " + to_string(config.Count) + "\n";
			break;
		case 3:
			outputText += "Destroyer (3): " + to_string(config.Count) + "\n";
			break;
		case 2:
			outputText += "Submarine (2): " + to_string(config.Count);
			break;
		}
		shipSizeOutput->value(outputText.c_str());
	}
}
//------------------------
// Toggleable UI Elements
//------------------------
void UIHandler::toggleShipPlacementElements()
{
	bool visible;
	if (visible)
	{
		placeShipBtn->show();
		battleshipBtn->show();
		cruiserBtn->show();
		destroyerBtn->show();
		submarineBtn->show();
		selectedShipOutput->show();
		coordsInput->show();
		shipSizeOutput->show();
	}
	else
	{
		placeShipBtn->hide();
		battleshipBtn->hide();
		cruiserBtn->hide();
		destroyerBtn->hide();
		submarineBtn->hide();
		selectedShipOutput->hide();
		shipSizeOutput->hide();
	}
}
void UIHandler::toggleFinishTurnBtn()
{
	
}
void UIHandler::toggleEnterNamesBtn()
{
	
}
void UIHandler::toggleFireBtn()
{
	
}

