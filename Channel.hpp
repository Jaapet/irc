#pragma once

# include <string>
# include <vector>
# include <algorithm>
# include <ctime>

# include "Session.hpp"

class Session;

class Channel
{
private :
	std::string	name;
	std::string	pw; // empty means no password
	std::string	topic; // Topic of the chan
	std::string topic_user; //who set the last the topic
	std::string topic_timestamp; // what time the topic was set
	std::string founder;
	size_t		max_users; // 0 means no limit
	bool		op_topic; // topic restrict
	bool		invite;

	std::vector<std::string>	users;
	std::vector<std::string>	operators;
	std::vector<std::string>	invited_users;

	void	remove_normal_user(Session &user);
	void	remove_operator(Session &user);
	std::string creation_time_ts;

public :
	Channel(const std::string &name, const std::string &founder_nick);
	~Channel();
	void	set_name(const std::string &name);
	void	set_pw(const std::string &pw);
	void	set_topic(const std::string &topic, const std::string &user);
	void	set_max_users(const size_t &max_users);
	void	set_op_topic(const bool &op_topic);
	void	set_invite(const bool &invite);
	void	set_founder(const std::string &nickname){this->founder = nickname;}

	std::string					get_name(void){return(name);}; //TOPIC
	std::string					get_topic(void){return(topic);}; //TOPIC
	std::string					get_topic_user(void){return(topic_user);}
	std::string						get_topic_timestamp(void){return(topic_timestamp);}
	std::vector<std::string>	get_users(void){return(users);}; //NAMES
	std::vector<std::string>	get_operators(void){return(operators);}; //OP
	std::string					get_founder(void){return(founder);}; //Founder
	size_t					get_nmemb(void){return(users.size());}; // Number of users
	std::string				get_pw(void){return (this->pw);}
	bool 					get_inviteonly(void){return(this->invite);}
	bool 					get_topicrestricted(void){return(this->op_topic);}
	size_t					get_maxusers(void){return (this->max_users);}
	bool					getUserInvited(std::string const &nickname);
	bool						is_op(std::string const &nickname);
	bool						is_user(std::string const &nickname);
	size_t					getMaxUsers(void){return(this->max_users);}
	std::string				getCreationTimeTs(void){return(this->creation_time_ts);}

	int		add_user(std::string const &nickname); //JOIN ; 0 if ok, 1 if not invited, 2 if already, 3 if full
	void	add_op(std::string const &nickname){this->operators.push_back(nickname);}
	void	rm_op(std::string const &nickname);
	bool	rm_user(std::string const &nickname); //PART ; KICK ; false if user not in chan
	void	invite_user(std::string const &nickname); //INVITE
	void	clear_invite(void)
		{this->invited_users.clear();}
	bool	checkPw(std::string const &pw_to_try)
		{return(this->pw == pw_to_try);}

};
