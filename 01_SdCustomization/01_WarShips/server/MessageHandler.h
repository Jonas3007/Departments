#pragma once 
#include "LobbyData.h"
#include "LobbyManager.h"


class MessageHandler
{
	public: 
	
		void serverToGame(const int &lobbyId,const std::string &data, const std::string &command);
	private: 
};