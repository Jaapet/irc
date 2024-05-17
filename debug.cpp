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
	std::cerr << CYAN <<"[USER " << session_fd << "]: " << msg << RESET;
}