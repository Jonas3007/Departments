#pragma once

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <algorithm>
#include <unistd.h>
#include <netinet/in.h>
#include <cstring>
#include "Session.h"
#include <map>
#include <unordered_map>
#include "LobbyManager.h"

class Server
{
	public: 
		std::unordered_map<int, Session> sessions;
		std::mutex session_mutex;
		LobbyManager lobbyManager;	
		int PORT = 3007;
		
		void initializeServer();
		void handleclient(int clientSocket);
		void handleMessage(int clientSocket, const std::string& message);
		int getClientLobbybySocket(int clientSocket);
	private: 
	
};
