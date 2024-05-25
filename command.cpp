#include "command.hpp"
#include "debug.hpp"
#include "reply.hpp"
#include "error.hpp"
#include "Message.hpp"
#include <vector>

std::string Command::getUserPrefix(Server *server, Session *session)
{
	std::string prefix;
	prefix = ":" + session->getNickName() + "!" + session->getUserName() + "@" + server->getHostName() + " ";
	return(prefix);
}


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
				Reply::RPL_MYINFO_004(server,session,message) +\
				Reply::PING_SERVER(server,session,message));
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
				Reply::RPL_MYINFO_004(server,session,message) +\
				Reply::PING_SERVER(server,session,message));
	}
	else
		return("");
}
// send(i, msg.c_str(), msg.length(), 0);

// send(i, msg.c_str(), msg.length(), 0);

// std::string	Command::oper(Server *server, Session *session, Message  message)
// {
// 	if(session->getAuthenticated() == false)
// 		return("");
// 	if (message.params.size() != 2)
// 		return(Error::ERR_NEEDMOREPARAMS_461(server,session,message));
// 	else if (message.params[1].compare(server->getOpPassword()));
// 		return (Error::ERR_PASSWDMISMATCH_464(server, session));
// 	else if ()
// 	{
// 		/* code */
// 	}
	
// }

std::string	Command::error(Server *server, Session *session, Message  message)
{
	(void)server;
	if(session->getAuthenticated() == false || message.payload.empty())
		return("");
	return("Error: " + message.payload + "\n");
}

std::string	Command::error_v2(Server *server, Session *session, Message  message)
{
	(void)server;
	if(session->getAuthenticated() == false || message.payload.empty())
		return("");
	return("Error :" + Command::quit(server, session, message) + Reply::endr);
}

std::string	Command::quit(Server *server, Session *session, Message  message)
{
	server->killSession(session->getFdSocket());
	
	Channel *tmp_chan = session->getChannel();
	if(tmp_chan)
	{
		std::string msg = ":" +session->getNickName() + " !d@" + server->getHostName() + "QUIT :" + "Quit: " + message.payload + Reply::endr; // A CHECK
		std::vector<std::string> lst_user = tmp_chan->get_users();
		for(size_t i = 0; i < lst_user.size(); i++)
		{
			server->getSession(lst_user[i])->addSendBuffer(msg);
		}
	}
	return("");
}

std::string	Command::privmsg(Server *server, Session *session, Message  message)
{
	if(session->getAuthenticated() == false)
		return ("");
	if (message.params.size() > 1)
		return (Error::ERR_TOOMENYTARGETS_407(server, session, message));
	int fd = -1;
	// If message.params[0] == & OU #, alors on boucle sur tous les utilisateurs de ce channel pour send le message
	if (server->getSession(message.params[0]))
		fd = server->getSession(message.params[0])->getFdSocket();
	if (fd == -1)
		return (Error::ERR_NOSUCHNICK_401(server, session, message));
	std::string	msg = Command::getUserPrefix(server, session) + "PRIVMSG " + message.params[0] + " :" + message.payload + Reply::endr;
	send(fd, msg.c_str(), msg.size(), MSG_NOSIGNAL);
	return ("");
}

//Only from the client to the server
std::string	Command::ping(Server *server, Session *session, Message  message)
{
	if(session->getAuthenticated() == false)
		return("");
	if(message.payload.empty())
		return(Error::ERR_NEEDMOREPARAMS_461(server,session,message));
	//Reply Pong
	return(":" + server->getHostName() + " PONG :" + message.payload + Reply::endr);

}
//Only from the client to the server
std::string	Command::pong(Server *server, Session *session, Message  message)
{
	(void)server;
	if(session->getAuthenticated() == false)
	{
		Debug::Warning("Received an unexpected PONG while session not auth");
		return("");
	}
	if(session->getWaitPong() == true && message.payload == session->getNickName())
	{
		Debug::Info("Received a correct pong while waiting it");
		session->newPong();
		return("");
	}
	else
	{
		Debug::Warning("Received an unexpected PONG while not waiting it or the token is not valid");
		return("");
	}
	
}