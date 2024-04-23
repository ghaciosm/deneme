#include "Server.hpp"
#include "Exception.hpp"
#include "Utils.hpp"
#include "Client.hpp"

#include "Room.hpp"
#include <string>
#include <iostream>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>
#include "Define.hpp"
#include <fcntl.h>

void Server::initSocket()
{
	this->_socket = socket(AF_INET, SOCK_STREAM, 0); // Create socket 0 for macos and IPPROTO_IP for linux ipv4 protokolüne göre soket oluşturur tcp için SOCK_STREAM udp için SOCK_DGRAM
	if (_socket < 0)
	{
		throw Exception("Socket creation failed");
	}
	else
	{
		std::cout << "Socket created successfully!    "; 
		Utils::printTime();
	}
	int dumb = 1;
	if (setsockopt(this->_socket, SOL_SOCKET, SO_REUSEADDR, &dumb, sizeof(int)) < 0)
	{
		throw Exception("Socket option failed");
	}
	else
	{
		std::cout << "Socket option set successfully! ";
		Utils::printTime() ;
	}
	if (fcntl(this->_socket, F_SETFL, O_NONBLOCK) < 0)
	{
		throw Exception("Socket fcntl failed on Server");
	}
	else
	{
		std::cout << "Socket fcntl set successfully!  ";
		Utils::printTime();
	}

	memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;		 
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(this->port);

	if (::bind(this->_socket, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		throw Exception("Socket bind failed");
	}
	else
	{
		std::cout << "Socket binded successfully!     ";
		Utils::printTime();
	}

	if (listen(this->_socket, SOMAXCONN) < 0)
	{
		throw Exception("Socket listen failed");
	}
	else
	{
		std::cout << "Socket listening successfully!  ";
		Utils::printTime() ;
	 }
}