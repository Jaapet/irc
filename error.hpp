#pragma once
#include <string>
#include "Session.hpp"
#include "reply.hpp"

namespace Error
{
	void ERR_ALREADYREGISTRED_462(Server *server, Session *session);
	void ERR_PASSWDMISMATCH_464(Server *server, Session *session);
};