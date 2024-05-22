#pragma once
#include <string>
#include "Session.hpp"
#include "reply.hpp"

namespace Error
{
	std::string ERR_ALREADYREGISTRED_462(Server *server, Session *session);
	std::string ERR_PASSWDMISMATCH_464(Server *server, Session *session);
};