#pragma once
#include <string>
#include "Session.hpp"

namespace Reply
{
	extern const std::string endr;
	std::string getPrefix(Server *server, Session *session, std::string rep_code);

	std::string RPL_WELCOME_001(Server *server, Session *session);
};