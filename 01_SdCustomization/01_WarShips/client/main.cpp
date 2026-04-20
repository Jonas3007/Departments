#include <iostream>
#include "Fl/Fl.H"
#include "Player_Window.h"
#include "NetworkClient.h"
#include "ClientMessageHandler.h"

using namespace std;

int main(int argc, char ** argv)
{
	NetworkClient netClient;
	UIHandler uiHandler;
	ClientMessageHandler msgHandler;
	netClient.setMsgHandler(make_unique<ClientMessageHandler>(msgHandler));
	msgHandler.addListener(&uiHandler);
	netClient.startClient();
	
	Fl_Window* playerWindow = CreatePlayerWindow();
	
	return Fl::run();
}