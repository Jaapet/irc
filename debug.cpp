#include "Server.hpp"
#include "debug.hpp"
#include <iomanip>


void Debug::Info(std::string const &msg)
{
	if(VERBOSE)
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
	if(VERBOSE)
		std::cout << CYAN <<"[FROM USER_FD=" << session_fd << "]: " << msg << RESET << std::endl;
}

void Debug::Reply(std::string const &repcode, int session_fd)
{
	if(VERBOSE)
		std::cout << MAGENTA <<"[TO USER_FD=" << session_fd << "]: " << repcode << RESET << std::endl;
}

void Debug::Header(void)
{
	std::string header;
header = "\n\t\t\t\t\t\tMay 2024\n\
\t  _ _____   _____ \n\
\t (_)  __ \\ / ____|\n\
\t  _| |__) | |     \n\
\t | |  _  /| |     \n\
\t | | | \\ \\| |____ \n\
\t |_|_|  \\_\\_____|\t@edfirmin\t@ggualerz\t@ndesprez\n\
                  \n";
	std::cout <<"\033[1m" << GREEN << header << RESET << "\033[0m" << std::endl;
}