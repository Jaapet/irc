#include "Session.hpp"

Session::Session(Server const *server_ptr): _server(server_ptr)
{
	this->_pass_is_set = false;
	this->_nick_is_set = false;
	this->_realname_is_set = false;
	this->_user_is_set = false;


	//DEBUG
	this->_nickname = "foo";
}

Session::~Session()
{
}