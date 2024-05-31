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
	std::string	ping(Server *server, Session *session, Message  message);
	std::string	pong(Server *server, Session *session, Message  message);
	std::string	quit(Server *server, Session *session, Message  message);
	std::string	privmsg(Server *server, Session *session, Message  message);
	// std::string	notice(Server *server, Session *session, Message  message);
	//std::string	oper(Server *server, Session *session, Message  message);
	//CHANNELS-----------------------------------------------------
	std::string	join(Server *server, Session *session, Message  message);
	std::string	part(Server *server, Session *session, Message  message); //done, missing send to chan
	std::string	topic(Server *server, Session *session, Message  message);
	std::string	names(Server *server, Session *session, Message  message);
	std::string	list(Server *server, Session *session, Message  message);
	std::string	invite(Server *server, Session *session, Message  message);
	std::string	kick(Server *server, Session *session, Message  message);
	// std::string	motd(Server *server, Session *session, Message  message);
	// std::string	version(Server *server, Session *session, Message  message);
	// std::string	admin(Server *server, Session *session, Message  message);
	// std::string	lusers(Server *server, Session *session, Message  message);
	// std::string	time(Server *server, Session *session, Message  message);
	// std::string	stats(Server *server, Session *session, Message  message);
	// std::string	help(Server *server, Session *session, Message  message);
	// std::string	help(Server *server, Session *session, Message  message);
	// std::string	mode(Server *server, Session *session, Message  message);
	std::string	who(Server *server, Session *session, Message  message);
	// std::string	whois(Server *server, Session *session, Message  message);
	// std::string	away(Server *server, Session *session, Message  message);
	// std::string	userhost(Server *server, Session *session, Message  message);
	// std::string	wallops(Server *server, Session *session, Message  message);
}