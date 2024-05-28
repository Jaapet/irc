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

//Find the char c before # or the last & char
bool Utils::findFlag(const std::string& str, char c) 
{
    // Find the position of the first '#' character
    size_t pos_hash = str.find('#');
    // Find the position of the last '&' character
    size_t pos_ampersand = str.rfind('&');
    
    // Determine the position to search until
    size_t pos_end = std::min(pos_hash, pos_ampersand);
    
    // Search for the character 'c' within the substring before '#' or the last '&'
    return str.substr(0, pos_end).find(c) != std::string::npos;
}
bool Utils::findChar(std::string &str, char &c)
{
	    return str.find(c) != std::string::npos;
}
void Utils::removeDuplicatesStr(std::vector<std::string>& vec) 
{
    // Sort the vector
    std::sort(vec.begin(), vec.end());

    // Remove adjacent duplicates
    vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
}
//channel should contain the prefix ~#&...
void Utils::sendToChannel(Server *server, Channel *channel, std::string &msg, std::string &channelname_with_flags_from_msg)
{
	bool is_op = Utils::findFlag(channelname_with_flags_from_msg, '@');
	bool is_protected = Utils::findFlag(channelname_with_flags_from_msg, '&');
	bool is_founder = Utils::findFlag(channelname_with_flags_from_msg, '~');
	std::vector<std::string> lst_user;
	if(is_founder == false && is_protected == false && is_op == false)
		lst_user = channel->get_users();	
	// else
	// {
	// 	if(is_op)
	// 	{
	// 		std::vector<std::string> ops = channel->getOps();
	// 		lst_user.insert(lst_user.end(), ops.begin(), ops.end());
	// 	}
	// 	if(is_protected)
	// 	{
	// 		std::vector<std::string> prot = channel->getProtected();
	// 		lst_user.insert(lst_user.end(), prot.begin(), prot.end());
	// 	}
	// 	if(is_founder)
	// 	{
	// 		lst_user.push_back(channel->getFounder());
	// 	}
	// }
	// Utils::removeDuplicatesStr(lst_user);
	if(channel)
	{
		for(size_t i = 0; i < lst_user.size(); i++)
		{
			server->getSession(lst_user[i])->addSendBuffer(msg);
		}
	}
}