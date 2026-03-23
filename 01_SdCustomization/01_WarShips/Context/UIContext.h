#pragma once
#include "PlayerIntel.h"
#include "GamePhase.h"


struct UIContext
{
	GamePhase CurrentPhase;
	PlayerIntel Player1Intel;
	PlayerIntel Player2Intel;
};