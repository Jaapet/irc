#include "utils.hpp"

std::string Utils::removeCRLF(std::string const &str)
{
	std::string out = str;

	if (!out.empty() && (out[out.size() - 1] == '\n' || out[out.size() - 1] == '\r')) {
        out.erase(out.size() - 1);
    }
    if (!out.empty() && (out[out.size() - 1] == '\n' || out[out.size() - 1] == '\r')) {
        out.erase(out.size() - 1);
    }
	return(out);
}

std::string Utils::strToUpper(std::string const &str)
{
	std::string out = str;

	for (std::string::iterator it = out.begin(); it != out.end(); ++it) 
	{
		*it = std::toupper(*it);
    }

	return(out);
}

std::string Utils::getCurrentDate(void)
{
	// Get the current time as a time_t object
    std::time_t currentTime = std::time(NULL);
    // Convert to local time representation
    std::tm* localTime = std::localtime(&currentTime);
    // Buffer to hold the formatted date string
    char dateString[100];
    // Format the date into a human-readable string
    // Format specifiers:
    // %Y - year with century
    // %m - month (01-12)
    // %d - day of the month (01-31)
    // %H - hour (00-23)
    // %M - minute (00-59)
    // %S - second (00-60)
    std::strftime(dateString, sizeof(dateString), "%Y-%m-%d %H:%M:%S", localTime);
    return (dateString);
}

bool Utils::isAllowedNickCharacter(char const c)
{
	return (isalnum(c) || c == '[' || c == ']' || c == '{' || c == '}' || c == '\\' || c == '|' || c == '_' || c == '-');
}

std::string Utils::getUserPrefix(Server *server, Session *session)
{
	std::string prefix;
	prefix = ":" + session->getNickName() + "!" + session->getUserName() + "@" + server->getHostName() + " ";
	return(prefix);
}

std::string Utils::getServerPrefix(Server *server, Session *session, std::string rep_code)
{
	std::string prefix;
	prefix = ":" + server->getHostName() + " " + rep_code + " " + session->getNickName() + " ";
	return(prefix);
}
