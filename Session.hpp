#pragma once

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include "Server.hpp"

#include "Channel.hpp"

#include <ctime>

class Channel;


class Server;

class Session
{
private:
	Server const *_server;

	bool _authenticated;
	bool _pass_is_set;
	std::string _username;
	bool _user_is_set;
	std::string _nickname;
	bool _nick_is_set;
	std::string _realname;
	bool _realname_is_set;
	std::string _sendBuffer;
	bool		_waitpong;
	std::time_t _lastpong;
	std::string	_away_status;

	Channel	*channel;
	//.. Add whatever you need

public:
	int	_fd_socket; // (Session/Client) a socket is basically a file descriptor++, fd in public because accept func have to acess it
	struct sockaddr_in _address_socket; // (Session/Client) struct who contain socket info in public because accept func have to acess it
	
	Session(Server const *server_ptr);
	~Session();

	//Getters
		//Basic info
		std::string	const getAwayStatus(void) const
			{return (this->_away_status);}
		bool getAuthenticated(void) const
			{return (this->_authenticated);}
		bool getPassIsSet(void) const
			{return (this->_pass_is_set);}
		std::string const &getUserName(void) const
			{return(this->_username);}
		bool getUserNameIsSet(void) const
			{return (this->_user_is_set);}
		std::string const &getNickName(void) const
			{return(this->_nickname);}
		bool getNickNameIsSet(void) const
			{return (this->_nick_is_set);}
		std::string const &getRealName(void) const
			{return(this->_realname);}
		bool getRealNameIsSet(void) const
			{return (this->_realname_is_set);}
		bool getWaitPong(void)
			{return(this->_waitpong);}
		Channel *getChannel(void)
			{return(this->channel);}
		//Socket info
		socklen_t getLenSocket(void) const
			{return (sizeof(_address_socket));}
		int const &getFdSocket(void) const
			{return (this->_fd_socket);}
		std::string &getSendBuffer(void)
			{return(this->_sendBuffer);}
	//Setters
	void setPassTrue(void)
		{this->_pass_is_set = true;}
	void setNickName(std::string const &nickname)
		{this->_nickname = nickname; this->_nick_is_set = true;;}
	void setUserName(std::string const &username)
		{this->_username = username; this->_user_is_set = true;}
	void setRealName(std::string const &realname)
		{this->_realname = realname; this->_realname_is_set = true;}
	void setWaitPong(void)
		{this->_waitpong = true;}
	void setChannel(Channel *channel)
		{this->channel = channel;}

	bool authenticate(void); //Every time this method is call it check if everything is meet for completing the auth; then return the correct 4 REPL



	// int							join_chan(Channel &chan, std::string &pass); //JOIN ; 0 if ok, 1 if not invited, 2 if already, 3 if full
	// bool						quit_chan(Channel &chan); //PART ; KICK ; false if user not in chan
	// void						set_topic(Channel &chan, std::string &topic); //TOPIC ; if empty string, clears the topic
	// std::string					get_topic(Channel &chan); //TOPIC
	// std::vector<std::string>	names_chan(Channel &chan); //NAMES
	// void						get_invited(Channel &chan); //INVITE
	// void						invite(Session &user, Channel &chan); //INVITE


	void newPong()
		{this->_lastpong = std::time(NULL); this->_waitpong = false;}
	void addSendBuffer(std::string &str)
	{
		this->_sendBuffer += str;
	}

};


