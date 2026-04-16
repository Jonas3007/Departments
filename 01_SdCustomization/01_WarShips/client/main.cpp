#include <iostream>
#include "Fl/Fl.H"
#include "Player_Window.h"
#include "NetworkClient.h"
#include "ClientMessageHandler.h"

using namespace std;

int main(int argc, char ** argv)
{
	// NetworkClient netClient;
	// UIHandler uiHandler;
	// ClientMessageHandler msgHandler;
	// uiHandler.msgHandler = make_unique<ClientMessageHandler>(msgHandler);
	// netClient.startClient();
	
	// Fl_Window* playerWindow = CreatePlayerWindow();
	
	// return Fl::run();
	
	string coordinateString = "A1,;";
	int ps = coordinateString.find(',');
	string letter = coordinateString.substr(0, ps -1);
	int number = stoi(coordinateString.substr(1,ps));
	
	cout << letter << " : " << number << endl;
}