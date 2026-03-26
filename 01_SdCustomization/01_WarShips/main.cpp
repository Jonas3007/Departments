#include <FL/Fl.H>
#include <iostream>
#include "Player_Window.h"
#include "Coordinates.h"
#include "Ship.h"
#include "UIContext.h"
#include "PlayerIntel.h"
#include "ShipFactory.h"
#include <typeinfo>
#include "GameMaster.h"
#include "UIHandler.h"

using namespace std;

int main(int argc, char** argv)
{
	GameMaster gameMaster;
	UIHandler uiHandler;
	gameMaster.uiHandler = &uiHandler;
	gameMaster.InitializeGame();
	UIContext UIctx = gameMaster.UIctx;
	ShipPlacementData *spd = new ShipPlacementData();
	
	Fl_Window *player1Window = CreatePlayerWindow(&UIctx, &gameMaster, spd);

	return Fl::run();
}