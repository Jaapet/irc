#pragma once
#include <string>
#include "Session.hpp"

class Session;

class Server;

namespace Command
{
	void	pass(Server *server, Session *session, std::string rawline);
};