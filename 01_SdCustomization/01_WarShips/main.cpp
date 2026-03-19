#include <FL/Fl.H>
#include <iostream>
#include "Player_Window.h"
#include "Coordinates.h"
#include "Ship.h"
#include "UIContext.h"
#include "PlayerIntel.h"

using namespace std;

int main(int argc, char** argv)
{
	

	Fl_Window* playerWindow = CreatePlayerWindow();
	playerWindow->show(argc, argv);
	return Fl::run();
}