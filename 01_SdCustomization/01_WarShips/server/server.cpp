#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <algorithm>
#include <unistd.h>
#include <netinet/in.h>
#include <cstring>
#include "server.h"
#include "MessageHandler.h"
// String Data structure that has to be implemented
// HIT -> after hit are the coordinates of the attack
// MISS -> after miss are the coordinates of the attack
// PLACE ->after place are the coordinates and the type of ship that should be placed
// JOIN -> after join is the player name the that was entered in the client
// ATTACK -> after attack are the coordinates of the attack
// Example: HIT:B4 -> this means that the attack on coordinates 3,4 was a hit

void Server::broadcastMessageToLobby(int lobbyId, const std::string &message)
{
	std::unordered_map<int, Session> lobbySessions;
	{
		std::lock_guard<std::mutex> lock(session_mutex);
		lobbySessions = sessions; // Create a copy of the sessions map to avoid holding the lock while sending messages
	}
	for (const auto &[key, value] : lobbySessions)
	{
		if (value.lobbyID == lobbyId)
		{
			send(value.socket, message.c_str(), message.size(), 0);
		}
	}
}

void Server::handleMessage(int clientSocket, const std::string &message)
{
	MessageHandler messageHandler; // Create an instance of MessageHandler to handle the message
	int delimiterPos = message.find(':');
	if (message.empty() || delimiterPos == std::string::npos)
	{
		std::cout << "Invalid message format: " << message << "\n";
		return;
	}
	std::string command = message.substr(0, delimiterPos);
	std::string data = message.substr(delimiterPos + 1);

	if (command == "JOIN")
	{
		int lobbyId = lobbyManager.checkForAvailableLobby(data); // Check for available lobby and join or create one
		{
			std::lock_guard<std::mutex> lock(session_mutex);
			sessions[clientSocket].playerName = data;
			sessions[clientSocket].lobbyID = lobbyId;
			std::cout << "Player " << data << " joined lobby " << lobbyId << "\n";
			// Optionally, send a response back to the client confirming the lobby join
		}
	}
	else if (command == "START")
	{
		lobbyManager.startGameForLobby(getClientLobbybySocket(clientSocket)); // Start the game for the lobby that the client is in
	}
	else
	{
		int lobbyId;
		lobbyId = getClientLobbybySocket(clientSocket); // Get the lobby ID for the client
		
		messageHandler.serverToGame(lobbyId, data, command, this->lobbyManager);
		{
			std::lock_guard<std::mutex> lock(lobby_mutex);
			GameStateDTO dto =  lobbyManager.getGameMasterInstance(lobbyId).buildGameStateDTO(); // Build the game state DTO with the gameMaster instance of the lobby
			std::string message = messageHandler.GameStateDTOtoString(dto); // Convert the game state DTO to a string message
			std::cout << "Broadcasting message to lobby " << lobbyId << ": \n" << message << "\n";
			broadcastMessageToLobby(lobbyId, message); // Broadcast the updated game state to all clients in the lobby
		}
		
	}
}

int Server::getClientLobbybySocket(int clientSocket)
{
	std::lock_guard<std::mutex> lock(session_mutex);
	return sessions.at(clientSocket).lobbyID;
}

void Server::handleclient(int clientSocket)
{
	char buffer[1024];

	
	while (true)
	{
		memset(buffer, 0, sizeof(buffer));
		int bytes = recv(clientSocket, buffer, sizeof(buffer), 0);

		if (bytes <= 0)
		{
			std::cout << "Client disconnected \n";
			{
				std::lock_guard<std::mutex> lock(session_mutex);
				sessions.erase(clientSocket);
			}
			return;
		}
		std::cout << "Client connected: " << clientSocket << "\n";
		std::string msg (buffer,bytes);
		cout << "Incoming:"<< clientSocket << ":" << msg << endl;
		//handleMessage(clientSocket, msg);
	}
}

void Server::initializeServer()
{
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);

	sockaddr_in address{};
	address.sin_family = AF_INET;		  // IPv4
	address.sin_addr.s_addr = INADDR_ANY; // any IP address gets accepted
	address.sin_port = htons(PORT);		  // bind socket to address and port

	bind(server_fd, (sockaddr *)&address, sizeof(address)); // connect socket to Ip and Port
	listen(server_fd, 10);									// 10 = backlog -> defines max length for pending connections

	std::cout << "Server Port:" << PORT << "\n";

	while (true)
	{
		socklen_t addrlen = sizeof(address);
		int clientSocket = accept(server_fd, (struct sockaddr *)&address, &addrlen);

		{
			std::lock_guard<std::mutex> lock(session_mutex);
			sessions[clientSocket].socket = clientSocket;
		}
		std::thread(&Server::handleclient, this, clientSocket).detach();
	}
	return;
}