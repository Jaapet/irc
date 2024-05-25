
#pragma once

#include <iostream>
#include <string>
#include <map>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#include "Channel.hpp"
#include "Session.hpp"
#include "Message.hpp"

#include "command.hpp"
#include "debug.hpp"
#include "utils.hpp"

#define BUFFER_SIZE  512
#define BACKLOG  10

struct Message;

class Session;

class Server
{
private:
	#include "ServerExceptions.hpp"

	int	_fd_socket; // (Server) a socket is basically a file descriptor++
	struct sockaddr_in _address_socket; // (Server) struct who contain socket info

	// Not used outside of server class no need for getters
	fd_set _read_sessions_fd;
	fd_set _write_sessions_fd;
	timeval _select_timeout;
	//
	std::string _hostname; // hostname of the irc server
	std::string _password; // password to join the server, no getter for obvious reasons
	uint16_t	_port; // uint16_t for unsigned int of 16 bit  0 to 65535 because a port can only be in this range according to the OS
	std::string _servername;
	std::string _networkname;
	std::string _version;//Set in constructor IDK wtf we should put
	std::string _available_user_modes;
	std::string _available_channel_modes;
	std::string _creation_date;

	bool _should_i_end_this_suffering; //Bool set to true to kill the server
	

	// std::map<std::string, Channel> _channels; // map of the channels, channel name is the key of the map, vallue is the object channel
	std::map<int, Session *> _sessions; //map of the sessions, session fd is the key
	typedef std::string (*CommandPtr)(Server *, Session *, Message );
	std::map<std::string, CommandPtr > _commands;
	
	//init method, should only be called by constructor
	void createSocket(void);
	void bindSocket(void);
	void launchListen(void);
	void initSessionsFds(void);
	void mapCommands(void);
	void handleConnections(void);
	void handleNewSession(int &fd_max);
	void handleReadEvents(int cur_fd);
	void executeCommands(std::vector<std::string> command_to_execute, int cur_fd);
	void handleWriteEvents( int cur_fd);
	
public:
	Server(std::string hostname, std::string pwd, uint16_t port);
	~Server();

	//Getters
		//Basic info
		std::string const &getHostName(void) const
			{return (this->_hostname);}
		uint16_t const &getPort(void) const
			{return (this->_port);}
		std::string const &getServerName(void) const
			{return (this->_servername);}
		std::string const &getNetworkName(void) const
			{return (this->_networkname);}
		std::string const &getVersion(void) const
			{return (this->_version);}
		std::string const &getAvailableUserModes(void) const
			{return (this->_available_user_modes);}
		std::string const &getAvailableChannelModes(void) const
			{return (this->_available_channel_modes);}
		std::string const &getCreationDate(void) const
			{return (this->_creation_date);}
		bool getKill(void) const
			{return (this->_should_i_end_this_suffering);}
		//Socket
		int	const &getFdSocket(void) const
			{return (this->_fd_socket);}
		sockaddr_in const &getAddressSocket(void) const
			{return (this->_address_socket);}
		socklen_t getLenSocket(void) const
			{return(sizeof(this->_address_socket));}
		//Misc
		int  getBufferSize(void) const
			{return (BUFFER_SIZE);}
		int  getBackLog(void) const
			{return (BACKLOG);}
		
	//Setters

	//Methods
		//Sessions
		void setNonBlockingFd(int fd);
		bool checkPassword(std::string passwordToCheck) const
			{return (passwordToCheck == this->_password);}
		void killSession(int const session_fd);
		Session *getSession(std::string const &nickname);
		//Messages
		std::vector<std::string>    splitBuffer(std::string const &str);
		void parseMessage(const std::string &message, Message &outmessage);
};