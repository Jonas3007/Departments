#include "UIHandler.h"
#include "GameMaster.h"
#include "ShipPlacementData.h"
#include "Fl/Fl_Box.H"
#include "Fl/Fl.H"
#include <vector>
#include "Ship.h"

//---------------------
// Helper
//---------------------
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
void UIHandler::updatePlayerTurnBox(GameMaster *gameMaster)
{
	string playerName = gameMaster->ActivePlayer.Name;
	gameMaster->uiHandler->playerTurnBox->copy_label(("Player: " + playerName).c_str());
	gameMaster->uiHandler->playerTurnBox->redraw();
}
void UIHandler::updatePhaseBox(GameMaster *gameMaster)
{
	string phaseName;
	switch (gameMaster->CurrentPhase)
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
	gameMaster->uiHandler->phaseBox->copy_label(("Phase: " + phaseName).c_str());
	gameMaster->uiHandler->phaseBox->redraw();
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

void UIHandler::updatePlayer1Grid(GameMaster *gameMaster)
{
	Fl_Color color;
	vector<Ship> P1Inventory = gameMaster->Player1.ShipInventory;
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
	vector<Coordinates> hitsReceived = gameMaster->Player1.hitsReceived;
	for (Coordinates hit : hitsReceived)
	{
		color = FL_RED;
		string cellPos = coordsToCellPos(hit);
		reColorPlayerShipGridCell(cellPos, color);
	}
	// show hits on opponent
	vector<Coordinates> hits = gameMaster->Player1.hits;
	for (Coordinates hit : hits)
	{
		color = FL_GREEN;
		string cellPos = coordsToCellPos(hit);
		reColorGridCell(cellPos, color);
	}
	// show misses on opponent
	vector<Coordinates> misses = gameMaster->Player1.misses;
	for (Coordinates miss : misses)
	{
		color = FL_WHITE;
		string cellPos = coordsToCellPos(miss);
		reColorGridCell(cellPos, color);
	}
}
void UIHandler::updatePlayer2Grid(GameMaster *gameMaster)
{

	vector<Ship> P2Inventory = gameMaster->Player2.ShipInventory;
	// Show ships in grid
	for (Ship ship : P2Inventory)
	{
		for (Coordinates coord : ship.GridLocation)
		{
			Fl_Color color = FL_BLACK;
			string cellPos = coordsToCellPos(coord);
			reColorPlayerShipGridCell(cellPos, color);
		}
	}
	// Show hits received
	vector<Coordinates> hitsReceived = gameMaster->Player2.hitsReceived;
	for (Coordinates hit : hitsReceived)
	{
		Fl_Color color = FL_RED;
		string cellPos = coordsToCellPos(hit);
		reColorPlayerShipGridCell(cellPos, color);
	}
	// show hits on opponent
	vector<Coordinates> hits = gameMaster->Player2.hits;
	for (Coordinates hit : hits)
	{
		Fl_Color color = FL_GREEN;
		string cellPos = coordsToCellPos(hit);
		reColorGridCell(cellPos, color);
	}
	// show misses on opponent
	vector<Coordinates> misses = gameMaster->Player2.misses;
	for (Coordinates miss : misses)
	{
		Fl_Color color = FL_WHITE;
		string cellPos = coordsToCellPos(miss);
		reColorGridCell(cellPos, color);
	}
}

void UIHandler::updatePlayerWindows(GameMaster *gameMaster)
{
	// Update Player Turn Box

	// Place Ships in Grid
	if (gameMaster->CurrentPhase == PlaceShipsP1 || gameMaster->CurrentPhase == Player1Turn)
	{
		resetGridColors();
		updatePlayer1Grid(gameMaster);
		updatePlayerTurnBox(gameMaster);
		updatePhaseBox(gameMaster);
		updateShipSizeOutput(gameMaster);
	}
	else if (gameMaster->CurrentPhase == PlaceShipsP2 || gameMaster->CurrentPhase == Player2Turn)
	{
		resetGridColors();
		updatePlayer2Grid(gameMaster);
		updatePlayerTurnBox(gameMaster);
		updatePhaseBox(gameMaster);
		updateShipSizeOutput(gameMaster);
	}
}

void UIHandler::updateShipSizeOutput(GameMaster *gameMaster)
{
	Player activePlayer = gameMaster->ActivePlayer;
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
void UIHandler::toggleShipPlacementElements(GameMaster *gameMaster)
{
	bool visible = gameMaster->CurrentPhase == PlaceShipsP1 || gameMaster->CurrentPhase == PlaceShipsP2;
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
void UIHandler::toggleFinishTurnBtn(GameMaster *gameMaster)
{
	bool visible = gameMaster->CurrentPhase == Player1Turn || gameMaster->CurrentPhase == Player2Turn 
	|| gameMaster->CurrentPhase == PlaceShipsP1 || gameMaster->CurrentPhase == PlaceShipsP2;
	if (visible)
	{
		finishTurnBtn->show();
	}
	else
	{
		finishTurnBtn->hide();
	}
	if (gameMaster->firedThisTurn == true)
	{
		finishTurnBtn->activate();
	}
	else
	{
		finishTurnBtn->deactivate();
	}
}
void UIHandler::toggleEnterNamesBtn(GameMaster *gameMaster)
{
	if (!gameMaster->Player1.Name.empty() && !gameMaster->Player2.Name.empty())
	{
		enterNamesBtn->hide();
	}
	else
	{
		enterNamesBtn->show();
	}
}
void UIHandler::toggleFireBtn(GameMaster *gameMaster)
{
	if (!gameMaster->CurrentPhase == PickNamePhase)
	{
		firebtn->show();
	}
	else
	{
		firebtn->hide();
	}
	if (gameMaster->firedThisTurn == true)
	{
		firebtn->deactivate();
	}
	else
	{
		firebtn->activate();
	}
}

void UIHandler::toggleTransitionScreen(GameMaster *gameMaster, bool showUI)
{

	if (showUI)
	{
		playTur_btn->show();
		PlayerShipGrid->hide();
		oceanGrid->hide();
		toggleFireBtn(gameMaster);
	}
	else
	{
		playTur_btn->hide();
		PlayerShipGrid->show();
		oceanGrid->show();	
		toggleFireBtn(gameMaster);
	}
	
}