#pragma once 

#include <string>
#include <vector>
#include "GameMaster.h"
#include "LobbyData.h"
#include <unordered_map>

class GameMaster;

class LobbyManager
{
	public: 
		std::unordered_map<int, LobbyData> lobbies; // Map of lobby ID to lobby data

	
		int createLobby(std::string playerNames);
		int checkForAvailableLobby(const std::string &layerName);
		void joinLobby(const int &lobbyID,const std::string &playerName);
		void removeLobby(const int &lobbyID);	
		void startGameForLobby(const int &lobbyID);
		void clientToGameMsgHandler(const int &lobbyID, const std::string &data, const std::string &command);
	private: 
	
};