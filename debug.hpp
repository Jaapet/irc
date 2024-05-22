#pragma once
#include <iostream>
#include <iostream>
#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */

namespace Debug
{
	void Info(std::string const &msg);

	void Success(std::string const &msg);

	void Warning(std::string const &msg);

	void Error(std::string const &msg);

	void Message(std::string const &msg, int session_fd);

	void Reply(std::string const &repcode, int session_fd);
}