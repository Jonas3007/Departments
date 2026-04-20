#include "MessageHandler.h"
#include "LobbyManager.h"
#include "GameMaster.h"	
#include "GameStateDTO.h"
#include "Coordinates.h"
#include "ShipConfig.h"
#include <string>
#include <iostream>


void MessageHandler::serverToGame(const int &lobbyId,const std::string &data, const std::string &command, LobbyManager &lobbyManager)
{	
	if (command == "PLACE")
	{
		lobbyManager.getGameMasterInstance(lobbyId).PlacePlayerShip(data);
	}
	else if (command == "ATTACK")
	{
		lobbyManager.getGameMasterInstance(lobbyId).FireAtCoordinates(data);
	}
	else
	{
		std::cout << "Unknown command: " << command << "\n";
	}
}

string MessageHandler::GameStateDTOtoString(GameStateDTO dto)
{
	string message;
	//write Player data to message string and GamePhase
	message += "GAMEPHASE=" + to_string(dto.currentPhase) + ";";
	message += "PLAYERINDEX=" + to_string(dto.playerIndex) + ";";
	message += "NAME=" + dto.playerName + ";";
	message += "OPPONENTNAME=" + dto.opponentName + ";";	
	message += "SHIPSTOPLACE=" + ShipConfigVectorToString(dto.playerShipsToPlace) + ";";
	message += "HITS=" + CoordsVectorToString(dto.playerHits) + ";";
	message += "MISSES=" + CoordsVectorToString(dto.playerMisses) + ";";
	message += "HITSRECEIVED=" + CoordsVectorToString(dto.playerHitsreceived) + ";";
	message += "SHIPSPLACED=" + CoordsVectorToString(dto.shipsPlaced) + ";";
	return message;
}

string MessageHandler::CoordsVectorToString(vector<Coordinates> coordsVector)
{
	string result;
	for (const auto &coords : coordsVector)
	{
		result += coords.Letter + to_string(coords.Number) + ",";
	}
	return result;
}
string MessageHandler::ShipConfigVectorToString(vector<ShipConfig> shipConfigVector)
{
	string result;
	for (const auto &config : shipConfigVector)
	{
		result += to_string(config.ShipSize) + ":" + to_string(config.Count) + ",";
	}
	return result;
}
