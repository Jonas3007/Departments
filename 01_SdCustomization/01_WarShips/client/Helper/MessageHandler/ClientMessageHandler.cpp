#include "ClientMessageHandler.h"
#include <iostream>
#include <string>
#include "GamePhase.h"

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
	// Player1
	else if (type == "P1NAME")
	{
		dto.player1Name = data;
	}
	else if (type == "P1SHIPSTOPLACE")
	{
		
	}
	else if (type == "P1HITS")
	{
		dto.player1Hits = stringToCoords(data);
	}
	else if (type == "P1MISSES")
	{
		dto.player1Misses = stringToCoords(data);
	}
	else if (type == "P1HITSRECEIVED")
	{
		dto.player1Hitsreceived = stringToCoords(data);
	}
	// Player2
	else if (type == "P2NAME")
	{
		dto.player2Name = data;
	}
	else if (type == "P2SHIPSTOPLACE")
	{
		
	}
	else if (type == "P2HITS")
	{
		dto.player2Hits = stringToCoords(data);
	}
	else if (type == "P2MISSES")
	{
		dto.player2Misses = stringToCoords(data);
	}
	else if (type == "P2HITSRECEIVED")
	{
		dto.player2Hitsreceived = stringToCoords(data);
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