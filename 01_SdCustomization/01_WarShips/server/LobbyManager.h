#pragma once 

#include <string>
#include <vector>
#include "LobbyData.h"
#include <unordered_map>
#include "MessageHandler.h"
#include <mutex>
#include "GameMaster.h"


class LobbyManager
{
	public: 
		std::unordered_map<int, LobbyData> lobbies; // Map of lobby ID to lobby data
		std::mutex lobbyMutex; // Mutex to protect access to the lobbies map

	
		int createLobby(std::string playerNames);
		int checkForAvailableLobby(const std::string &layerName);
		void joinLobby(const int &lobbyID,const std::string &playerName);
		void removeLobby(const int &lobbyID);	
		void startGameForLobby(const int &lobbyID);
		GameMaster getGameMasterInstance(const int &lobbyId);
	private: 
	
};