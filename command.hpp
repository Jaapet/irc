#pragma once
#include <string>
#include "Session.hpp"

class Session;

class Server;

namespace Command
{
	std::string	pass(Server *server, Session *session, std::string rawline);
};