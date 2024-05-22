#pragma once
#include <string>
#include "Session.hpp"
#include "Server.hpp"
#include "Message.hpp"

struct Message;

class Session;

class Server;

namespace Command
{
	std::string cap(Server *server, Session *session, Message  message);
	std::string	pass(Server *server, Session *session, Message  message);
	std::string	nick(Server *server, Session *session, Message  message);
	std::string	user(Server *server, Session *session, Message  message);
};