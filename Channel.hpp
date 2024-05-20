#pragma once

# include <string>
# include <vector>
# include <algorithm>

class Channel
{
private :
	std::string	name;
	std::string	pw; // empty means no password
	std::string	topic; // ?
	u_int16_t	max_users; // 0 means no limit
	bool		_op_topic; // ?
	bool		invite;

	std::vector<std::string>	_users;
	std::vector<std::string>	_operators;

	void	remove_normal_user(Client &user);
	void	remove_operator(Client &user);

public :
	Channel(const std::string &name);

};