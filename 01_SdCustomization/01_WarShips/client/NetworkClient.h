#pragma once
#include "UIHandler.h"
#include <iostream>
#include <string>
#include <memory>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include "ClientMessageHandler.h"
#include "GameStateDTO.h"


class NetworkClient
{
	public: 
		int PORT = 12345;
		int BUFFER_SIZE = 1024;

		void setMsgHandler(shared_ptr<ClientMessageHandler> handler);
		int startClient();
		void receiveMessages(int sock);
		void sendMessage(int socket);
	
	private: 
		std::shared_ptr<ClientMessageHandler> msgHandler;
};