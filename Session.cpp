#include "Session.hpp"
#include "reply.hpp"

Session::Session(Server const *server_ptr): _server(server_ptr), _username("*"), _nickname("*"), _realname("*")
{
	this->_authenticated = false;
	this->_pass_is_set = false;
	this->_nick_is_set = false;
	this->_realname_is_set = false;
	this->_user_is_set = false;
	this->_sendBuffer.clear();
	this->_lastpong = 0;
	this->_channel = NULL;
}

Session::~Session()
{
}

bool Session::authenticate(void)
{
	if(this->_nick_is_set && this->_user_is_set && this->_realname_is_set)
	{
		this->_authenticated = true;
		return(true);
	}
	return(false);

	
}
