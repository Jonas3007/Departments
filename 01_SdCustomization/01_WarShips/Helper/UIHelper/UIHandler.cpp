#include "UIHandler.h"
#include "GameMaster.h"
#include "ShipPlacementData.h"
#include "Fl/Fl_Box.H"	
#include "Fl/Fl.H"
#include <vector>
#include "Ship.h"


//---------------------
//Helper
//---------------------
string coordsToCellPos(Coordinates coords)
{
	return coords.Letter + to_string(coords.Number);
}
//---------------------
//Setter for UI elements
//---------------------
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
void UIHandler::setGridCells(Fl_Box *cell)
{
		gridCells.push_back(cell);
}
void UIHandler::setShipPlacementElements(Fl_Button *battleshipBtn, Fl_Button *cruiserBtn, Fl_Button *destroyerBtn, Fl_Button *submarineBtn, Fl_Output *selectedShipOutput, Fl_Input *coordsInput, Fl_Multiline_Output *shipSizeOutput)
{	this->battleshipBtn = battleshipBtn;
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

void UIHandler::reColorGridCell( string cellPos, Fl_Color color)
{ 
	
	for (Fl_Box* cell : gridCells)
	{
		if (cell->label() == cellPos)
		{
			cell->color(color);
			cell->redraw();
			break;
		}
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

void UIHandler::updatePlayer1Grid(GameMaster *gameMaster)
{
	Fl_Color color;
	UIContext uiContext = gameMaster->UIctx;
	vector<Ship> P1Inventory = uiContext.Player1Intel.ShipsInventory;
	//Show ships in grid
	for(Ship ship : P1Inventory)
	{
		for(Coordinates coord : ship.GridLocation)
		{
			color = FL_BLACK;
			string cellPos = coordsToCellPos(coord);
			reColorGridCell(cellPos, color);
		}
	}
	//Show hits received
	vector<Coordinates> hitsReceived = uiContext.Player1Intel.hitsReceived;
	for(Coordinates hit : hitsReceived)
	{
		color = FL_RED;
		string cellPos = coordsToCellPos(hit);
		reColorGridCell(cellPos, color);
	}
	//show hits on opponent
	vector<Coordinates> hits = uiContext.Player1Intel.hits;
	for(Coordinates hit : hits)
	{
		color = FL_GREEN;
		string cellPos = coordsToCellPos(hit);
		reColorGridCell(cellPos, color);
	}
	

}
void UIHandler::updatePlayer2Grid(GameMaster *gameMaster)
{
	UIContext uiContext = gameMaster->UIctx;
	vector<Ship> P2Inventory = uiContext.Player2Intel.ShipsInventory;
	//Show ships in grid
	for(Ship ship : P2Inventory)
	{
		for(Coordinates coord : ship.GridLocation)
		{
			Fl_Color color = FL_BLACK;
			string cellPos = coordsToCellPos(coord);
			reColorGridCell(cellPos, color);
		}
	}
	//Show hits received
	vector<Coordinates> hitsReceived = uiContext.Player2Intel.hitsReceived;
	for(Coordinates hit : hitsReceived)
	{
		Fl_Color color = FL_RED;
		string cellPos = coordsToCellPos(hit);
		reColorGridCell(cellPos, color);
	}
	//show hits on opponent
	vector<Coordinates> hits = uiContext.Player2Intel.hits;
	for(Coordinates hit : hits)
	{
		Fl_Color color = FL_GREEN;
		string cellPos = coordsToCellPos(hit);
		reColorGridCell(cellPos, color);
	}
}

void UIHandler::updatePlayerWindows(GameMaster *gameMaster)
{
	//Update Player Turn Box
	updatePlayerTurnBox(gameMaster);
	
	//Place Ships in Grid
	if(gameMaster->CurrentPhase == PlaceShipsP1 || gameMaster->CurrentPhase == Player1Turn)
	{
		updatePlayer1Grid(gameMaster);
	}
	else if (gameMaster->CurrentPhase == PlaceShipsP2 || gameMaster->CurrentPhase == Player2Turn)
	{
		updatePlayer2Grid(gameMaster);
	}
	
}

void UIHandler::updateShipSizeOutput(GameMaster *gameMaster)
{
	Player activePlayer = gameMaster->ActivePlayer;
	string outputText ;
	for(ShipConfig config : activePlayer.ShipsToPlace)
	{
		switch(config.ShipSize)
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
void UIHandler::toggleShipPlacementElements(GameMaster *gameMaster)
{
	bool visible = gameMaster->CurrentPhase == PlaceShipsP1 || gameMaster->CurrentPhase == PlaceShipsP2;
	if (visible)
	{
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
		battleshipBtn->hide();
		cruiserBtn->hide();
		destroyerBtn->hide();
		submarineBtn->hide();
		selectedShipOutput->hide();
		coordsInput->hide();
		shipSizeOutput->hide();
		
	}
}