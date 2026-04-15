#include <FL/Fl.H>
#include <iostream>

#include "Coordinates.h"
#include "Ship.h"
#include "ShipFactory.h"
#include <typeinfo>
#include "GameMaster.h"
#include "server.h"

class Server;
using namespace std;

int main(int argc, char** argv)
{
	Server server;
	server.initializeServer();
	return 0;
}