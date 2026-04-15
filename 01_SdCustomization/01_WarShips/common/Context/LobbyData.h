#pragma once
#include "GameMaster.h"
#include <memory>

class GameMaster;

struct LobbyData
{
	int LobbyID;
	string player1;
	string player2;
	std::unique_ptr<GameMaster> gameMaster;
};