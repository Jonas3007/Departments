#pragma once 
#include "ShipPlacementData.h"
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
		//Player Grid
		void setGridCells(Fl_Box *cells);
		void setPlayerShipGridCells(Fl_Box *cells);
		void setFinishTurnBtn(Fl_Button *btn);
		void setEnterNamesBtn(Fl_Button *btn);	
		void setFireBtn(Fl_Button *btn);
		void setShipPlacementElements(Fl_Button *placeShipbtn,Fl_Button *battleshipBtn, Fl_Button *cruiserBtn, Fl_Button *destroyerBtn, Fl_Button *submarineBtn, Fl_Output *selectedShipOutput, Fl_Input *coordsInput, Fl_Multiline_Output *shipSizeOutput);
		string getPlayerName();	
		
		//UI Update single Elements
		void reColorGridCell(string cellPos, Fl_Color color);
		void reColorPlayerShipGridCell(string cellPos, Fl_Color color);	
		void updatePlayerTurnBox(GameMaster *gameMaster);
		void updatePhaseBox(GameMaster *gameMaster);
		void updatePlayer1Grid(GameMaster *gameMaster);
		void updatePlayer2Grid(GameMaster *gameMaster);
		void updateShipSizeOutput(GameMaster *gameMaster);
		void resetGridColors();	
		
		//UI Update according to GameState
		void updatePlayerWindows(GameMaster *gameMaster);
		void toggleEnterNamesBtn(GameMaster *gameMaster);	
		void toggleFinishTurnBtn(GameMaster *gameMaster);
		void toggleFireBtn(GameMaster *gameMaster);	
		void toggleShipPlacementElements(GameMaster *gameMaster);
		
		
		Fl_Input *nameInput;
		vector<Fl_Box *> PlayerShipGridCells;
		vector<Fl_Box *> gridCells;

	private:
		Fl_Button *firebtn;
		Fl_Button *enterNamesBtn;	
		Fl_Button *finishTurnBtn;
		//Game State Elements
		Fl_Box *playerTurnBox;
		Fl_Box *phaseBox;
		
		
		// shipplacement elements
		Fl_Button *placeShipBtn;
		Fl_Button *battleshipBtn;
		Fl_Button *cruiserBtn;
		Fl_Button *destroyerBtn;
		Fl_Button *submarineBtn;
		Fl_Output *selectedShipOutput;
		Fl_Input *coordsInput;
		Fl_Multiline_Output *shipSizeOutput;
		
};

