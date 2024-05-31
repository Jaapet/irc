#pragma once
#include <string>
#include "Session.hpp"
#include "Message.hpp"

struct Message;

namespace Reply
{
	extern const std::string endr;
	
	std::string PING_SERVER(Server *server, Session *session, Message message);

	std::string RPL_WELCOME_001(Server *server, Session *session, Message message);
	std::string RPL_YOURHOST_002(Server *server, Session *session, Message message);
	std::string RPL_CREATED_003(Server *server, Session *session, Message message);
	std::string RPL_MYINFO_004(Server *server, Session *session, Message message);
	std::string RPL_AWAY_301(Server *server, Session *session, Message message);
	std::string RPL_ENDOFWHO_315(Server *server, Session *session, Message message);
	std::string RPL_CHANNELMODEIS_324(Server *server, Session *session, Message message);
	std::string RPL_CREATIONTIME_329(Server *server, Session *session, Channel *channel);
	std::string RPL_NOTOPIC_331(Server *server, Session *session, Channel *channel);
	std::string RPL_TOPIC_332(Server *server, Session *session, Channel *channel);
	std::string RPL_TOPICWHOTIME_333(Server *server, Session *session, Channel *channel);
	std::string RPL_WHOREPLY_352(Server *server, Session *session ,Channel *target_channel, Session *target_session);
	std::string RPL_NAMREPLY_353(Server *server, Session *session, Channel *channel);
	std::string RPL_ENDOFNAMES_366(Server *server, Session *session, std::string chan_name);

}