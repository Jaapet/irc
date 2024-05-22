#include "debug.hpp"
#include "error.hpp"

// send(i, msg.c_str(), msg.length(), 0);
std::string Error::ERR_ALREADYREGISTRED_462(Server *server, Session *session)
{
	Debug::Reply("ERR_ALREADYREGISTRED(462)", session->getFdSocket());

	std::string msg = Reply::getPrefix(server, session, "462") + ":You may not reregister" + Reply::endr;
	return(msg);	
}
std::string Error::ERR_PASSWDMISMATCH_464(Server *server, Session *session)
{
	Debug::Reply("ERR_PASSWDMISMATCH_464", session->getFdSocket());

	std::string msg = Reply::getPrefix(server, session, "464") + ":Password incorrect" + Reply::endr;
	return(msg);
}