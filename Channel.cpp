#include "Channel.hpp"

Channel::Channel (std::string const &name)
{
	this->name = name;
	this->op_topic = false;
	this->invite = false;
}

void	Channel::set_name(const std::string &name)
{
	this->name = name;
}

void	Channel::set_pw(const std::string &pw)
{
	this->pw = pw;
}

void	Channel::set_topic(const std::string &topic)
{
	this->topic = topic;
}

void	Channel::set_max_users(const u_int16_t &max_users)
{
	this->max_users = max_users;
}

void	Channel::set_op_topic(const bool &op_topic)
{
	this->op_topic = op_topic;
}

void	Channel::set_invite(const bool &invite)
{
	this->invite = invite;
}
