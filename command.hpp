#pragma once
#include <string>
#include "Session.hpp"

class Session;

class Server;

namespace Command
{
	std::string cap(Server *server, Session *session, std::string rawline);
	std::string	pass(Server *server, Session *session, std::string rawline);
	std::string	nick(Server *server, Session *session, std::string rawline);
	std::string	user(Server *server, Session *session, std::string rawline);
};