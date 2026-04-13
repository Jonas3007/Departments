#include <iostream>
#include <string>
#include <memory>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;	

constexpr int PORT = 8080;
constexpr int BUFFER_SIZE = 1024;
int main() {
	int sock = 0;
	struct sockaddr_in serv_addr;
	char buffer[BUFFER_SIZE] = {0};
	// Creating socket file descriptor
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		std::cerr << "Socket creation error" << std::endl;
		return -1;
	}
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
		std::cin >> input;
		if (input == "exit")
		{
			// Close the socket and exit the loop
			close(sock);
			break;
		}
		std::string message = "Client says: " + input;
		send(sock, message.c_str(), message.size(), 0);
		std::cout << "Message sent: " << message << std::endl;
		ssize_t valread = read(sock, buffer, BUFFER_SIZE);
		std::cout << "Received: " << buffer << std::endl;
		memset(buffer, 0, BUFFER_SIZE); // Clear the buffer for the next message
	}
	exit(0);
	return 0;
}