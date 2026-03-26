#pragma once 
#include "ShipPlacementData.h"
#include "UIContext.h"
#include "GameMaster.h"
#include "Player_Window.h"
#include <Fl/Fl_Input.H>
#include <Fl/Fl_Box.H>
#include <vector>
#include "Ship.h"
#include "Fl/Fl_Button.H"
#include "Fl/Fl_Output.H"
#include "Fl/Fl_Multiline_Output.H"

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
		void setShipPlacementElements(Fl_Button *battleshipBtn, Fl_Button *cruiserBtn, Fl_Button *destroyerBtn, Fl_Button *submarineBtn, Fl_Output *selectedShipOutput, Fl_Input *coordsInput, Fl_Multiline_Output *shipSizeOutput);
		string getPlayerName();	
		//UI Update Functions
		void reColorGridCell(string cellPos, Fl_Color color);
		void updatePlayerTurnBox(GameMaster *gameMaster);
		void updatePhaseBox(GameMaster *gameMaster);
		void updatePlayer1Grid(GameMaster *gameMaster);
		void updatePlayer2Grid(GameMaster *gameMaster);
		void updatePlayerWindows(GameMaster *gameMaster);
		void toggleShipPlacementElements(GameMaster *gameMaster);
		void updateShipSizeOutput(GameMaster *gameMaster);
		
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
		Fl_Multiline_Output *shipSizeOutput;
		
};

