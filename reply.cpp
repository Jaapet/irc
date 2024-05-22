#include "debug.hpp"
#include "reply.hpp"

namespace Reply {const std::string endr = "\r\n";}
//   start the message by : or add more prefix args
std::string Reply::getPrefix(Server *server, Session *session, std::string rep_code)
{
	std::string prefix;
	prefix = ":" + server->getHostName() + " " + rep_code + " " + session->getNickName() + " ";
	return(prefix);
}
std::string Reply::RPL_WELCOME_001(Server *server, Session *session)
{
	Debug::Reply("RPL_WELCOME(001)", session->getFdSocket());
	
	std::string msg = Reply::getPrefix(server, session, "001") + ":Welcome to the ft_irc " + session->getNickName() + Reply::endr;
	return(msg);
}