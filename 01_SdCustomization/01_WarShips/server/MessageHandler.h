#pragma once 
#include "LobbyData.h"
#include "LobbyManager.h"
#include <vector>
#include "ShipConfig.h"
#include "Coordinates.h"
#include "GameStateDTO.h"
#include <string>
#include "LobbyManager.h"

class LobbyManager;
class MessageHandler
{
	public: 
	
		void serverToGame(const int &lobbyId,const std::string &data, const std::string &command, LobbyManager &lobbyManager);
		string GameStateDTOtoString(GameStateDTO gameStateDTO);
		string CoordsVectorToString(vector<Coordinates> coordsVector);
		string ShipConfigVectorToString(vector<ShipConfig> shipConfigVector);
	private: 
};