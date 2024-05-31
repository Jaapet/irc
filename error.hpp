#pragma once
#include <string>
#include "Session.hpp"
#include "reply.hpp"
#include "Message.hpp"

struct Message;

namespace Error
{
	std::string ERR_ERRONEUSNICKNAME_432(Server *server, Session *session, Message message);
	std::string ERR_NICKNAMEINUSE_433(Server *server, Session *session, Message message);
	std::string ERR_NEEDMOREPARAMS_461(Server *server, Session *session, Message message);
	std::string ERR_ALREADYREGISTRED_462(Server *server, Session *session);
	std::string ERR_PASSWDMISMATCH_464(Server *server, Session *session);
	std::string ERR_CANNOTSENDTICHAN_404(Server *server, Session *session, Message message);
	std::string ERR_NOSUCHNICK_401(Server *server, Session *session, Message message);
	std::string ERR_TOOMANYTARGETS_407(Server *server, Session *session, Message message);
	std::string ERR_NORECIPIENT_411(Server *server, Session *session, Message message);
	std::string ERR_NOTEXTTOSNED_412(Server *server, Session *session, Message message);
	std::string RPL_AWAY_301(Server *server, Session *session, Message message);
	std::string ERR_NOSUCHSERVER_402(Server *server, Session *session, Message message);
	std::string ERR_NOPRIVILEGES_481(Server *server, Session *session, Message message);
}