#include "command.hpp"
#include "debug.hpp"
#include "reply.hpp"
#include "error.hpp"
#include "Message.hpp"
#include <vector>



std::string Command::cap(Server *server, Session *session, Message message)
{
	(void)server;
	(void)session;
	(void)message;
	return("");
}

std::string	Command::pass(Server *server, Session *session, Message message)
{
	
	// //Check if the correct command was called, yes I check a 2nd time
	// if(args[0] != "PASS" || args[1].empty() == true)
	// {
	// 	Debug::Warning("PASS should not be called, arg0: " + args[0] + " arg1 " + args[1] + "\n rawline: \n" + rawline);
	// 	return ("");
	// }
	
	if(message.params.empty())
	{
		return(Error::ERR_NEEDMOREPARAMS_461(server, session, message));
	}
	if(session->getPassIsSet() == true)
	{
		return(Error::ERR_ALREADYREGISTRED_462(server, session));
		// server->killSession(session->getFdSocket()); //Disconect the user ?
	}
	
	
	//Passwd check
	if(server->checkPassword(message.params[0]) == false)
	{
		return(Error::ERR_PASSWDMISMATCH_464(server, session));
	}
	else
	{
		session->setPassTrue();
		return("");
		// return(Reply::RPL_WELCOME_001(server, session)); // FOR TEST
	}
}

static bool isAllowedNickCharacter(char const c)
{
	return (isalnum(c) || c == '[' || c == ']' || c == '{' || c == '}' || c == '\\' || c == '|' || c == '_' || c == '-');
}

std::string	Command::nick(Server *server, Session *session, Message message)
{
	if(session->getPassIsSet() == false)
		return("");
	if(session->getAuthenticated() == true)
		return(Error::ERR_ALREADYREGISTRED_462(server,session));
	if(message.params.empty())
		return(Error::ERR_NEEDMOREPARAMS_461(server, session, message));
	if(message.params[0].length() < 1 || message.params[0].length() > 9)
		return(Error::ERR_ERRONEUSNICKNAME_432(server, session, message));
	for(size_t i = 0; i < message.params[0].size(); i++)
	{
		if(!(isAllowedNickCharacter(message.params[0][i])))
			return(Error::ERR_ERRONEUSNICKNAME_432(server, session, message));
	}
	if(server->getSession(message.params[0]) != NULL)
		return(Error::ERR_NICKNAMEINUSE_433(server, session, message));
	session->setNickName(message.params[0]);
	if(session->authenticate())
	{
		return(	Reply::RPL_WELCOME_001(server,session,message) +\
				Reply::RPL_YOURHOST_002(server,session,message) +\
				Reply::RPL_CREATED_003(server,session,message) +\
				Reply::RPL_MYINFO_004(server,session,message));
	}
	else
		return("");
}

std::string	Command::user(Server *server, Session *session, Message message)
{
	if(session->getPassIsSet() == false)
		return("");
	if(session->getAuthenticated() == true)
		return(Error::ERR_ALREADYREGISTRED_462(server,session));
	if(message.params.empty() || (message.params.size() < 3 && (!(message.payload.empty()))) || (message.params.size() < 4 && (message.payload.empty())) )
		return(Error::ERR_NEEDMOREPARAMS_461(server, session, message));
	session->setUserName(message.params[0]);
	if(message.params.size() == 4)
		session->setRealName(message.params[3]);
	else
		session->setRealName(message.payload);
	if(session->authenticate())
	{
		return(	Reply::RPL_WELCOME_001(server,session,message) +\
				Reply::RPL_YOURHOST_002(server,session,message) +\
				Reply::RPL_CREATED_003(server,session,message) +\
				Reply::RPL_MYINFO_004(server,session,message));
	}
	else
		return("");
}
// send(i, msg.c_str(), msg.length(), 0);