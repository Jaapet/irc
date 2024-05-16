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

class Server;

class Session
{
private:
	Server const *_server;
	

	std::string _username;
	std::string _nickname;
	std::string _realname;

	//.. Add whatever you need

public:
	int	_fd_socket; // (Session/Client) a socket is basically a file descriptor++, fd in public because accept func have to acess it
	struct sockaddr_in _address_socket; // (Session/Client) struct who contain socket info in public because accept func have to acess it
	
	Session(Server const *server_ptr);
	~Session();

	socklen_t getLenSocket(void) const
		{return (sizeof(_address_socket));}
	int const &getFdSocket(void) const
		{return (this->_fd_socket);}
	//DO YOUR OWN GETTERS
	// ...
	//
	

};


