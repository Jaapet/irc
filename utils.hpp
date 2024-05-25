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

	void sendToChannel(Server *server, Session *session, Message message);

	std::string getUserPrefix(Server *server, Session *session);
	std::string getServerPrefix(Server *server, Session *session, std::string rep_code);
}
