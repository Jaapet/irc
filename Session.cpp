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
	this->channel = NULL;
	this->_away_status = "";
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

// int	Session::join_chan(Channel &chan, std::string &pass)
// {
// 	return (chan.add_user(this->_nickname));
// }

// bool	Session::quit_chan(Channel &chan)
// {
// 	return (chan.rm_user(this->_nickname));
// }

// void	Session::set_topic(Channel &chan, std::string &topic)
// {
// 	chan.set_topic(topic);
// }

// std::string	Session::get_topic(Channel &chan)
// {
// 	return (chan.get_topic());
// }

// std::vector<std::string>	Session::names_chan(Channel &chan)
// {
// 	return (chan.get_users());
// }

// void	Session::get_invited(Channel &chan)
// {
// 	chan.invite_user(this->_nickname);
// }

// void	Session::invite(Session &user, Channel &chan)
// {
// 	user.get_invited(chan);
// }
