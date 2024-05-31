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
//Connection Messages
	std::string cap(Server *server, Session *session, Message  message); // To ignore
	// std::string	authenticate(Server *server, Session *session, Message  message); //Not to do
	std::string	pass(Server *server, Session *session, Message  message);
	std::string	nick(Server *server, Session *session, Message  message);
	std::string	user(Server *server, Session *session, Message  message);
	std::string	ping(Server *server, Session *session, Message  message);
	std::string	pong(Server *server, Session *session, Message  message);
	// std::string	oper(Server *server, Session *session, Message  message); //Not to do
	std::string	quit(Server *server, Session *session, Message  message);
	// std::string	error(Server *server, Session *session, Message  message); //Not to do
	std::string	join(Server *server, Session *session, Message  message);

	std::string	part(Server *server, Session *session, Message  message);
	std::string	topic(Server *server, Session *session, Message  message);
	std::string	names(Server *server, Session *session, Message  message);
	std::string	list(Server *server, Session *session, Message  message);
	// std::string	invite(Server *server, Session *session, Message  message);
	// std::string	kick(Server *server, Session *session, Message  message);
//Server Queries and Commands
	// std::string	motd(Server *server, Session *session, Message  message);
	// std::string	version(Server *server, Session *session, Message  message);
	// std::string	admin(Server *server, Session *session, Message  message);
	// std::string	connect(Server *server, Session *session, Message  message); // to throw an error
	// std::string	lusers(Server *server, Session *session, Message  message);
	// std::string	time(Server *server, Session *session, Message  message);
	// std::string	stats(Server *server, Session *session, Message  message);
	// std::string	help(Server *server, Session *session, Message  message);
	// std::string	info(Server *server, Session *session, Message  message);
	std::string	mode(Server *server, Session *session, Message  message);
//Sending Messages
	std::string	privmsg(Server *server, Session *session, Message  message);
	// std::string	notice(Server *server, Session *session, Message  message); // to throw an error
//User-Based Queries
	std::string	who(Server *server, Session *session, Message  message);
	// std::string	whois(Server *server, Session *session, Message  message);
	// std::string	whowas(Server *server, Session *session, Message  message); // Not to do
//Operator Messages
	// std::string	kill(Server *server, Session *session, Message  message); // Not to do
	// std::string	rehash(Server *server, Session *session, Message  message); // Not to do
	// std::string	restart(Server *server, Session *session, Message  message); // Not to do
	// std::string	squit(Server *server, Session *session, Message  message); // Not to do
//Optional Messages
	// std::string	away(Server *server, Session *session, Message  message);
	// std::string	links(Server *server, Session *session, Message  message); // Not to do
	// std::string	userhost(Server *server, Session *session, Message  message);
	// std::string	wallops(Server *server, Session *session, Message  message);
}