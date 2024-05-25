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
	std::string getUserPrefix(Server *server, Session *session);

	std::string cap(Server *server, Session *session, Message  message);
	std::string	pass(Server *server, Session *session, Message  message);
	std::string	nick(Server *server, Session *session, Message  message);
	std::string	user(Server *server, Session *session, Message  message);
	std::string	ping(Server *server, Session *session, Message  message);
	std::string	pong(Server *server, Session *session, Message  message);
	std::string	quit(Server *server, Session *session, Message  message);
	std::string	error(Server *server, Session *session, Message  message);
	std::string	error_v2(Server *server, Session *session, Message  message);
	std::string	privmsg(Server *server, Session *session, Message  message);
	std::string	notice(Server *server, Session *session, Message  message);
	//std::string	oper(Server *server, Session *session, Message  message);
};