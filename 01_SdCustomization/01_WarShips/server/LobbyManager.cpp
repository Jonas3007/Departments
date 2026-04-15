#include "LobbyManager.h"

int LobbyManager::createLobby(int clientSocket, std::string playerName )
{
	LobbyData newLobby;
	newLobby.LobbyID = lobbies.size() + 1; // Simple way to generate a unique lobby ID
	newLobby.player1 = playerName;
	newLobby.player2 = ""; // Will be set when the second player joins
	newLobby.player1Socket = clientSocket;
	newLobby.player2Socket = -1; // Will be set when the second player joins
	newLobby.gameMaster = new GameMaster(); // Create a new game master for this lobby
	
	lobbies.push_back(newLobby);
	return newLobby.LobbyID;
}

int LobbyManager::checkForAvailableLobby(const int &clientSocket, const std::string &playerName)
{
	bool lobbyJoined = false;
	for(const auto& lobby : lobbies)
	{
		if(lobby.player2Socket == -1) // Check if the second player slot is still available
		{
			lobbyJoined = true;
			return joinLobby(lobby.LobbyID, int clientSocket, std::string playerName); // Join the available lobb
		}
	}
	if(!lobbyJoined)
	{
		return createLobby(clientSocket, playerName); // No available lobby, create a new one
	}
}

int LobbyManager::joinLobby(const int &lobbyID,const int &clientSocket,const std::string &playerName)
{
	for(auto& lobby : lobbies)
	{
		if(lobby.LobbyID == lobbyID && lobby.player2Socket == -1) // Check if the lobby ID matches and the second player slot is available
		{
			lobby.player2 = playerName;
			lobby.player2Socket = clientSocket;
			return lobby.LobbyID; // Successfully joined the lobby
		}
	}
	return -1; // Failed to join the lobby (lobby not found or already full)
}