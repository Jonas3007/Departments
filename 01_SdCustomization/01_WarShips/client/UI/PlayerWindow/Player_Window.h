#pragma once
#include <Fl/Fl_Window.H>
#include "Callbacks.h"
#include "UIHandler.h"
#include "ShipPlacementData.h"

class UIHandler;
Fl_Window* CreatePlayerWindow(const UIHandler &uiHandler);
