#pragma once

#include <string>


struct Session
{
	int socket;
	std::string playerName;
	int lobbyID;
};