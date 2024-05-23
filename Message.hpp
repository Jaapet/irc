#pragma once
#include <string>
#include <vector>

struct Message
{
	std::string sender;
    std::string command;
    std::vector<std::string> params;
    std::string payload;

	Message();
	void clear();
};

//sender PASS param1 param2 :payload payload