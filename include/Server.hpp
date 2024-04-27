#pragma once

#include <string>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "Define.hpp"
#include "Room.hpp"
#include "CommandRPL.hpp"
#include "ErrorRPL.hpp"

#include <unistd.h>
#include <map>

using std::string;
using std::vector;

class Client;
class Room;

class Server
{
public:
	Server(const std::string & port, const std::string & password);
	virtual ~Server();
	void run();
	void join(const std::string & params, Client &client);
	void part(const std::string & params, Client &client);
	void privmsg(const std::string & command, Client &client);
	void op(const std::string & params, Client &client);
	void mode(const std::string & params, Client &client);
	void nick(const std::string & params, Client &client);
	void who(const std::string & command, Client &client);
	void topic(const std::string & command, Client &client);
	void ping(const std::string & params, Client &client);
	void quit(const std::string & params, Client &client);
	void whois(const std::string &, Client &cli);
	void list(const std::string & params, Client &client);
	void names(const std::string & params, Client &fd);
	void notice(const std::string & input, Client &fd);
	void kick(const std::string & input, Client &fd);
	void user(const std::string & params, Client &client);
	void cap(const std::string & params, Client &client);
	void pass(const std::string & param, Client &client);
	void invite(const std::string & input, Client &client);
	bool isClient(const std::string & nickname);

	Room &getRoom(const std::string & name);

	vector<Room> &getRooms();

	bool isRoom(const std::string & name);

	void addRoom(const Room &room);
	void addClient(const Client &client);

	vector<Client> &getClients();

	void	responseAllClientResponseToGui(Client &client, Room &room);
	bool	isClientInRoom(Room &room, const Client &client);
	bool	isClientInRoom(Client &client, string &room);
	bool	isClientInRoom(Room &room, string &nick);
	void	removeClient(int fd);

	Client	&getClientByNick(const std::string & nick);

	int		getSocket() const { return this->_socket; }

private:
	Server();
	Server(const Server &other);
	Server &operator=(const Server &other);
	void	initSocket();
	void	initFunctions();
	void	modeChannel(std::vector<std::string> &params, Client &client);
	void	runCommand(const std::string & command, Client &client);

	int					port;
	string				password;
	int					_socket;
	struct sockaddr_in	address;
	struct sockaddr_in	clientAddress;

	fd_set readfds;
	fd_set writefds;
	/*
		The reason for storing file descriptors in supplementary sets (this->readFdsSup and this->writeFdsSup)
		instead of directly modifying the original sets (this->readFds and this->writeFds) is to avoid race conditions
		and to ensure that the original sets remain unchanged for the next iteration of the loop.


		avoid blocking sockets we need to use select() function
		and copy the original sets to supplementary sets
	*/
	fd_set				writeFdsCopy;
	fd_set				readFdsCopy;

	vector<Client>		clients;
	vector<Room>		channels;

	char				buffer[1024];
	std::map<std::string, void (Server::*)(const std::string &, Client &)> _commands;
};
