#pragma once
#include <string>
#include "GameStateDTO.h"
#include <vector>
#include "Coordinates.h"
#include "ShipConfig.h"
#include "GamePhase.h"
#include "IGameStateListener.h"

class ClientMessageHandler
{
public:
	void addListener(IGameStateListener *listener);
	void notifyListeners(const GameStateDTO &newState);
	GameStateDTO handleMessage(const std::string &msg);
	void stringTokenizer(const std::string &message);
	void buildGameStateDTO(const std::string &type, const std::string &data);
	GamePhase parseGamePhase(const std::string &phaseStr);
	vector<Coordinates> stringToCoords(const std::string &data);
	vector<ShipConfig> stringToShipConfig(const std::string &data);

private:
	std::vector<IGameStateListener *> listeners;
	GameStateDTO dto;
};