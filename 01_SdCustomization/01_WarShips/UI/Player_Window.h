#pragma once
#include <Fl/Fl_Window.H>
#include "UIContext.h"
#include "Callbacks.h"
#include "GameMaster.h"

class GameMaster;

Fl_Window* CreatePlayerWindow(UIContext *UIctx, GameMaster *gameMaster);
