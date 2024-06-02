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
	std::string RPL_STATSUPTIME_242(Server *server, Session *session);
	std::string RPL_LUSERCLIENT_251(Server *server, Session *session);
	std::string RPL_LUSEROP_252(Server *server, Session *session);
	std::string RPL_LUSERUNKNOWN_253(Server *server, Session *session);
	std::string RPL_LUSERCHANNELS_254(Server *server, Session *session);
	std::string RPL_LUSERME_254(Server *server, Session *session);


	std::string RPL_ADMINME_256(Server *server, Session *session, Server *target_server);
	std::string RPL_ADMINLOC1_257(Server *server, Session *session, Server *target_server);
	std::string RPL_ADMINLOC2_258(Server *server, Session *session, Server *target_server);
	std::string RPL_ADMINEMAIL_259(Server *server, Session *session, Server *target_server);
	std::string RPL_LOCALUSERS_265(Server *server, Session *session);
	std::string RPL_AWAY_301(Server *server, Session *session, Message message);
	std::string RPL_UNAWAY_305(Server *server, Session *session);
	std::string RPL_NOWAWAY_306(Server *server, Session *session);
	std::string RPL_WHOISREGNICK_307(Server *server, Session *session, std::string nickname);
	std::string RPL_WHOISUSER_311(Server *server, Session *session, Session *target);
	std::string RPL_WHOISSERVER_312(Server *server, Session *session, Session *target);
	std::string RPL_WHOISSERVER_312(Server *server, Session *session, Session *target);
	std::string RPL_WHOISCHANNELS_319(Server *server, Session *session, Session *target);
	std::string RPL_WHOISSPECIAL_320(Server *server, Session *session, Session *target);

	std::string RPL_ENDOFWHO_315(Server *server, Session *session, Message message);
	std::string RPL_LISTSTART_321(Server *server, Session *session);
	std::string RPL_LIST_322(Server *server, Session *session, Channel *channel);
	std::string RPL_LISTEND_323(Server *server, Session *session);
	std::string RPL_CHANNELMODEIS_324(Server *server, Session *session, Message message);
	std::string RPL_CREATIONTIME_329(Server *server, Session *session, Channel *channel);
	std::string RPL_NOTOPIC_331(Server *server, Session *session, Channel *channel);
	std::string RPL_TOPIC_332(Server *server, Session *session, Channel *channel);
	std::string RPL_TOPICWHOTIME_333(Server *server, Session *session, Channel *channel);
	std::string RPL_INVITING_341(Server *server, Session *session, std::string nickname, std::string channel);
	std::string RPL_VERSION_351(Server *server, Session *session, std::string server_name);
	std::string RPL_WHOREPLY_352(Server *server, Session *session ,Channel *target_channel, Session *target_session);
	std::string RPL_NAMREPLY_353(Server *server, Session *session, Channel *channel);
	std::string RPL_ENDOFNAMES_366(Server *server, Session *session, std::string chan_name);

	std::string RPL_INFO_371(Server *server, Session *session, std::string info_str);
	std::string RPL_MOTD_372(Server *server, Session *session, std::string motd_line);
	std::string RPL_ENDOFINFO_374(Server *server, Session *session);
	std::string RPL_MOTDSTART_375(Server *server, Session *session, std::string server_name);
	std::string RPL_ENDOFMOTD_376(Server *server, Session *session);
	std::string RPL_TIME_391(Server *server, Session *session, Server *target_srv);

	std::string RPL_HELPSTART_704(Server *server, Session *session, std::string subject, std::string firstline);
	std::string RPL_HELPTXT_705(Server *server, Session *session, std::string subject, std::string line);
	std::string RPL_ENDOFHELP_706(Server *server, Session *session, std::string subject, std::string lastline);

}