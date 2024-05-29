#include "debug.hpp"
#include "error.hpp"
std::string Error::ERR_ERRONEUSNICKNAME_432(Server *server, Session *session, Message message)
{
	Debug::Reply("ERR_ERRONEUSNICKNAME(432)", session->getFdSocket());

	std::string msg = Utils::getServerPrefix(server, session, "432") + " " + message.params[0] + " :Erroneus nickname" + Reply::endr;
	return(msg);	
}

std::string Error::ERR_NICKNAMEINUSE_433(Server *server, Session *session, Message message)
{
	Debug::Reply("ERR_NICKNAMEINUSE(433)", session->getFdSocket());

	std::string msg = Utils::getServerPrefix(server, session, "433") + " " + message.params[0] + " :Nickname is already in use" + Reply::endr;
	return(msg);	
}

std::string Error::ERR_NEEDMOREPARAMS_461(Server *server, Session *session,  Message message)
{
	Debug::Reply("ERR_NEEDMOREPARAMS_461(461)", session->getFdSocket());

	std::string msg = Utils::getServerPrefix(server, session, "461") + message.command + " :Not enough parameters" + Reply::endr;
	return(msg);	
}

std::string Error::ERR_ALREADYREGISTRED_462(Server *server, Session *session)
{
	Debug::Reply("ERR_ALREADYREGISTRED(462)", session->getFdSocket());

	std::string msg = Utils::getServerPrefix(server, session, "462") + ":You may not reregister" + Reply::endr;
	return(msg);	
}

std::string Error::ERR_PASSWDMISMATCH_464(Server *server, Session *session)
{
	Debug::Reply("ERR_PASSWDMISMATCH_464", session->getFdSocket());

	std::string msg = Utils::getServerPrefix(server, session, "464") + ":Password incorrect" + Reply::endr;
	return(msg);
}

std::string Error::ERR_CANNOTSENDTICHAN_404(Server *server, Session *session, Message message)
{
	Debug::Reply("ERR_ERRONEUSNICKNAME(404)", session->getFdSocket());

	(void)message;
	std::string msg = Utils::getServerPrefix(server, session, "404") + " " + session->getNickName() + " " + "<channel>" + " :Cannot send to channel" + Reply::endr;
	return(msg);	
}

std::string Error::ERR_NOSUCHNICK_401(Server *server, Session *session, Message message)
{
	Debug::Reply("ERR_NOSUCHNICK(401)", session->getFdSocket());

	std::string msg = Utils::getServerPrefix(server, session, "401") + session->getNickName() + " " + message.params[0] + ":No such nick/channel" + Reply::endr;
	return(msg);
}

std::string Error::ERR_TOOMENYTARGETS_407(Server *server, Session *session, Message message)
{
	Debug::Reply("ERR_TOOMENYTARGETS(407)", session->getFdSocket());

	std::string msg = Utils::getServerPrefix(server, session, "407") + session->getNickName() + " " + message.params[0] + "Too many target, care monda" + Reply::endr;
	return(msg);
}

std::string Error::ERR_NORECIPIENT_411(Server *server, Session *session, Message message)
{
	Debug::Reply("ERR_NORECIPIENT(411)", session->getFdSocket());

	std::string msg = Utils::getServerPrefix(server, session, "411") + session->getNickName() + " :No recipient given (" + message.command + ")" + Reply::endr;
	return(msg);
}

std::string Error::ERR_NOTEXTTOSNED_412(Server *server, Session *session, Message message)
{
	Debug::Reply("ERR_NOTEXTTOSNED(412)", session->getFdSocket());

	(void)message;
	std::string msg = Utils::getServerPrefix(server, session, "412") + session->getNickName() + " :No text to send" + Reply::endr;
	return(msg);
}

std::string Error::RPL_AWAY_301(Server *server, Session *session, Message message)
{
	Debug::Reply("ERR_NOTEXTTOSNED(301)", session->getFdSocket());

	std::string msg = Utils::getServerPrefix(server, session, "301") + session->getNickName() + " " + message.params[0] + " :" + session->getAwayStatus() + Reply::endr;
	return(msg);
}

std::string ERR_NOSUCHCHANNEL_403(Server *server, Session *session, Message message)
{
	Debug::Reply("ERR_NOSUCHCHANNEL(403)", session->getFdSocket());

	std::string msg = Utils::getServerPrefix(server, session, "403") + session->getNickName() + " " + message.params[0] + " :No such channel" + Reply::endr;
	return(msg);
}

std::string ERR_NOTONCHANNEL_442(Server *server, Session *session, Message message)
{
	Debug::Reply("ERR_NOTONCHANNEL(442)", session->getFdSocket());

	std::string msg = Utils::getServerPrefix(server, session, "442") + session->getNickName() + " " + message.params[0] + " :You're not on that channel" + Reply::endr;
	return(msg);
}
