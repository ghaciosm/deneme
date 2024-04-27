#pragma once


#define USAGE "./ircserv [port] [password]"

#include <string>
#include <vector>
#include "Define.hpp"
#include <iostream>

using std::string;
using std::vector;
class Client;

namespace Utils {
	int					ft_stoi(const std::string & str);
	void				clearBuffer(char *buffer, int size);
	std::string			ft_trim(const std::string & str, const std::string & delims);
	std::vector<std::string>			ft_firstWord(const std::string & str);
	std::vector<std::string>			ft_split(const std::string & str, const std::string & delims);
	bool				isEqualNonSensitive(const string& str1, const string& str2);
	std::string			getTime();
	void				instaWriteAll(std::vector<Client> clients, std::string message);
	void				instaWrite(int fd, std::string message);
	std::string			ft_join(const std::vector<std::string> &vec, const std::string &delim, int start);
	void				instaSend(int fd, std::string message);
	int					getMaxFd(const vector<Client> &v, int serverfd);
	std::string			ft_getNick(const std::string& str);
	std::string			ft_itoa(int n);
	void 				printTime();
}
