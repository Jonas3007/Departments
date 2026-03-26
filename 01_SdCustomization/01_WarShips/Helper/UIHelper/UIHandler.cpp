#include "UIHandler.h"
#include "GameMaster.h"
#include "UIElements.h"
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
// Update UI
//---------------------

void reColorGridCell(UIElements uiData, string cellPos, Fl_Color color)
{ 
	
	for (Fl_Box* cell : uiData.gridCells)
	{
		if (cell->label() == cellPos)
		{
			cell->color(color);
			cell->redraw();
			break;
		}
	}
}
void updatePlayerTurnBox(UIElements uiData, ShipPlacementData *spd)
{
	string playerName = spd->gameMaster->ActivePlayer.Name;
	uiData.playerTurnBox->copy_label(("Current Player: " + playerName).c_str());
	uiData.playerTurnBox->redraw();
}

void updatePlayer1Grid(UIElements uiData, ShipPlacementData *spd)
{
	UIContext uiContext = spd->gameMaster->UIctx;
	vector<Ship> P1Inventory = uiContext.Player1Intel.ShipsInventory;
	//Show ships in grid
	for(Ship ship : P1Inventory)
	{
		for(Coordinates coord : ship.GridLocation)
		{
			Fl_Color color = FL_BLACK;
			string cellPos = coordsToCellPos(coord);
			reColorGridCell(uiData,cellPos, color);
		}
	}
	//Show hits received
	vector<Coordinates> hitsReceived = uiContext.Player1Intel.hitsReceived;
	for(Coordinates hit : hitsReceived)
	{
		Fl_Color color = FL_RED;
		string cellPos = coordsToCellPos(hit);
		reColorGridCell(uiData,cellPos, color);
	}
	//show hits on opponent
	vector<Coordinates> hits = uiContext.Player1Intel.hits;
	for(Coordinates hit : hits)
	{
		Fl_Color color = FL_GREEN;
		string cellPos = coordsToCellPos(hit);
		reColorGridCell(uiData,cellPos, color);
	}
	

}
void updatePlayer2Grid(UIElements uiData, ShipPlacementData *spd)
{
	
}

void updatePlayerWindows(UIElements uiData, ShipPlacementData *spd )
{
	//Update Player Turn Box
	updatePlayerTurnBox(uiData, spd);
	
	//Place Ships in Grid
	UIContext uiContext = spd->gameMaster->UIctx;
	
	
}	