#include "ClientMessageHandler.h"
#include <iostream>
#include <string>
#include "GamePhase.h"

void ClientMessageHandler::addListener(IGameStateListener *listener)
{
	listeners.push_back(listener);
}
void ClientMessageHandler::notifyListeners(const GameStateDTO &newState)
{
	for (IGameStateListener *listener : listeners)
	{
		listener->onGameStateUpdate(newState);
	}
}
GameStateDTO ClientMessageHandler::handleMessage(const std::string &msg)
{
	
	this->stringTokenizer(msg);
	notifyListeners(dto);
	return dto;
}
void ClientMessageHandler::stringTokenizer(const std::string &msg)
{
	std::string message = msg;
	while (true)
	{
		int delPos = message.find(';');
		int equalPos = message.find('=');
		if (delPos == std::string::npos || equalPos == std::string::npos)
		{
			break; // No more tokens to process
		}
		string type = message.substr(0, equalPos);
		string data = message.substr(equalPos + 1, delPos - equalPos);
		buildGameStateDTO(type, data);
		message.erase(0, delPos + 1);
	}
}

void ClientMessageHandler::buildGameStateDTO(const std::string &type, const std::string &data)
{
	if (type == "GAMEPHASE")
	{
		dto.currentPhase == parseGamePhase(data);
	}
	// Player
	else if (type == "NAME")
	{
		dto.playerName = data;
	}
	else if (type == "SHIPSTOPLACE")
	{
		dto.playerShipsToPlace = stringToShipConfig(data);
	}
	else if (type == "HITS")
	{
		dto.playerHits = stringToCoords(data);
	}
	else if (type == "MISSES")
	{
		dto.playerMisses = stringToCoords(data);
	}
	else if (type == "HITSRECEIVED")
	{
		dto.playerHitsreceived = stringToCoords(data);
	}
	else if (type == "SHIPSPLACED")
	{
		dto.shipsPlaced = stringToCoords(data);
	}
	else if (type == "OPPONENTNAME")
	{
		dto.opponentName = data;
	}
	else if (type == "PLAYERINDEX")
	{
		dto.playerIndex = stoi(data);
	}
	else
	{
		cout << "Unknown DTO type: " << type << "\n";
	}
	
}

vector<Coordinates> ClientMessageHandler::stringToCoords(const std::string &data)
{
	vector<Coordinates> coordsVector;
	Coordinates coords;
	std::string cData= data;
	while (true)
	{
		int commaPos = cData.find(',');
		if (commaPos == std::string::npos)
		{
			break;
		}	
		string letter = cData.substr(0, commaPos -1);
		int number = stoi(cData.substr(1,commaPos));
		coords.Letter = letter[0];
		coords.Number = number;	
		coordsVector.push_back(coords);
		cData.erase(0, commaPos + 1);
	}
	return coordsVector;
}

vector<ShipConfig> ClientMessageHandler::stringToShipConfig(const std::string &data)
{
	vector<ShipConfig> shipConfigVector;
	std::string scData = data;
	while (true)
	{
		int colonPos =scData.find(':');
		int commaPos = scData.find(',');
		if (colonPos == std::string::npos || commaPos == std::string::npos)
		{
			break;
		}
		int shipSize = stoi(scData.substr(0, colonPos));
		int count = stoi(scData.substr(colonPos + 1, commaPos - colonPos));
		ShipConfig config;
		config.ShipSize = shipSize;
		config.Count = count;
		shipConfigVector.push_back(config);
		scData.erase(0, commaPos + 1);	
	}
	return shipConfigVector;
}
GamePhase ClientMessageHandler::parseGamePhase(const std::string &phaseStr)
{
	if (phaseStr == "PickNamePhase")
	{
		return GamePhase::PickNamePhase;
	}
	else if (phaseStr == "PlaceShipsP1")
	{
		return GamePhase::PlaceShipsP1;
	}
	else if (phaseStr == "PlaceShipsP2")
	{
		return GamePhase::PlaceShipsP2;
	}
	else if (phaseStr == "Player1Turn")
	{
		return GamePhase::Player1Turn;
	}
	else if (phaseStr == "Player2Turn")
	{
		return GamePhase::Player2Turn;
	}
	else if (phaseStr == "GameOver")
	{
		return GamePhase::GameOver;
	}
	else
	{
		cout << "Unknown GamePhase: " << phaseStr << "\n";
		return GamePhase::GameOver; // Default to GameOver for unknown phases
	}
}