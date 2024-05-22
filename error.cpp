#include "debug.hpp"
#include "error.hpp"
std::string Error::ERR_ERRONEUSNICKNAME_432(Server *server, Session *session, Message message)
{
	Debug::Reply("ERR_ERRONEUSNICKNAME(432)", session->getFdSocket());

	std::string msg = Reply::getPrefix(server, session, "432") + " " + message.params[0] + " :Erroneus nickname" + Reply::endr;
	return(msg);	
}

std::string Error::ERR_NICKNAMEINUSE_433(Server *server, Session *session, Message message)
{
	Debug::Reply("ERR_NICKNAMEINUSE(433)", session->getFdSocket());

	std::string msg = Reply::getPrefix(server, session, "433") + " " + message.params[0] + " :Nickname is already in use" + Reply::endr;
	return(msg);	
}

std::string Error::ERR_NEEDMOREPARAMS_461(Server *server, Session *session,  Message message)
{
	Debug::Reply("ERR_NEEDMOREPARAMS_461(461)", session->getFdSocket());

	std::string msg = Reply::getPrefix(server, session, "461") + message.command + " :Not enough parameters" + Reply::endr;
	return(msg);	
}

std::string Error::ERR_ALREADYREGISTRED_462(Server *server, Session *session)
{
	Debug::Reply("ERR_ALREADYREGISTRED(462)", session->getFdSocket());

	std::string msg = Reply::getPrefix(server, session, "462") + ":You may not reregister" + Reply::endr;
	return(msg);	
}
std::string Error::ERR_PASSWDMISMATCH_464(Server *server, Session *session)
{
	Debug::Reply("ERR_PASSWDMISMATCH_464", session->getFdSocket());

	std::string msg = Reply::getPrefix(server, session, "464") + ":Password incorrect" + Reply::endr;
	return(msg);
}