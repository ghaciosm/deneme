#pragma once

#include <string>
#include <vector>
#include "Define.hpp"
#include <netinet/in.h>

using std::string;
using std::vector;


class Client
{
public:
	Client();
	Client(int fd, int port);
	Client(const Client &other);
	Client			&operator=(const Client &other);

	int				getFd() const;
	int				getPort() const;
	string			getBuffer() const;
	bool			getIsRegistered() const;
	bool			getIsPassworded() const;
	int				getType() const;

	vector<string>	&getmesagesFromServer();
	string		  	getNick() const;
	string		  	getUserName() const;
	string		  	getRealName() const;
	string		  	getHostName() const;
	string		  	getServerName() const;

	void			setHostName(const std::string & hostName);
	void			setServerName(const std::string & serverName);
	void			setNick(const std::string & nick);
	void			setRegistered(bool val);
	void			setPassworded(bool val);
	void			setBuffer(const std::string & str);
	void			setType(int type);

	void			setUserName(const std::string & userName);
	void			setRealName(const std::string & realName);
	string			getUserByHexChat() const;
	virtual			~Client();
	char			_ip[INET_ADDRSTRLEN]; // 123.123.123.123 + \0

	bool			operator==(const Client &rhs) const;
private:
	int				_type; // 1:hex 3:bot
	int				_fd;// her clientin kendine ait fd si olacak ve server burdan haberleşecek (socket)
	int				_port;
	string			buffer;
	vector<string>	_messagesFromServer;
	bool			isRegistered;
	bool			isPassworded;
	string			_nick;
	string			_userName;
	string			_hostName;
	string			_serverName;
	string			_realName;
};
