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

std::string Reply::RPL_AWAY_301(Server *server, Session *session, Message message)
{
	Debug::Reply("ERR_NOTEXTTOSNED(301)", session->getFdSocket());

	std::string msg = Utils::getServerPrefix(server, session, "301") + session->getNickName() + " " + message.params[0] + " :" + session->getAwayStatus() + Reply::endr;
	return(msg);
}

std::string Reply::RPL_ENDOFWHO_315(Server *server, Session *session, Message message)
{
	std::string msg;
	msg = Utils::getServerPrefix(server, session, "315") + message.params[0] + " :End of WHO list" + Reply::endr;
	return(msg);
}
std::string Reply::RPL_CHANNELMODEIS_324(Server *server, Session *session, Message message)
{
	Debug::Reply("RPL_CHANNELMODEIS(324)", session->getFdSocket());

	std::string msg = Utils::getServerPrefix(server,session,"324") + message.params[0];

	std::string mode_str = " +";
	std::string mode_arg = "";
	if(server->getChannel(message.params[0])->get_inviteonly() == true)
		mode_str += "i";
	if(server->getChannel(message.params[0])->get_topicrestricted() == true)
		mode_str += "t";
	if(server->getChannel(message.params[0])->get_pw() != "")
	{
		mode_str += "k";
		if(mode_arg != "")
			mode_arg += " ";
		mode_arg += server->getChannel(message.params[0])->get_pw();
	}
	if(server->getChannel(message.params[0])->get_maxusers() > 0)
	{
		mode_str += "l";
		if(mode_arg != "")
			mode_arg += " ";
		mode_arg += Utils::itoa(server->getChannel(message.params[0])->get_maxusers());
	}
	if(mode_str != " +")
		msg += mode_str + " " + mode_arg;
	msg += Reply::endr;
	return(msg);

}

std::string Reply::RPL_CREATIONTIME_329(Server *server, Session *session, Channel *channel)
{
	Debug::Reply("RPL_CREATIONTIME(329)", session->getFdSocket());

	std::string msg = Utils::getServerPrefix(server, session, "329") + channel->get_name() + " " + channel->get_topic_user() +" "+  channel->getCreationTimeTs() + Reply::endr;
	return(msg);
}
std::string Reply::RPL_NOTOPIC_331(Server *server, Session *session, Channel *channel)
{
	Debug::Reply("RPL_NOTOPIC(331)", session->getFdSocket());

	std::string msg = Utils::getServerPrefix(server, session, "331") + channel->get_name() + " :No topic is set" + Reply::endr;
	return(msg);
}
std::string Reply::RPL_TOPIC_332(Server *server, Session *session, Channel *channel)
{
	Debug::Reply("RPL_TOPIC(332)", session->getFdSocket());

	std::string msg = Utils::getServerPrefix(server, session, "332") + channel->get_name() + " :" + channel->get_topic() + Reply::endr;
	return(msg);
}

std::string Reply::RPL_TOPICWHOTIME_333(Server *server, Session *session, Channel *channel)
{
	Debug::Reply("RPL_TOPICWHOTIME(333)", session->getFdSocket());

	std::string msg = Utils::getServerPrefix(server, session, "333") + channel->get_name() + " " + channel->get_topic_user() + " " + channel->get_topic_timestamp() +  Reply::endr;
	return(msg);
}
//target_channel || target_session, one should be NULL, if all are null, will send all the user of the server like a WHO 0
std::string Reply::RPL_WHOREPLY_352(Server *server, Session *session ,Channel *target_channel, Session *target_session)
{
	std::string msg;
	std::string flag = "H";
	Debug::Reply("RPL_WHOREPLY(352)", session->getFdSocket());
	if(target_channel != NULL && target_session != NULL)
	{
		Debug::Warning("Invalid use of Reply::RPL_WHOREPLY_352()");
		return("");
	}
	else if (target_channel == NULL && target_session == NULL) // For WHO 0 (Not support by HexChat but can be used by the bot)
	{
		std::map<int, Session*> sessions = server->getSessions();
		std::map<int, Session*>::iterator it;

		if (sessions.size() > 0)
		{
		    it = sessions.begin();
		    while (it != sessions.end())
		    {
				if(it->second != NULL)
				{
					flag = "H";
					if(it->second->getAwayStatus() != "")
						flag = "G";
					msg += Utils::getServerPrefix(server, session, "352") + "* " + it->second->getUserName() + " " + server->getHostName() + " " + server->getServerName() + " " + it->second->getNickName() + " " + flag + " :0 " + it->second->getRealName() + Reply::endr;
		        
				}
				++it;
				
		    }
		}
	}
	else if(target_session != NULL)
	{
		if(target_session->getAwayStatus() != "")
			flag = "G"; 
		msg += Utils::getServerPrefix(server, session, "352") + "* " + target_session->getUserName() + " " + server->getHostName() + " " + server->getServerName() + " " + target_session->getNickName() + " " + flag + " :0 " + target_session->getRealName() + Reply::endr;
	}
	else if(target_channel != NULL)
	{
		std::vector<std::string> users = target_channel->get_users();
		for(size_t i = 0; i < users.size(); i++)
		{
			flag = "H";
			if(server->getSession(users[i])->getAwayStatus() != "")
				flag = "G"; 
			if(target_channel->is_op(users[i]))
				flag += "@";
			msg += Utils::getServerPrefix(server, session, "352") + target_channel->get_name() + " " + server->getSession(users[i])->getUserName() + " " + server->getHostName() + " " + server->getServerName() + " " + server->getSession(users[i])->getNickName() + " " + flag + " :0 " + server->getSession(users[i])->getRealName() + Reply::endr;
		}
	}
	return(msg);
}

std::string Reply::RPL_NAMREPLY_353(Server *server, Session *session, Channel *channel)
{
	Debug::Reply("RPL_NAMREPLY(353)", session->getFdSocket());
	std::string msg = Utils::getServerPrefix(server,session,"353") + "= " + channel->get_name() + " :";
	std::vector<std::string> users = channel->get_users();
	for(size_t i = 0; i < users.size(); i++)
	{
		if(i == 0)
		{
			if(channel->is_op(users[i]))
				msg += "@" + users[i];
			else
				msg += users[i];

		}
		else
		{
			if(channel->is_op(users[i]))
				msg += " @" + users[i];
			else
				msg += " " + users[i];
		}

	}
	msg += Reply::endr;
	return(msg);
}

std::string Reply::RPL_ENDOFNAMES_366(Server *server, Session *session, std::string chan_name)
{
	Debug::Reply("RPL_ENDOFNAMES(366)", session->getFdSocket());
	std::string msg = Utils::getServerPrefix(server,session,"366") + chan_name + " :End of /NAMES list" + Reply::endr;

	return(msg);
}