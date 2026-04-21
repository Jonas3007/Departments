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
	if (currentGameState.playerIndex == 1 && currentGameState.currentPhase == GamePhase::Player1Turn || currentGameState.currentPhase == GamePhase::PlaceShipsP1)
	{
		playerTurnBox->label(currentGameState.playerName.c_str());
	}
	else if (currentGameState.playerIndex == 2 && currentGameState.currentPhase == GamePhase::Player2Turn || currentGameState.currentPhase == GamePhase::PlaceShipsP2)
	{
		playerTurnBox->label(currentGameState.playerName.c_str());
	}
	else
	{
		playerTurnBox->label(currentGameState.opponentName.c_str());
	}
}
void UIHandler::updatePhaseBox()
{
	string phaseName;
	switch (currentGameState.currentPhase)
	{
	case GamePhase::PlaceShipsP1:
		phaseName = "Place Ships - Player 1";
		phaseBox->label(phaseName.c_str());
		break;
	case GamePhase::PlaceShipsP2:
		phaseName = "Place Ships - Player 2";
		phaseBox->label(phaseName.c_str());
		break;
	case GamePhase::Player1Turn:
		phaseName = "Player 1's Turn";
		phaseBox->label(phaseName.c_str());
		break;
	case GamePhase::Player2Turn:
		phaseName = "Player 2's Turn";
		phaseBox->label(phaseName.c_str());
		break;
	case GamePhase::GameOver:
		phaseName = "Game Over";
		phaseBox->label(phaseName.c_str());
		break;
	case GamePhase::PickNamePhase:
		phaseName = "Pick Name Phase";
		phaseBox->label(phaseName.c_str());
		break;
	default:
		phaseName = "Unknown Phase";
		phaseBox->label(phaseName.c_str());
		break;
	}
}
void UIHandler::updatePlayerGrid()
{
	Fl_Color color;
	vector<Coordinates> shipCoords = currentGameState.shipsPlaced;
	for (Coordinates coord : shipCoords)
	{
		color = FL_BLACK;
		string cellPos = coordsToCellPos(coord);
		reColorPlayerShipGridCell(cellPos, color);
	}

	// Show hits received
	vector<Coordinates> hitsReceived = currentGameState.playerHitsreceived;
	for (Coordinates hit : hitsReceived)
	{
		color = FL_RED;
		string cellPos = coordsToCellPos(hit);
		reColorPlayerShipGridCell(cellPos, color);
	}
	// show hits on opponent
	vector<Coordinates> hits = currentGameState.playerHits;
	for (Coordinates hit : hits)
	{
		color = FL_GREEN;
		string cellPos = coordsToCellPos(hit);
		reColorGridCell(cellPos, color);
	}
	// show misses on opponent
	vector<Coordinates> misses = currentGameState.playerMisses;
	for (Coordinates miss : misses)
	{
		color = FL_WHITE;
		string cellPos = coordsToCellPos(miss);
		reColorGridCell(cellPos, color);
	}
}

void UIHandler::updateShipSizeOutput()
{
	string outputText;
	for (ShipConfig config : currentGameState.playerShipsToPlace)
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

