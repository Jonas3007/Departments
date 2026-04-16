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
	//write Player1 data to message string and GamePhase
	message += "GAMEPHASE=" + to_string(dto.currentPhase) + ";";
	message += "P1NAME=" + dto.player1Name + ";";
	message += "P1SHIPSTOPLACE=" + ShipConfigVectorToString(dto.player1ShipsToPlace) + ";";
	message += "P1HITS=" + CoordsVectorToString(dto.player1Hits) + ";";
	message += "P1MISSES=" + CoordsVectorToString(dto.player1Misses) + ";";
	message += "P1HITSRECEIVED=" + CoordsVectorToString(dto.player1Hitsreceived) + ";";
	
	// write Player1 data to message string
	message += "P2NAME=" + dto.player2Name + ";";
	message += "P2SHIPSTOPLACE=" + ShipConfigVectorToString(dto.player2ShipsToPlace) + ";";
	message += "P2HITS=" + CoordsVectorToString(dto.player2Hits) + ";";
	message += "P2MISSES=" + CoordsVectorToString(dto.player2Misses) + ";";
	message += "P2HITSRECEIVED=" + CoordsVectorToString(dto.player2Hitsreceived) + ";";
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
