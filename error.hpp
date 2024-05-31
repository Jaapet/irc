#pragma once
#include <string>
#include "Session.hpp"
#include "reply.hpp"
#include "Message.hpp"

struct Message;

namespace Error
{
	std::string ERR_NOSUCHNICK_401(Server *server, Session *session, Message message);
	std::string ERR_NOSUCHSERVER_402(Server *server, Session *session, Message message);
	std::string ERR_NOSUCHCHANNEL_403(Server *server, Session *session, Message message);
	std::string ERR_CANNOTSENDTICHAN_404(Server *server, Session *session, Message message);
	std::string ERR_TOOMANYCHANNELS_405(Server *server, Session *session, Message message);
	std::string ERR_TOOMANYTARGETS_407(Server *server, Session *session, Message message);
	std::string ERR_NORECIPIENT_411(Server *server, Session *session, Message message);
	std::string ERR_NOTEXTTOSNED_412(Server *server, Session *session, Message message);
	std::string ERR_UNKNOWNCOMMAND_421(Server *server, Session *session, Message message);
	std::string ERR_ERRONEUSNICKNAME_432(Server *server, Session *session, Message message);
	std::string ERR_NICKNAMEINUSE_433(Server *server, Session *session, Message message);
	std::string ERR_NOTONCHANNEL_442(Server *server, Session *session, Message message);
	std::string ERR_NEEDMOREPARAMS_461(Server *server, Session *session, Message message);
	std::string ERR_ALREADYREGISTRED_462(Server *server, Session *session);
	std::string ERR_PASSWDMISMATCH_464(Server *server, Session *session);
	std::string ERR_CHANNELISFULL_471(Server *server, Session *session, std::string &chan_name);
	std::string ERR_INVITEONLYCHAN_473(Server *server, Session *session, std::string &chan_name);
	std::string ERR_BADCHANNELKEY_475(Server *server, Session *session, std::string &chan_name);
	std::string ERR_BADCHANMASK_476(Server *server, Session *session, std::string &chan_name);
	std::string ERR_NOPRIVILEGES_481(Server *server, Session *session, Message message);
	std::string ERR_CHANOPRIVSNEEDED_482(Server *server, Session *session, std::string &chan_name);
	std::string ERR_UMODEUNKNOWNFLAG_501(Server *server, Session *session);
	std::string ERR_INVALIDMODEPARAM_696(Server *server, Session *session, Message *message,std::string description);

}