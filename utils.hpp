#pragma once

#include <string>
#include <ctime>
#include "Message.hpp"
#include "Session.hpp"
#include "Server.hpp"
class Message;
class Server;
class Session;
namespace Utils
{
	std::string removeCRLF(std::string const &str);

	std::string strToUpper(std::string const &str);

	std::string getCurrentDate(void);

	bool isAllowedNickCharacter(char const c);
	bool findChar(std::string &str, char &c);
	bool findFlag(const std::string& str, char c);
	void removeDuplicatesStr(std::vector<std::string>& vec);
	void sendToChannel(Server *server, Channel *channel, std::string &msg, std::string &channelname_with_flags_from_msg);

	std::string getUserPrefix(Server *server, Session *session);
	std::string getServerPrefix(Server *server, Session *session, std::string rep_code);
}
