#pragma once

# include <string>
# include <vector>
# include <algorithm>

# include "Session.hpp"

class Session;

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
	std::vector<std::string>	invited_users;

	void	remove_normal_user(Session &user);
	void	remove_operator(Session &user);

public :
	Channel(const std::string &name);

	void	set_name(const std::string &name);
	void	set_pw(const std::string &pw);
	void	set_topic(const std::string &topic); //TOPIC ; if empty string, clears the topic
	void	set_max_users(const u_int16_t &max_users);
	void	set_op_topic(const bool &op_topic);
	void	set_invite(const bool &invite);

	std::string					get_topic(void){return(topic);}; //TOPIC
	std::vector<std::string>	get_users(void){return(users);}; //NAMES
	u_int16_t					get_nmemb(void){return(users.size());}; //LIST ; timestamp ?
	bool						is_op(std::string const &nickname);

	int		add_user(std::string const &nickname); //JOIN ; 0 if ok, 1 if not invited, 2 if already, 3 if full
	bool	rm_user(std::string const &nickname); //PART ; KICK ; false if user not in chan
	void	invite_user(std::string const &nickname); //INVITE

	

};
