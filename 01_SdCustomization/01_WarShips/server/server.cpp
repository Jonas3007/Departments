#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <algorithm>
#include <unistd.h>
#include <netinet/in.h>
#include <cstring>
#include "server.h"
// String Data structure that has to be implemented 
// HIT -> after hit are the coordinates of the attack 
// MISS -> after miss are the coordinates of the attack
// PLACE ->after place are the coordinates and the type of ship that should be placed
// JOIN -> after join is the player name the that was entered in the client
// ATTACK -> after attack are the coordinates of the attack
// Example: HIT:B4 -> this means that the attack on coordinates 3,4 was a hit




void Server::handleMessage(int clientSocket, const std::string& message)
{
	int delimiterPos = message.find(':')
	if(message.empty() || delimiterPos == std::string::npos)
	{
		std::cout << "Invalid message format: " << message << "\n";
		return;
	}
	std::string command = message.substr(0, delimiterPos);
	std::string data = message.substr(delimiterPos + 1);
	
	switch (command)
	{
		case "HIT":
			std::cout << "Received HIT command with data: " << data << "\n";
			// Handle HIT logic here
			break;
		case "MISS":
			std::cout << "Received MISS command with data: " << data << "\n";
			// Handle MISS logic here
			break;
		case "PLACE":
			std::cout << "Received PLACE command with data: " << data << "\n";
			// Handle PLACE logic here
			break;
		case "JOIN":
			std::cout << "Received JOIN command with data: " << data << "\n";
			lobbyManager.checkForAvailableLobby(&clientSocket, &data); // Check for available lobby and join or create one
			break;
		case "ATTACK":
			std::cout << "Received ATTACK command with data: " << data << "\n";
			// Handle ATTACK logic here
			break;
		default:
			std::cout << "Unknown command: " << command << "\n";
			break;
	}
}

void Server::handleclient(int clientSocket)
{
	char buffer[];
	
	memset(buffer, 0, sizeof(buffer));
	int bytes = recv(clientSocket, buffer, sizeof(buffer), 0);
	
	if(bytes <= 0)
	{
		std::cout << "Client disconnected \n";
		{
			lock(session_mutex);
			sessions.erase(clientSocket);
		}
		return;
	}
	std::string msg = buffer;
	handleMessage(clientSocket, msg);
}

void Server::initializeServer()
{
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	
	sockaddr_in address{};
	address.sin_family = AF_INET;		  // IPv4
	address.sin_addr.s_addr = INADDR_ANY; // any IP address gets accepted
	address.sin_port = htons(PORT);	  // bind socket to address and port

	bind(server_fd, (sockaddr *)&address, sizeof(address)); // connect socket to Ip and Port
	listen(server_fd, 10);									// 10 = backlog -> defines max length for pending connections

	std::cout << "Server Port:"<< PORT<< "\n";

	while (true)
	{
		socklen_t addrlen = sizeof(address);
		int clientSocket = accept(server_fd, (struct sockaddr *)&address, &addrlen);

		{
			lock(session_mutex);
			sessions[clientSocket] = Session{clientSocket};
		}
		std::thread(handleclient, clientSocket).detach();
	}
	return 0;
	
}