#include "LobbyManager.h"
#include <stdexcept>
#include <iostream>

int LobbyManager::createLobby(std::string playerName )
{
	LobbyData newLobby;
	newLobby.LobbyID = lobbies.size() + 1; // Simple way to generate a unique lobby ID
	newLobby.player1 = playerName;
	newLobby.player2 = ""; // Will be set when the second player joins
	newLobby.gameMaster = std::make_unique<GameMaster>(); // Initialize a new GameMaster for this lobby
	
	lobbies.emplace(newLobby.LobbyID, std::move(newLobby)); // Add the new lobby to the map
	return newLobby.LobbyID;
}

int LobbyManager::checkForAvailableLobby( const std::string &playerName)
{
	bool lobbyJoined = false;
	auto it = lobbies.begin();
	while (it != lobbies.end())
	{
		if (it->second.player2.empty()) // Check if the second player slot is empty
		{
			joinLobby(it->second.LobbyID, playerName); // Join the lobby
			lobbyJoined = true;
			return it->second.LobbyID; // Return the lobby ID that was joined
		}
		++it;
	}
	if(!lobbyJoined)
	{
		return createLobby(playerName); // No available lobby, create a new one
	}
	return -1; // This line should never be reached, but is here to satisfy the compiler
}

void LobbyManager::joinLobby(const int &lobbyID,const std::string &playerName)
{
	if(lobbies.at(lobbyID).player2 != " ") // Check if the lobby is already full
	{
		throw std::runtime_error("Lobby is already full");
	}
	else
	{
		 lobbies.at(lobbyID).player2 = playerName;
	}
}

void LobbyManager::startGameForLobby(const int &lobbyID)
{
	if(lobbies.at(lobbyID).player1.empty() || lobbies.at(lobbyID).player2.empty())
	{
		throw std::runtime_error("Both players must be present to start the game");
	}
	else
	{
		lobbies.at(lobbyID).gameMaster->InitializeGame(lobbies.at(lobbyID).player1,lobbies.at(lobbyID).player2 ); // Initialize the game for this lobby
	}
}


// String Data structure that has to be implemented
// HIT -> after hit are the coordinates of the attack
// MISS -> after miss are the coordinates of the attack
// PLACE ->after place are the coordinates and the type of ship that should be placed
// JOIN -> after join is the player name the that was entered in the client
// ATTACK -> after attack are the coordinates of the attack
// Example: HIT:B4 -> this means that the attack on coordinates 3,4 was a hit
void LobbyManager::clientToGameMsgHandler(const int &lobbyID, const std::string &data,const std::string &command)
{
	if (command == "PLACE")
	{
		lobbies.at(lobbyID).gameMaster->PlacePlayerShip(data);
	}
	else if (command == "ATTACK")
	{
		lobbies.at(lobbyID).gameMaster->FireAtCoordinates(data);
	}
	else
	{
		std::cout << "Unknown command: " << command << "\n";
	}
}