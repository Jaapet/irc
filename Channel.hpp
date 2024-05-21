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
	bool		op_topic; // ?
	bool		invite;

	std::vector<std::string>	users;
	std::vector<std::string>	operators;

	void	remove_normal_user(Client &user);
	void	remove_operator(Client &user);

public :
	Channel(const std::string &name);

	void	set_name(const std::string &name);
	void	set_pw(const std::string &pw);
	void	set_topic(const std::string &topic);
	void	set_max_users(const u_int16_t &max_users);
	void	set_op_topic(const bool &op_topic);
	void	set_invite(const bool &invite);
};
