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

//-----------------------------------------------------------------------------------------------

bool	Channel::is_op(std::string const &nickname)
{
	for (int i = 0; i < this->operators.size(); i++)
	{
		if (this->operators[i] == nickname)
			return (true);
	}
	return (false);
}


//-----------------------------------------------------------------------------------------------

bool	Channel::add_user(std::string const &nickname)
{
	if (this->invite && *std::find(this->invited_users.begin(), this->invited_users.end(), nickname) != nickname)
		return (1);
	if (*std::find(this->users.begin(), this->users.end(), nickname) == nickname)
		return (2);
	if (this->users.size() >= this->max_users)
		return (3);
	this->users.push_back(nickname);
	return (0);
}

bool	Channel::rm_user(std::string const &nickname)
{
	std::string temp;

	for (int i = 0; i < this->users.size(); i++)
	{
		if (this->users[i] == nickname)
		{
			this->users[i] = this->users[get_nmemb() - 1];
			this->users[get_nmemb() - 1] = nickname;
			this->users.pop_back();
			return (true);
		}
	}
	return (false);
}

void	Channel::invite_user(std::string const &nickname)
{
	for (int i = 0; i < this->invited_users.size(); i++)
	{
		if (this->invited_users[i] == nickname)
			return ;
	}
	this->invited_users.push_back(nickname);
}
