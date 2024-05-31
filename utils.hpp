#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>

#include "Message.hpp"
#include "Session.hpp"
#include "Server.hpp"
class Channel;
struct Message;
class Server;
class Session;
namespace Utils
{
	std::string removeCRLF(std::string const &str);

	std::string strToUpper(std::string const &str);

	std::string getCurrentDate(void);
	std::string getCurrentTimestamp();

	bool isAllowedNickCharacter(char const c);
	bool findChar(std::string &str, char &c);
	bool findFlag(const std::string& str, char c);
	void removeDuplicatesStr(std::vector<std::string>& vec);
	void sendToChannel(Server *server, Channel *channel, std::string sender, std::string &msg, std::string &channelname_with_flags_from_msg);

	std::string getUserPrefix(Server *server, Session *session);
	std::string getServerPrefix(Server *server, Session *session, std::string rep_code);
	void sendBufferNow(Session *session);
	template <typename T>
	std::string itoa(T value) 
	{
	    std::ostringstream oss;
	    oss << value;
	    return oss.str();
	}
	bool isValidChannelName(const std::string& str);
	std::vector<std::string> split(const std::string& str, char delimiter);
}
