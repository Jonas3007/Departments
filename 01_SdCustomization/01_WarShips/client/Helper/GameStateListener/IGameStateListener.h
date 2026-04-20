#pragma once 
#include "GameStateDTO.h"

class IGameStateListener
{
	public: 	
	virtual void onGameStateUpdate(const GameStateDTO &newState) = 0; // Pure virtual function to be implemented by derived classes
}; 
