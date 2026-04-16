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


class NetworkClient
{
	public: 
		int PORT = 12345;
		int BUFFER_SIZE = 1024;
	
		int startClient();
		void receive_messages(int sock);
	
	private: 
};