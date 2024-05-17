#include "debug.hpp"

void Debug::Info(std::string const &msg)
{
	std::cout << WHITE <<"INFO:\t\t" << msg << RESET << std::endl;
}
void Debug::Success(std::string const &msg)
{
	std::cout << GREEN <<"SUCCESS:\t" << msg << RESET << std::endl;
}
void Debug::Warning(std::string const &msg)
{
	std::cout << YELLOW <<"WARN:\t\t" << msg << RESET << std::endl;
}
void Debug::Error(std::string const &msg)
{
	std::cerr << RED <<"PANIC:\t" << msg << RESET << std::endl;
}