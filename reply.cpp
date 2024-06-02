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

std::string Reply::RPL_STATSUPTIME_242(Server *server, Session *session)
{
	Debug::Reply("", session->getFdSocket());

	size_t day,hour,minute,second;
	server->getUptime(day,hour,minute,second);
	std::string msg = Utils::getServerPrefix(server,session, "242") + ":Server Up " + Utils::itoa(day) + " days " + Utils::itoa(hour) + ":" + Utils::itoa(minute) + ":" + Utils::itoa(second) + Reply::endr;
	return(msg);
}

std::string Reply::RPL_LUSERCLIENT_251(Server *server, Session *session)
{
	Debug::Reply("", session->getFdSocket());
	std::string msg = Utils::getServerPrefix(server,session, "251") + ":There are " + Utils::itoa(server->getActiveUsersNb()) + " users and 0 invisible on 1 servers" + Reply::endr;
	return(msg);
}
std::string Reply::RPL_LUSEROP_252(Server *server, Session *session)
{
	Debug::Reply("", session->getFdSocket());
	std::string msg = Utils::getServerPrefix(server,session, "252") + Utils::itoa(server->getOperatorUsersNb()) + " :operator(s) online" + Reply::endr;
	return(msg);
}
std::string Reply::RPL_LUSERUNKNOWN_253(Server *server, Session *session)
{
	Debug::Reply("", session->getFdSocket());
	std::string msg = Utils::getServerPrefix(server,session, "253") + Utils::itoa(server->getUnknownUsersNb()) + " :unknown connection(s)" + Reply::endr;
	return(msg);
}
std::string Reply::RPL_LUSERCHANNELS_254(Server *server, Session *session)
{
	Debug::Reply("", session->getFdSocket());
	std::string msg = Utils::getServerPrefix(server,session, "254") + Utils::itoa(server->getChannelsNb()) + " :channels formed" + Reply::endr;
	return(msg);
}
std::string Reply::RPL_LUSERME_254(Server *server, Session *session)
{
	Debug::Reply("", session->getFdSocket());
	std::string msg = Utils::getServerPrefix(server,session, "255") + ":I have " + Utils::itoa(server->getActiveUsersNb() + server->getUnknownUsersNb()) + " clients and 1 servers" + Reply::endr;
	return(msg);
}


std::string Reply::RPL_ADMINME_256(Server *server, Session *session, Server *target_server)
{
	Debug::Reply("RPL_ADMINME(256)", session->getFdSocket());

	std::string msg = Utils::getServerPrefix(server, session, "256") + target_server->getHostName() + " :Administrative info" +  Reply::endr;
	return(msg);
}
std::string Reply::RPL_ADMINLOC1_257(Server *server, Session *session, Server *target_server)
{
	Debug::Reply("RPL_ADMINLOC1(257)", session->getFdSocket());

	std::string msg = Utils::getServerPrefix(server, session, "257") + ":" + target_server->getHosterLocation() + Reply::endr;
	return(msg);
}
std::string Reply::RPL_ADMINLOC2_258(Server *server, Session *session, Server *target_server)
{
	Debug::Reply("RPL_ADMINLOC2(258)", session->getFdSocket());

	std::string msg = Utils::getServerPrefix(server, session, "258")  + ":" + target_server->getHosterOrganization() + Reply::endr;
	return(msg);
}
std::string Reply::RPL_ADMINEMAIL_259(Server *server, Session *session, Server *target_server)
{
	Debug::Reply("RPL_ADMINEMAIL(259)", session->getFdSocket());

	std::string msg = Utils::getServerPrefix(server, session, "259") + ":" + target_server->getHosterContact() + Reply::endr;
	return(msg);
}

std::string Reply::RPL_LOCALUSERS_265(Server *server, Session *session)
{
	Debug::Reply("RPL_LOCALUSERS(265)", session->getFdSocket());
	std::string msg = Utils::getServerPrefix(server, session, "265") + Utils::itoa(server->getActiveUsersNb()) + " " + Utils::itoa(server->getSessionMax()) +" :Current local users " + Utils::itoa(server->getActiveUsersNb()) + ", max " +  Utils::itoa(server->getSessionMax()) + Reply::endr;
	return(msg);
}

std::string Reply::RPL_AWAY_301(Server *server, Session *session, Message message)
{
	Debug::Reply("ERR_NOTEXTTOSNED(301)", session->getFdSocket());

	std::string msg = Utils::getServerPrefix(server, session, "301") + message.params[0] + " :" + session->getAwayStatus() + Reply::endr;
	return(msg);
}

std::string Reply::RPL_UNAWAY_305(Server *server, Session *session)
{
	Debug::Reply("RPL_UNAWAY(305)", session->getFdSocket());

	std::string msg = Utils::getServerPrefix(server, session, "305") + ":You are no longer marked as being away" + Reply::endr;
	return(msg);
}
std::string Reply::RPL_NOWAWAY_306(Server *server, Session *session)
{
	Debug::Reply("RPL_NOWAWAY(306)", session->getFdSocket());

	std::string msg = Utils::getServerPrefix(server, session, "306") + ":You have been marked as being away" + Reply::endr;
	return(msg);
}

std::string Reply::RPL_WHOISREGNICK_307(Server *server, Session *session, std::string nickname)
{
	Debug::Reply("RPL_WHOISREGNICK(307)", session->getFdSocket());
	std::string msg = Utils::getServerPrefix(server, session, "307") + nickname + " :has identified for this nick" + Reply::endr;
	return(msg);
}

std::string Reply::RPL_WHOISUSER_311(Server *server, Session *session, Session *target)
{
	Debug::Reply("RPL_WHOISUSER(311)", session->getFdSocket());
	std::string msg = Utils::getServerPrefix(server, session, "311") + target->getNickName() + " " + target->getUserName() + " " + server->getHostName() + " * :" + target->getRealName() + Reply::endr;
	return(msg);
}
std::string Reply::RPL_WHOISSERVER_312(Server *server, Session *session, Session *target)
{
	Debug::Reply("RPL_WHOISSERVER(312)", session->getFdSocket());
	std::string msg = Utils::getServerPrefix(server, session, "312") + target->getNickName() + " " + server->getHostName() + " :" + server->getInfo() + Reply::endr;
	return(msg);
}
std::string Reply::RPL_ENDOFWHO_315(Server *server, Session *session, Message message)
{
	Debug::Reply("RPL_ENDOFWHO(315)", session->getFdSocket());
	std::string msg;
	msg = Utils::getServerPrefix(server, session, "315") + message.params[0] + " :End of WHO list" + Reply::endr;
	return(msg);
}
std::string Reply::RPL_WHOISCHANNELS_319(Server *server, Session *session, Session *target)
{
	Debug::Reply("RPL_WHOISCHANNELS(319)", session->getFdSocket());
	if(target->getChannel() == NULL)
		return("");
	std::string op;
	if(target->getChannel()->is_op(target->getNickName()) == true)
		op = "@";
	std::string msg = Utils::getServerPrefix(server, session, "319") + target->getNickName() + " :" + op + target->getChannel()->get_name() + Reply::endr;
	return(msg);
}
std::string Reply::RPL_WHOISSPECIAL_320(Server *server, Session *session, Session *target)
{
	Debug::Reply("RPL_WHOISSPECIAL(320)", session->getFdSocket());
	std::string special = "All user cannot be server wide operator nor idle, this functionality is not supported";
	if(target->getNickName() == "edfirmin")
		special = "Some people says that I look like the donkey in Schreck, I'm not dubed by Eddie Murphy";
	if(target->getNickName() == "ggualerz")
		special = "Yes it's me who wrote terrible things on WHOIS cmd for edfirmin && ndesprez";
	if(target->getNickName() == "ndesprez")
		special = "I did a tmongell on this project, it's my repository but I will probably never read those lines";
	std::string msg;
	msg = Utils::getServerPrefix(server, session, "320") + target->getNickName() + " :" + special + Reply::endr;
	return(msg);
}

std::string Reply::RPL_LISTSTART_321(Server *server, Session *session)
{
	Debug::Reply("RPL_LISTSTART(321)", session->getFdSocket());

	std::string msg;
	msg = Utils::getServerPrefix(server, session, "321") + "Channel :Users  Name" + Reply::endr;
	return(msg);
}
std::string Reply::RPL_LIST_322(Server *server, Session *session, Channel *channel)
{
	Debug::Reply("RPL_LIST(322)", session->getFdSocket());

	std::string msg;
	std::string topic = channel->get_topic();
	if(topic == "")
		topic = "No topic set";
	msg = Utils::getServerPrefix(server, session, "322") + channel->get_name() + " " + Utils::itoa(channel->get_nmemb()) + " :" + topic + Reply::endr;
	return(msg);
}
std::string Reply::RPL_LISTEND_323(Server *server, Session *session)
{
	Debug::Reply("RPL_LISTEND(323)", session->getFdSocket());

	std::string msg;
	msg = Utils::getServerPrefix(server, session, "323") +  ":End of /LIST" + Reply::endr;
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
std::string Reply::RPL_INVITING_341(Server *server, Session *session, std::string nickname, std::string channel)
{
	Debug::Reply("RPL_INVITING(341)", session->getFdSocket());

	std::string msg = Utils::getServerPrefix(server, session, "341") + nickname + " " + channel +  Reply::endr;
	return(msg);
}
std::string Reply::RPL_VERSION_351(Server *server, Session *session, std::string server_name)
{
	Debug::Reply("RPL_VERSION(351)", session->getFdSocket());

	std::string msg = Utils::getServerPrefix(server, session, "351") + server->getVersion() + " " + server_name + " " + server->getVersionComments() +  Reply::endr;
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
std::string Reply::RPL_INFO_371(Server *server, Session *session, std::string info_str)
{
	Debug::Reply("RPL_INFO(371)", session->getFdSocket());
	std::string msg = Utils::getServerPrefix(server,session,"371") + ":" + info_str + Reply::endr;

	return(msg);
}
std::string Reply::RPL_MOTD_372(Server *server, Session *session, std::string motd_line)
{
	Debug::Reply("RPL_MOTD(372)", session->getFdSocket());
	std::string msg =  Utils::getServerPrefix(server,session,"372") + ":" + motd_line + Reply::endr;
	return(msg);
}
std::string Reply::RPL_ENDOFINFO_374(Server *server, Session *session)
{
	Debug::Reply("RPL_ENDOFINFO(374)", session->getFdSocket());
	std::string msg = Utils::getServerPrefix(server,session,"374") + ":End of INFO list" + Reply::endr;

	return(msg);
}
std::string Reply::RPL_MOTDSTART_375(Server *server, Session *session, std::string server_name)
{
	Debug::Reply("RPL_MOTDSTART(375)", session->getFdSocket());
	std::string msg =  Utils::getServerPrefix(server,session,"375") + ":- " + server_name + " Message of the day - " + Reply::endr;
	return(msg);
}
std::string Reply::RPL_ENDOFMOTD_376(Server *server, Session *session)
{
	Debug::Reply("RPL_ENDOFMOTD(376)", session->getFdSocket());
	std::string msg =  Utils::getServerPrefix(server,session,"376") + ":End of /MOTD command." + Reply::endr;
	return(msg);
}

std::string Reply::RPL_TIME_391(Server *server, Session *session, Server *target_srv)
{
	Debug::Reply("RPL_TIME(391)", session->getFdSocket());
	std::string msg =  Utils::getServerPrefix(server,session,"391") + target_srv->getHostName() + " " + Utils::getCurrentTimestamp() + " :" + Utils::getCurrentDate() + Reply::endr;
	return(msg);
}


std::string Reply::RPL_HELPSTART_704(Server *server, Session *session, std::string subject, std::string firstline)
{
	Debug::Reply("RPL_HELPSTART(704)", session->getFdSocket());
	std::string msg =  Utils::getServerPrefix(server,session,"704") + subject + " :###" + firstline + Reply::endr;
	return(msg);
}
std::string Reply::RPL_HELPTXT_705(Server *server, Session *session, std::string subject, std::string line)
{
	Debug::Reply("RPL_HELPTXT(705)", session->getFdSocket());
	std::string msg =  Utils::getServerPrefix(server,session,"705") + subject + " :" + line + Reply::endr;
	return(msg);
}
std::string Reply::RPL_ENDOFHELP_706(Server *server, Session *session, std::string subject, std::string lastline)
{
	Debug::Reply("RPL_ENDOFHELP(706)", session->getFdSocket());
	std::string msg =  Utils::getServerPrefix(server,session,"706") + subject + " :" + lastline + Reply::endr;
	return(msg);
}