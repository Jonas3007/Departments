#pragma once 
#include "ShipPlacementData.h"
#include "UIContext.h"
#include "GameMaster.h"
#include "UIElements.h"
#include "Player_Window.h"

//---------------------
// Update UI
//---------------------
class UIHandler
{
	public:
		//Setter for UI elements
		void setNameInput(Fl_Input *input);	
		void setPlayerTurnBox(Fl_Box *box);
		void setPhaseBox(Fl_Box *box);
		void setGridCells(Fl_Box *cells);
		void setShipPlacementElements(Fl_Button *battleshipBtn, Fl_Button *cruiserBtn, Fl_Button *destroyerBtn, Fl_Button *submarineBtn, Fl_Output *selectedShipOutput, Fl_Input *coordsInput);
		string getPlayerName();	
		//UI Update Functions
		void reColorGridCell(string cellPos, Fl_Color color);
		void updatePlayerTurnBox(GameMaster *gameMaster);
		void updatePhaseBox(GameMaster *gameMaster);
		void updatePlayer1Grid(GameMaster *gameMaster);
		void updatePlayer2Grid(GameMaster *gameMaster);
		void updatePlayerWindows(GameMaster *gameMaster);
		void toggleShipPlacementElements(GameMaster *gameMaster);
		
		Fl_Input *nameInput;

	private:
		Fl_Box *playerTurnBox;
		Fl_Box *phaseBox;
		vector<Fl_Box *> gridCells;
		
		// shipplacement elements
		Fl_Button *battleshipBtn;
		Fl_Button *cruiserBtn;
		Fl_Button *destroyerBtn;
		Fl_Button *submarineBtn;
		Fl_Output *selectedShipOutput;
		Fl_Input *coordsInput;
		
};

