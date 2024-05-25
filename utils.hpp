#pragma once

#include <string>
#include <ctime>

namespace Utils
{
	std::string removeCRLF(std::string const &str);

	std::string strToUpper(std::string const &str);

	std::string getCurrentDate(void);

}
