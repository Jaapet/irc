#include "debug.hpp"
#include "error.hpp"
std::string Error::ERR_NOSUCHNICK_401(Server *server, Session *session, Message message)
{
	Debug::Reply("ERR_NOSUCHNICK(401)", session->getFdSocket());

	std::string msg = Utils::getServerPrefix(server, session, "401") + session->getNickName() + " " + message.params[0] + ":No such nick/channel" + Reply::endr;
	return(msg);
}

std::string Error::ERR_NOSUCHSERVER_402(Server *server, Session *session, Message message)
{
	Debug::Reply("ERR_NOSUCHSERVER(402)", session->getFdSocket());

	std::string msg = Utils::getServerPrefix(server, session, "402") + session->getNickName() + " " + message.params[0] + " :No such server" + Reply::endr;
	return(msg);
}

std::string Error::ERR_NOSUCHCHANNEL_403(Server *server, Session *session, Message message)
{
	Debug::Reply("ERR_NOSUCHCHANNEL(403)", session->getFdSocket());

	std::string msg = Utils::getServerPrefix(server, session, "403") + session->getNickName() + " " + message.params[0] + " :No such channel" + Reply::endr;
	return(msg);
}

std::string Error::ERR_TOOMANYCHANNELS_405(Server *server, Session *session, Message message)
{
	(void)message;
	Debug::Reply("ERR_TOOMANYCHANNELS(405)", session->getFdSocket());

	std::string chan_name;
	if(session->getChannel() == NULL)
		chan_name = "*";
	std::string msg = Utils::getServerPrefix(server, session, "405") + " " + chan_name + " :You have joined too many channels" + Reply::endr;
	return(msg);	
}

std::string Error::ERR_CANNOTSENDTICHAN_404(Server *server, Session *session, Message message)
{
	Debug::Reply("ERR_ERRONEUSNICKNAME(404)", session->getFdSocket());

	std::string msg = Utils::getServerPrefix(server, session, "404") + " " + session->getNickName() + " " + message.params[0] + " :Cannot send to channel" + Reply::endr;
	return(msg);	
}

std::string Error::ERR_TOOMANYTARGETS_407(Server *server, Session *session, Message message)
{
	Debug::Reply("ERR_TOOMANYTARGETS(407)", session->getFdSocket());

	std::string msg = Utils::getServerPrefix(server, session, "407") + session->getNickName() + " " + message.params[0] + "Too many target, care monda" + Reply::endr;
	return(msg);
}

std::string Error::ERR_NORECIPIENT_411(Server *server, Session *session, Message message)
{
	Debug::Reply("ERR_NORECIPIENT(411)", session->getFdSocket());

	std::string msg =Utils::getServerPrefix(server, session, "411") + session->getNickName() + " :No recipient given (" + message.command + ")" + Reply::endr;
	return(msg);
}

std::string Error::ERR_NOTEXTTOSNED_412(Server *server, Session *session, Message message)
{
	Debug::Reply("ERR_NOTEXTTOSNED(412)", session->getFdSocket());

	(void)message;
	std::string msg = Utils::getServerPrefix(server, session, "412") + session->getNickName() + " :No text to send" + Reply::endr;
	return(msg);
}


std::string Error::ERR_UNKNOWNCOMMAND_421(Server *server, Session *session, Message message)
{
	Debug::Reply("ERR_UNKNOWNCOMMAND(421)", session->getFdSocket());

	std::string msg = Utils::getServerPrefix(server, session, "421") + message.command + " :Unknown command" + Reply::endr;
	return(msg);	
}

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
std::string  Error::ERR_NOTONCHANNEL_442(Server *server, Session *session, Message message)
{
	Debug::Reply("ERR_NOTONCHANNEL(442)", session->getFdSocket());

	std::string msg = Utils::getServerPrefix(server, session, "442") + session->getNickName() + " " + message.params[0] + " :You're not on that channel" + Reply::endr;
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
	Debug::Reply("ERR_PASSWDMISMATCH(464)", session->getFdSocket());

	std::string msg = Utils::getServerPrefix(server, session, "464") + ":Password incorrect" + Reply::endr;
	return(msg);
}
std::string Error::ERR_INVITEONLYCHAN_473(Server *server, Session *session, std::string &chan_name)
{
	Debug::Reply("ERR_INVITEONLYCHAN(473)", session->getFdSocket());

	std::string msg = Utils::getServerPrefix(server, session, "473") + chan_name + " :Cannot join channel (+i)" + Reply::endr;
	return(msg);
}
std::string Error::ERR_BADCHANNELKEY_475(Server *server, Session *session, std::string &chan_name)
{
	Debug::Reply("ERR_BADCHANNELKEY(475)", session->getFdSocket());

	std::string msg = Utils::getServerPrefix(server, session, "475") + chan_name + " :Cannot join channel (+k)" + Reply::endr;
	return(msg);
}

std::string Error::ERR_BADCHANMASK_476(Server *server, Session *session, std::string &chan_name)
{
	Debug::Reply("ERR_BADCHANMASK(476)", session->getFdSocket());

	std::string msg = Utils::getServerPrefix(server, session, "476") + chan_name +  " :Bad Channel Mask" + Reply::endr;
	return(msg);
}



std::string Error::ERR_NOPRIVILEGES_481(Server *server, Session *session, Message message)
{
	Debug::Reply("ERR_NOPRIVILEGES(481)", session->getFdSocket());

	(void)message;
	std::string msg = Utils::getServerPrefix(server, session, "481") + session->getNickName() + " :Permission Denied - You're not an IRC operator" + Reply::endr;
	return(msg);
}
