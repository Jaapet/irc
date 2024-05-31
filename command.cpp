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
		if(!(Utils::isAllowedNickCharacter(message.params[0][i])))
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

// std::string	Command::error(Server *server, Session *session, Message  message)
// {
// 	(void)server;
// 	if(session->getAuthenticated() == false || message.payload.empty())
// 		return("");
// 	return("Error: " + message.payload + "\n");
// }

// std::string	Command::error_v2(Server *server, Session *session, Message  message)
// {
// 	(void)server;
// 	if(session->getAuthenticated() == false || message.payload.empty())
// 		return("");
// 	return("Error :" + Command::quit(server, session, message) + Reply::endr);
// }

std::string	Command::quit(Server *server, Session *session, Message  message)
{
	std::string msg;
	msg = "ERROR :Respond to QUIT from client";
	session->addSendBuffer(msg);
	msg = Utils::getUserPrefix(server, session) + "QUIT :" + "Quit: " + message.payload + Reply::endr;
	Channel *tmp_chan = session->getChannel();
	if(tmp_chan)
	{
		std::string chan_name = tmp_chan->get_name();
		if (tmp_chan->get_users().size() > 1)
		{
			Utils::sendToChannel(server, tmp_chan, session->getNickName(), msg, chan_name);
			tmp_chan->rm_user(session->getNickName());
		}
		else
			server->removeChannel(chan_name);
	}
		
	// {
		// std::string msg = ":" +session->getNickName() + " !d@" + server->getHostName() + "QUIT :" + "Quit: " + message.payload + Reply::endr; // A CHECK
		// std::vector<std::string> lst_user = tmp_chan->get_users();
		// for(size_t i = 0; i < lst_user.size(); i++)
		// {
		// 	server->getSession(lst_user[i])->addSendBuffer(msg);
		// }
	// }
	std::cout << "DEBUG5" << std::endl;
	server->killSession(session->getFdSocket(), true);
	std::cout << "DEBUG6" << std::endl;
	return("");
}

// std::string	Command::notice(Server *server, Session *session, Message  message)
// {
// 	if(session->getAuthenticated() == false)
// 		return ("");
// 	// If message.params[0] == & OU #, alors on boucle sur tous les utilisateurs de ce channel pour send le message
// 	if (!server->getSession(message.params[0]))
// 		return ("");
// 	std::string	msg = Utils::getUserPrefix(server, session) + "PRIVMSG " + message.params[0] + " :" + message.payload + Reply::endr;
// 	//send(fd, msg.c_str(), msg.size(), MSG_NOSIGNAL);
// 	server->getSession(message.params[0])->addSendBuffer(msg);
// 	return ("");
// }

std::string	Command::privmsg(Server *server, Session *session, Message  message)
{
	std::string msg;
	std::string command_name;
	if(message.command == "PRIVMSG")
		command_name = "PRIVMSG";
	else
		command_name = "NOTICE";
	if(session->getAuthenticated() == false)
		return ("");
	if (message.params.size() > 2)
		return (Error::ERR_TOOMANYTARGETS_407(server, session, message));
	if (message.params.size() == 0)
		return (Error::ERR_NORECIPIENT_411(server, session, message));
	if (message.payload.empty() && message.params.size() == 1)
		return (Error::ERR_NOTEXTTOSNED_412(server, session, message));
	if(message.params[0].find('#') != std::string::npos || message.params[0].find('&') != std::string::npos) //If PRIVMSG TO A CHANNEL
	{
		if (!Utils::isValidChannelName(message.params[0]))
			return (Error::ERR_BADCHANMASK_476(server, session, message.params[0]));
		Channel *target = server->getChannel(message.params[0].substr(message.params[0].find('#'))); //remove possible flags
		if(target == NULL)
			return(Error::ERR_NOSUCHCHANNEL_403(server, session, message));
		if(session->getChannel() != target)
			return(Error::ERR_CANNOTSENDTICHAN_404(server, session, message));
		if(!message.payload.empty())
			msg = Utils::getUserPrefix(server, session) + command_name + " " + message.params[0] + " :" + message.payload + Reply::endr;
		if(!msg.empty())
			Utils::sendToChannel(server, target, session->getNickName(),  msg, message.params[0]);
	}
	else //If PRIVMSG TO AN USER
	{
		if (!server->getSession(message.params[0]))
			return (Error::ERR_NOSUCHNICK_401(server, session, message));
		if (session->getAwayStatus() != "" && command_name != "NOTICE")
			return (Reply::RPL_AWAY_301(server, session, message));
		if(!message.payload.empty())
			msg = Utils::getUserPrefix(server, session) + command_name + " " + message.params[0] + " :" + message.payload + Reply::endr;
		else if(!message.params[1].empty())
			msg = Utils::getUserPrefix(server, session) + command_name + " " + message.params[0] + " :" + message.params[1] + Reply::endr; //Add for more natural command line

		server->getSession(message.params[0])->addSendBuffer(msg);
	}

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
	}}

//CHANNELS-----------------------------------------------------

std::string	Command::part(Server *server, Session *session, Message  message)
{
	if(session->getAuthenticated() == false)
		return ("");
	if (message.params.size() < 1)
		return (Error::ERR_NEEDMOREPARAMS_461(server, session, message));
	std::string reason;
	if (message.payload.empty())
		reason = "Unknown";
	else
		reason = message.payload;
	
	Channel *channel = server->getChannel(message.params[0]);
	if(channel == NULL)
		return(Error::ERR_NOSUCHCHANNEL_403(server, session, message));
	if(session->getChannel() != channel)
		return(Error::ERR_NOTONCHANNEL_442(server,session,message));
	if(channel->get_users().size() == 1)
	{
		session->setChannel(NULL);
		server->removeChannel(channel->get_name());
	}
	else
	{
		std::vector<std::string> chan_users = channel->get_users();
		for(size_t i = 0; i < chan_users.size(); i++)
		{
			// if(chan_users[i] != session->getNickName())
			// {
			std::string msg = Utils::getUserPrefix(server,session) + "PART " + channel->get_name() + " " + reason + Reply::endr;
			server->getSession(chan_users[i])->addSendBuffer(msg);
			// }
		}
	}
	return("");
}

std::string	Command::join(Server *server, Session *session, Message  message)
{
	if(session->getAuthenticated() == false)
		return ("");
	if(message.params.size() == 1 && message.params[0] == "0") // see RFC Join cmd
		return(Command::part(server, session, message));
	if(session->getChannel() != NULL)
		return(Error::ERR_TOOMANYCHANNELS_405(server,session,message));
	if(message.params.size() < 1)
		return(Error::ERR_NEEDMOREPARAMS_461(server, session, message));
	if(!Utils::isValidChannelName(message.params[0]))
		return(Error::ERR_BADCHANMASK_476(server,session, message.params[0]));

	if(message.params.size() == 1)
		message.params.push_back(""); //add a blank password to channel
	if(message.params.size() > 2) //if try to join more than a server
		return(Error::ERR_TOOMANYCHANNELS_405(server,session,message));
	Channel *target_chan;
	target_chan = server->getChannel(message.params[0]);
	bool newchan = false;
	if(target_chan == NULL)
	{
		newchan = true;
		Debug::Info("Channel name not found, lets create a new one");
		target_chan = new Channel(message.params[0], message.sender);
		target_chan->add_op(session->getNickName());
		target_chan->set_founder(session->getNickName());
		server->addChannel(message.params[0], target_chan);
	}
	else if(!target_chan->get_pw().empty() && !target_chan->checkPw(message.params[1])) //if chan have a password and the password don't match
		return(Error::ERR_BADCHANNELKEY_475(server, session, message.params[0]));
	else if(target_chan->get_inviteonly() && target_chan->getUserInvited(session->getNickName()) == false)
		return(Error::ERR_INVITEONLYCHAN_473(server, session, message.params[0]));
	//Check max USER ????
	target_chan->add_user(session->getNickName()); //Oui j'ai vu noé que tu renvoie un int, le probleme c'est que ça gere pas si le channel est en mode invite ou non
	std::string join_msg = Utils::getUserPrefix(server, session) +  "JOIN " + message.params[0] + Reply::endr;
	if(newchan == true)
		join_msg += Utils::getUserPrefix(server, session) +  "MODE " + message.params[0] + " +o " + session->getNickName() + Reply::endr;//inform that the user who create the chan is op
	Utils::sendToChannel(server, target_chan, session->getNickName(), join_msg, message.params[0]); //send join message of the user to all other users of this chan
	session->setChannel(target_chan);
	std::string msg = join_msg;
	if(target_chan->get_topic() != "")
	{
		msg += Reply::RPL_TOPIC_332(server, session, target_chan) + Reply::RPL_TOPICWHOTIME_333(server, session, target_chan);
	}
	msg += Reply::RPL_NAMREPLY_353(server, session, target_chan);
	msg += Reply::RPL_ENDOFNAMES_366(server, session, target_chan);
	return(msg);

}

std::string	Command::who(Server *server, Session *session, Message  message)
{
	if(session->getAuthenticated() == false)
		return ("");
	if(message.params.empty())
		return(Error::ERR_NEEDMOREPARAMS_461(server,session,message));
	std::string msg;
	if(message.params[0][0] == '#' || message.params[0][0] == '&')//If target is a channel
	{
		Channel *target_chan = server->getChannel(message.params[0]);
		if(target_chan == NULL)
			return(Error::ERR_NOSUCHCHANNEL_403(server, session, message));
		msg = Reply::RPL_WHOREPLY_352(server, session,target_chan, NULL) + Reply::RPL_ENDOFWHO_315(server, session, message);
	}
	else
	{
		Session *target_session = server->getSession(message.params[0]);
		if(target_session == NULL)
			return(Error::ERR_NOSUCHNICK_401(server, session, message));
		msg = Reply::RPL_WHOREPLY_352(server, session,NULL, target_session) + Reply::RPL_ENDOFWHO_315(server, session, message);
	}
	return(msg);
}

// std::string	Command::topic(Server *server, Session *session, Message  message)
// {

	
// }

// std::string	Command::names(Server *server, Session *session, Message  message)
// {

	
// }

// std::string	Command::list(Server *server, Session *session, Message  message)
// {

	
// }

// std::string	Command::invite(Server *server, Session *session, Message  message)
// {

	
// }

// std::string	Command::kick(Server *server, Session *session, Message  message)
// {

	
// }

// std::string	Command::motd(Server *server, Session *session, Message  message)
// {

	
// }

// std::string	Command::version(Server *server, Session *session, Message  message)
// {

	
// }

// std::string	Command::admin(Server *server, Session *session, Message  message)
// {

	
// }

// std::string	Command::lusers(Server *server, Session *session, Message  message)
// {

	
// }

// std::string	Command::time(Server *server, Session *session, Message  message)
// {

	
// }

// std::string	Command::stats(Server *server, Session *session, Message  message)
// {

	
// }

// std::string	Command::help(Server *server, Session *session, Message  message)
// {

	
// }

// std::string	Command::info(Server *server, Session *session, Message  message)
// {

	
// }

// std::string	Command::mode(Server *server, Session *session, Message  message)
// {

	
// }



// std::string	Command::whois(Server *server, Session *session, Message  message)
// {

	
// }


// std::string	Command::away(Server *server, Session *session, Message  message)
// {

	
// }

// std::string	Command::userhost(Server *server, Session *session, Message  message)
// {

	
// }

// std::string	Command::wallops(Server *server, Session *session, Message  message)
// {

	
// }
