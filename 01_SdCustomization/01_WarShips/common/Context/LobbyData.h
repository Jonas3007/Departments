#pragma once
#include "GameMaster.h"

class GameMaster;

struct LobbyData
{
	int LobbyID;
	int player1Socket;
	int player2Socket;
	string player1;
	string player2;
	GameMaster *gameMaster;
};