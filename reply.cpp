#include "debug.hpp"
#include "reply.hpp"

namespace Reply {const std::string endr = "\r\n";}
//   start the message by : or add more prefix args

std::string Reply::PING_SERVER(Server *server, Session *session, Message message)
{
	Debug::Message("PING TO CLIENT", server->getFdSocket());
	
	(void)message;
	session->setWaitPong();
	std::string msg = ":" + server->getHostName() + " PING :" + session->getNickName() + Reply::endr;
	return(msg);
}

std::string Reply::RPL_WELCOME_001(Server *server, Session *session, Message message)
{
	Debug::Reply("RPL_WELCOME(001)", session->getFdSocket());
	
	(void)message;
	std::string msg = Utils::getServerPrefix(server, session, "001") + ":Welcome to the ft_irc " + session->getNickName() + Reply::endr;
	return(msg);
}
std::string Reply::RPL_YOURHOST_002(Server *server, Session *session, Message message)
{
	Debug::Reply("RPL_YOURHOST(002)", session->getFdSocket());
	
	(void)message;
	std::string msg = Utils::getServerPrefix(server, session, "002") + ":Your host is " + server->getServerName() + ", running version " + server->getVersion() + Reply::endr;
	return(msg);
}
std::string Reply::RPL_CREATED_003(Server *server, Session *session, Message message)
{
	Debug::Reply("RPL_CREATED(003)", session->getFdSocket());
	
	(void)message;
	std::string msg = Utils::getServerPrefix(server, session, "003") + ":This server was created " + server->getCreationDate() + Reply::endr;
	return(msg);
}
std::string Reply:: RPL_MYINFO_004(Server *server, Session *session, Message message)
{
	Debug::Reply("RPL_MYINFO(004)", session->getFdSocket());
	
	(void)message;
	std::string msg = Utils::getServerPrefix(server, session, "004") + server->getServerName() + " " + server->getVersion() + " " + server->getAvailableUserModes() + " " + server->getAvailableChannelModes() + Reply::endr; //Channel mode with a parameter ?
	return(msg);
}