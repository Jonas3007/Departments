#include <catch2/catch_test_macros.hpp>
#include "GameMaster.h"
#include "Coordinates.h"
#include "PlayerIntel.h"
#include "ShipFactory.h"
#include "ShipConfig.h"
#include "Ship.h"
#include "UIContext.h"
#include <iostream>
#include <vector>


TEST_CASE("Test", "[GameMaster]")
{
	GameMaster gameMaster;
	int result = gameMaster.test(5);
	REQUIRE(result == 6);
}
