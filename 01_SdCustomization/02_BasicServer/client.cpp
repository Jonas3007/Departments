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

using namespace std;	

constexpr int PORT = 12345;
constexpr int BUFFER_SIZE = 1024;
void receive_messages(int sock)
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
		
		std::string message = buffer;
		std::cout << "Received: " << message << std::endl;
		
	}
	
}

int main() {
	int counter = 0;	
	string clientName;
	cout << "Enter your name: "; 
	cin >> clientName;
	int sock = 0;
	char buffer[BUFFER_SIZE] = {0};
	// Creating socket file descriptor
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		std::cerr << "Socket creation error" << std::endl;
		return -1;
	}
	sockaddr_in serv_addr{};
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	// Convert IPv4 and IPv6 addresses from text to binary form
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
		std::cerr << "Invalid address/ Address not supported" << std::endl;
		return -1;
	}
	// Connect to the server
	if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
		std::cerr << "Connection Failed" << std::endl;
		return -1;
	}
	while (true)
	{
		std::string input; 
		std::getline(std::cin, input);
		if (input == "exit")
		{
			// Close the socket and exit the loop
			close(sock);
			break;
		}
		std::string message = clientName + ": " + input; // Prepend the client's name to the message
		send(sock, message.c_str(), message.size(), 0);
		std::thread(receive_messages, sock).detach(); // Start a thread to receive messages from the server
	}
	exit(0);
	return 0;
}