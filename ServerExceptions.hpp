#pragma once
#include <exception>

class SocketCreationError : public std::exception {
	public:
	const char *what() const throw()
	{
		return("Cannot create the socket");
	}
};
class SocketBindingError : public std::exception {
	public:
	const char *what() const throw()
	{
		return("Cannot bind the socket");
	}
};
class SocketListenError : public std::exception {
	public:
	const char *what() const throw()
	{
		return("Cannot listen");
	}
};
class SelectCallError : public std::exception {
	public:
	const char *what() const throw()
	{
		return("Cannot call select()");
	}
};
class SessionCreationError : public std::exception {
	public:
	const char *what() const throw()
	{
		return("Cannot create a session");
	}
};

class DuplicatedSessionFd : public std::exception {
	public:
	const char *what() const throw()
	{
		return("Duplicate session fd or a ghost session");
	}
};

class BotCreationFail : public std::exception {
	public:
	const char *what() const throw()
	{
		return("Bot connection to the serv. fail");
	}
};
