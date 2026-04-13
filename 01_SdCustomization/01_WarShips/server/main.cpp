#include <FL/Fl.H>
#include <iostream>

#include "Coordinates.h"
#include "Ship.h"
#include "ShipFactory.h"
#include <typeinfo>
#include "GameMaster.h"


using namespace std;

int main(int argc, char** argv)
{
	GameMaster gameMaster;

	gameMaster.InitializeGame();
	ShipPlacementData *spd = new ShipPlacementData();
	

	return 0;
}