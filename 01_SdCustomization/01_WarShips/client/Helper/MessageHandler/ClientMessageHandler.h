#pragma once 
#include <string>
#include "GameStateDTO.h"
#include <vector>
#include "Coordinates.h"
#include "ShipConfig.h"
#include "GamePhase.h"



class ClientMessageHandler
{
	public:
		
		GameStateDTO getGameStateDTO();
		void stringTokenizer(const std::string& message);
		void buildGameStateDTO(const std::string &type, const std::string &data);
		GamePhase parseGamePhase(const std::string &phaseStr);
		vector<Coordinates> stringToCoords(const std::string &data);
		vector<ShipConfig> stringToShipConfig(const std::string &data);
		
	private: 
		GameStateDTO dto;
	
};