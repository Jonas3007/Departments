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
		// int = socket, Session = session data for the client connected with the socket
		std::unordered_map<int, Session> sessions;
		std::mutex session_mutex;
		LobbyManager lobbyManager;
		std::mutex lobby_mutex; // Mutex to protect access to the lobbyManager
		int PORT = 12345;
		
		void initializeServer();
		void handleclient(int clientSocket);
		void handleMessage(int clientSocket, const std::string& message);
		int getClientLobbybySocket(int clientSocket);
		void broadcastMessageToLobby(int lobbyId, const std::string& message);
	private: 
	
};
