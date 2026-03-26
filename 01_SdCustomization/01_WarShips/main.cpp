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

using namespace std;

int main(int argc, char** argv)
{
	GameMaster gameMaster;
	gameMaster.InitializeGame();
	UIContext UIctx = gameMaster.UIctx;
	UIElements *uiData = new UIElements();
	ShipPlacementData *spd = new ShipPlacementData();
	
	Fl_Window *player1Window = CreatePlayerWindow(&UIctx, &gameMaster, uiData, spd);

	return Fl::run();
}