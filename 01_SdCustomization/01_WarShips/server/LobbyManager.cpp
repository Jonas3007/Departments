#include "LobbyManager.h"
#include <stdexcept>
#include <iostream>

int LobbyManager::createLobby(std::string playerName)
{

	LobbyData newLobby;
	newLobby.LobbyID = lobbies.size() + 1; // Simple way to generate a unique lobby ID
	newLobby.player1 = playerName;
	newLobby.player2 = "";								  // Will be set when the second player joins
	newLobby.gameMaster = std::make_unique<GameMaster>(); // Initialize a new GameMaster for this lobby

	{
		std::lock_guard<std::mutex> lock(lobbyMutex);
		lobbies.emplace(newLobby.LobbyID, std::move(newLobby));
	}
	// Add the new lobby to the map
	return newLobby.LobbyID;
}

int LobbyManager::checkForAvailableLobby(const std::string &playerName)
{
	bool lobbyJoined = false;
	{
		std::lock_guard<std::mutex> lock(lobbyMutex);
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
	}
	if (!lobbyJoined)
	{
		return createLobby(playerName); // No available lobby, create a new one
	}
	return -1; // This line should never be reached, but is here to satisfy the compiler
}

void LobbyManager::joinLobby(const int &lobbyID, const std::string &playerName)
{
	{
		std::lock_guard<std::mutex> lock(lobbyMutex);
		if (lobbies.at(lobbyID).player2 != " ") // Check if the lobby is already full
		{
			throw std::runtime_error("Lobby is already full");
		}
		else
		{
			lobbies.at(lobbyID).player2 = playerName;
		}
	}
}

void LobbyManager::startGameForLobby(const int &lobbyID)
{

	if (lobbies.at(lobbyID).player1.empty() || lobbies.at(lobbyID).player2.empty())
	{
		throw std::runtime_error("Both players must be present to start the game");
	}
	else
	{
		{
			std::lock_guard<std::mutex> lock(lobbyMutex);
			lobbies.at(lobbyID).gameMaster->InitializeGame(lobbies.at(lobbyID).player1, lobbies.at(lobbyID).player2); // Initialize the game for this lobby
		}
	}
}


GameMaster LobbyManager::getGameMasterInstance(const int &lobbyId)
{
	return *(lobbies.at(lobbyId).gameMaster);
}