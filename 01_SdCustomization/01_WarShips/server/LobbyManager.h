#pragma once 

#include <string>
#include <vector>
#include "GameMaster.h"
#include "LobbyData.h"

class GameMaster;

class LobbyManager
{
	public: 
		vector<LobbyData> lobbies;

	
		int createLobby(int clientSocket, std::string playerNames);
		int checkForAvailableLobby(int clientSocket, std::string playerName);
		int joinLobby(int lobbyID, int clientSocket, std::string playerName);
	private: 
	
};