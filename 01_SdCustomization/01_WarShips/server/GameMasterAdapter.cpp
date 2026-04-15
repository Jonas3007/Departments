#include "GameMasterAdapter.h"

void GameMasterAdapter::getData(string data)
{
	while (true)
	{
		int commaPos = data.find(',');
		if(data.empty()){ break;}
		if (commaPos == string::npos)
		{
			currentData.push_back(data);
			break;
		}
		else
		{
			string token = data.substr(0, commaPos);
			currentData.push_back(token);
			data.erase(0, commaPos + 1);
		}
	}
}	

void GameMasterAdapter::processServerData()
{
	
}