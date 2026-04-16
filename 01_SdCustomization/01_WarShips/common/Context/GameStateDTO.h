#pragma once    


struct GameStateDTO
{
	string player1Name;
	string player2Name;
	vector<Ship> player1Ships;
	vector<Ship> player2Ships;
	vector<Coordinates> player1Hits;
	vector<Coordinates> player1Misses;
	vector<Coordinates> player1Hitsreceived;
	vector<Coordinates> player2Hits;
	vector<Coordinates> player2Misses;
	vector<Coordinates> player2Hitsreceived;
	GamePhase currentPhase;
};