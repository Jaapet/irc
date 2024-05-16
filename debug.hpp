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
	void Info(std::string const &msg)
	{
		std::cout << WHITE <<"INFO:\t\t" << msg << RESET << std::endl;
	}

	void Success(std::string const &msg)
	{
		std::cout << GREEN <<"SUCCESS:\t" << msg << RESET << std::endl;
	}

	void Warning(std::string const &msg)
	{
		std::cout << YELLOW <<"WARN:\t\t" << msg << RESET << std::endl;
	}

	void Error(std::string const &msg)
	{
		std::cout << RED <<"PANIC:\t" << msg << RESET << std::endl;
	}
}