#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <algorithm>
#include <unistd.h>
#include <netinet/in.h>
#include <cstring>

struct ClientInfo
{
	int socket;
	std::string name;
};

std::vector<int> clients;
std::mutex clients_mutex;
std::mutex cInfo_mutex;
std::vector<ClientInfo> clientInfos;

void broadcast_message(const std::string &message, int senderSocket)
{
	std::lock_guard<std::mutex> lock(clients_mutex);

	for (int client : clients)
	{
		if (client != senderSocket)
		{
			send(client, message.c_str(), message.size(), 0);
		}
	}
}

void handleclient(int clientSocket)
{
	char buffer[1024];

	while (true)
	{
		memset(buffer, 0, sizeof(buffer));
		int bytes = recv(clientSocket, buffer, sizeof(buffer), 0);

		// checks if clients are still connected or if there is an error: 0 -> client disconnected, < 0 -> error, > 0 -> count of received bytes
		if (bytes <= 0)
		{
			std::cout << "Client disconnected \n";
			break;
		}
		// char buffer to string
		std::string message = buffer;

		std::cout << clientSocket << ":" << message << std::endl;
		// broadcast to every other client except the one who is sending the message
		broadcast_message(message, clientSocket);
	}

	{
		std::lock_guard<std::mutex> lock(clients_mutex);
		clients.erase(std::remove(clients.begin(), clients.end(), clientSocket), clients.end());
	}

	// close connection to client
	close(clientSocket);
}

int main()
{

	int server_fd = socket(AF_INET, SOCK_STREAM, 0); // socket file description

	sockaddr_in address{};
	address.sin_family = AF_INET;		  // IPv4
	address.sin_addr.s_addr = INADDR_ANY; // any IP address gets accepted
	address.sin_port = htons(12345);	  // bind socket to address and port

	bind(server_fd, (sockaddr *)&address, sizeof(address)); // connect socket to Ip and Port
	listen(server_fd, 10);									// 10 = backlog -> defines max length for pending connections

	std::cout << "Server Port: 12345\n";

	while (true)
	{
		socklen_t addrlen = sizeof(address);
		int clientSocket = accept(server_fd, (struct sockaddr *)&address, &addrlen);

		{
			std::lock_guard<std::mutex> lock(clients_mutex);
			clients.push_back(clientSocket);
		}
		std::thread(handleclient, clientSocket).detach();
	}
	return 0;
}