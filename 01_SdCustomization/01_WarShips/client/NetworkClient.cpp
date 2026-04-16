#include "NetworkClient.h"
#include "UIHandler.h"

void NetworkClient::receive_messages(int sock)
{
	char buffer[1024];
	while (true)
	{
		memset(buffer, 0, sizeof(buffer));
		int bytes = recv(sock, buffer, sizeof(buffer), 0);
		if (bytes <= 0)
		{
			std::cout << "Disconnected from server" << std::endl;
			break;
		}
		std::string message(buffer, bytes);
		std::cout << "Received: " << message << std::endl;
	}
	close(sock); // Close the socket when done
}
int NetworkClient::startClient()
{
	int sock = 0;
	char buffer[BUFFER_SIZE] = {0};
	// Creating socket file descriptor
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		std::cout << "Socket creation error" << std::endl;
		return -1;
	}
	sockaddr_in serv_addr{};
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	// Convert IPv4 and IPv6 addresses from text to binary form
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
	{
		std::cout << "Invalid address/ Address not supported" << std::endl;
		return -1;
	}
	// Connect to the server
	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		std::cout << "Connection Failed" << std::endl;
		return -1;
	}
	
	std::thread(&NetworkClient::receive_messages,this, sock).detach(); // Start a thread to receive messages from the server

	exit(0);
	return 0;
}