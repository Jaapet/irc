#include "debug.hpp"

void Debug::Info(std::string const &msg)
{
	std::cout << WHITE <<"[INFO]: " << msg << RESET << std::endl;
}
void Debug::Success(std::string const &msg)
{
	std::cout << GREEN <<"[SUCCESS]: " << msg << RESET << std::endl;
}
void Debug::Warning(std::string const &msg)
{
	std::cout << YELLOW <<"[WARN]: " << msg << RESET << std::endl;
}
void Debug::Error(std::string const &msg)
{
	std::cerr << RED <<"[PANIC]: " << msg << RESET << std::endl;
}

void Debug::Message(std::string const &msg, int session_fd)
{
	std::cout << CYAN <<"[FROM USER_FD=" << session_fd << "]: " << msg << RESET << std::endl;
}

void Debug::Reply(std::string const &repcode, int session_fd)
{
	std::cout << MAGENTA <<"[TO USER_FD=" << session_fd << "]: " << repcode << RESET << std::endl;
}