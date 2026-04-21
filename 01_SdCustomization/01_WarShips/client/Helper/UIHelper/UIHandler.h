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
#include "Lobby_Window.h"
#include "GameOver_Window.h"
#include <memory>
#include "ClientMessageHandler.h"
#include "IGameStateListener.h"	

class LobbyWindow;
class ClientMessageHandler;	
//---------------------
// Update UI
//---------------------
class UIHandler: public IGameStateListener
{
	public:
		//LobbyWindow Elements
		//made the all public to avoid setter and getter for each element, since they are needed in callbacks and onGameStateUpdate
		Fl_Input *nameInput;
		Fl_Output *nameOutput;
		Fl_Button *joinGame_btn;
		Fl_Input *lobbyInput;
		Fl_Button *hostGame_btn;
		Fl_Button *check_btn;
		Fl_Output *lobbyOutput;
		Fl_Multiline_Output *infoOutput;
		LobbyWindow *lobbyWindow;
		
		//PlayerWindow Elements
		//Grids
		vector<Fl_Box *> PlayerShipGridCells;
		vector<Fl_Box *> gridCells;
		//Groups
		Fl_Group *PlayerShipGrid;
		Fl_Group *oceanGrid;
		//Buttons
		Fl_Button *placeShipBtn;
		Fl_Button *battleshipBtn;
		Fl_Button *cruiserBtn;
		Fl_Button *destroyerBtn;
		Fl_Button *submarineBtn;
		Fl_Button *firebtn;
		Fl_Button *enterNamesBtn;	
		Fl_Button *finishTurnBtn;
		//Game State Elements
		Fl_Box *playerTurnBox;
		Fl_Box *phaseBox;
		//Inputs and Outputs
		Fl_Output *selectedShipOutput;
		Fl_Input *coordsInput;
		Fl_Multiline_Output *shipSizeOutput;
		
		
		//GameOverWindow Elements
		GameOverWindow *gameOverWindow;
		GameStateDTO currentGameState;
		
		virtual void onGameStateUpdate(const GameStateDTO &newState) override; 
		void updateUIAccordingToGameState();	
			
		//setter for grid groups and cells	
		void setShipPlacementElements(Fl_Button *placeShipbtn,Fl_Button *battleshipBtn, Fl_Button *cruiserBtn, Fl_Button *destroyerBtn, Fl_Button *submarineBtn, Fl_Output *selectedShipOutput, Fl_Input *coordsInput, Fl_Multiline_Output *shipSizeOutput);
		
		string getPlayerName();	
		
		//UI Update single Elements
		void resetPlayerInputs();
		void reColorGridCell(string cellPos, Fl_Color color);
		void reColorPlayerShipGridCell(string cellPos, Fl_Color color);	
		void updatePlayerTurnBox();
		void updatePhaseBox();
		void updatePlayerGrid();
		void updateShipSizeOutput();
		void resetGridColors();	
		
		//UI Update according to GameState
	
		void toggleShipPlacementElements();
		
	private:
};

