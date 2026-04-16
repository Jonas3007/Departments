#include "MessageHandler.h"
#include "LobbyManager.h"
#include "GameMaster.h"	
#include <iostream>


void MessageHandler::serverToGame(const int &lobbyId,const std::string &data, const std::string &command)
{
	LobbyManager LobbyManager;
	auto gameMaster = LobbyManager.getGameMasterInstance(lobbyId);
	if (command == "PLACE")
	{
		gameMaster.PlacePlayerShip(data);
	}
	else if (command == "ATTACK")
	{
		gameMaster.FireAtCoordinates(data);
	}
	else
	{
		std::cout << "Unknown command: " << command << "\n";
	}
}
