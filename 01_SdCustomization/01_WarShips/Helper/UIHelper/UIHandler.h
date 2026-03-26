#pragma once 
#include "ShipPlacementData.h"
#include "UIContext.h"
#include "GameMaster.h"
#include "UIElements.h"
#include "Player_Window.h"

//---------------------
// Update UI
//---------------------
void reColorGridCell(UIElements uiData, string cellPos);
void updatePlayerTurnBox(UIElements uiData, ShipPlacementData *spd);
void updatePlayerWindows(UIElements uiData, ShipPlacementData *spd);
