#include "Server.hpp"
#include <unistd.h>
#include <csignal>
#include <cstring>

volatile sig_atomic_t ctrlc_pressed = 0;

bool checkColumn(char *str)
{
	int colonCount = 0;
	for (int i = 0; str[i] != '\0'; ++i) 
	{
        if (str[i] == ':') {
            colonCount++;
        }
    }
	if(colonCount != 2)
	{
		Debug::Error("Invalid use it should be \"./ircserv [host:port_network:password_network] <port> <password>\"");
		std::exit(1);
		return(false);
	}
	return(true);
}

int main(int argc, char **argv)
{
	//Do parsing shit here
	//check if port is valid
	int port;
	std::string pwd;

	if (argc != 3)
	{
		Debug::Error("Invalid use it should be \"./ircserv <port> <password>\"");
		std::exit(1);
	}
	else
	{
		
		port = atoi(argv[1]);
		if(port < 0 || port > 65535 )
		{
			Debug::Error("Invalid port");
			std::exit(1);
		}
		pwd = argv[2];
		
		char hostname[256];
		if (gethostname(hostname, sizeof(hostname)) != 0)
		{
			Debug::Error("Invalid hostname");
			std::exit(1);
		}
		Server irc(std::string(hostname), pwd , port);
	}
	// else if (argc == 4)
	// {
	// 	port = atoi(argv[2]);
	// 	if(port < 0 || port > 65535 )
	// 	{
	// 		Debug::Error("Invalid server port");
	// 		std::exit(1);
	// 	}
	// 	pwd = argv[3];
	// 	checkColumn(argv[1]);
		
	// 	char *token = strtok(const_cast<char*>(argv[1]), ":");
	// 	std::string host = token;
	// 	token = strtok(NULL, ":");
	// 	int port_network = atoi(token);
	// 	token = strtok(NULL, ":");
	// 	std::string password_network = token;
	// 	if(port_network < 0 || port_network > 65535 )
	// 	{
	// 		Debug::Error("Invalid network port");
	// 		std::exit(1);
	// 	}
	// 	(void)port_network;
	// 	(void)password_network;
	// 	Server irc_argc4(host, pwd , port);
	// }
	return(0);
}