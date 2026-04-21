#include <iostream>
#include "Fl/Fl.H"
#include "Player_Window.h"
#include "NetworkClient.h"
#include "ClientMessageHandler.h"
#include "Callbacks.h"
using namespace std;

int main(int argc, char ** argv)
{
	NetworkClient netClient;
	UIHandler uiHandler;
	auto handler = std::make_shared<ClientMessageHandler>();
	netClient.setMsgHandler(handler);
	setClientMessageHandler(handler);
	handler->addListener(&uiHandler);
	netClient.startClient();
	
	Fl_Window* playerWindow = CreatePlayerWindow(uiHandler);
	
	return Fl::run();
}