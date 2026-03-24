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
	UIContext* UIctx;
	UIctx->CurrentPhase = PlaceShips;

	Fl_Window* playerWindow = CreatePlayerWindow(UIctx);
	playerWindow->show(argc, argv);
	return Fl::run();

}