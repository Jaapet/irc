#include "Server.hpp"
#include "Session.hpp"
#include "Message.hpp"
#include <fcntl.h>
#include <cstring>
#include <ctime>

//CONSTRUCTOR//////////////////////////////////////////////////
Server::Server(std::string hostname, std::string pwd, uint16_t port): _hostname(hostname), _password(pwd), _port(port) 
{
	//Init
	this->_select_timeout.tv_usec = 100000;

	this->_servername = "PEPPA_IRC";
	this->_networkname = "NETWORK_NAME";
	this->_version = "1234";
	this->_available_user_modes = "AVAILABLE_USER_MODES";
	this->_available_channel_modes = "AVAILABLE_CHANNEL_MODES";
	this->_creation_date = Utils::getCurrentDate();
	Debug::Info("Persue the server to not commit suicide");
	this->_should_i_end_this_suffering = false;

	Debug::Info("Attempt to initialize " + this->getHostName() + " IRC server");
	try
	{
		
		this->createSocket();
		this->bindSocket();
		this->launchListen();
		this->mapCommands();
		this->initSessionsFds();
		Debug::Success("Launching of " + this->getHostName() + " IRC server was sucessfull " + Utils::getCurrentDate());
	}
	catch(const std::exception& e)
	{
		Debug::Error(e.what());
		std::exit(1); 
	}
	// Start of the loop to handle the cnx
	try
	{
		this->handleConnections();
	}
	catch(const std::exception& e)
	{
		Debug::Error(e.what());
		std::exit(1);
	}
	
}

Server::~Server()
{
}
















//PRIVATE METHODS///////////////////////////////////////////////////////

// Private method, should only be launched by the constructor
void Server::createSocket(void)
{
	this->_fd_socket = socket(AF_INET, SOCK_STREAM, 0); // TO COMMENT JPTA
	if (this->_fd_socket < 0){
		throw(Server::SocketCreationError()); 
	}
}

void Server::bindSocket(void)
{
	Debug::Info("Prepare structure for binding");
	std::memset(&this->_address_socket, 0, sizeof(this->_address_socket)); //Full this->_address_socket with 0 bytes (bzero it, bzero is not part of c++ std lib)
	this->_address_socket.sin_family = AF_INET; //Specify its a tcp ipv4
	this->_address_socket.sin_addr.s_addr = INADDR_ANY; // Listen on every interfaces like a 0.0.0.0
	this->_address_socket.sin_port = htons(this->getPort()); //htons is used to convert a 16-bit quantity from host byte order to network byte order
	Debug::Info("Attempt to bind the socket");
	if (bind(this->getFdSocket(), (struct sockaddr *)&this->getAddressSocket(), this->getLenSocket()) < 0){
		throw(Server::SocketBindingError()); 
	}
}

void Server::launchListen(void)
{
	Debug::Info("Attempt to listening ");
	if (listen(this->getFdSocket(), this->getBackLog()) < 0){
		throw(Server::SocketListenError()); 
	}
}

void Server::initSessionsFds(void)
{
	Debug::Info("Attempt to create fd for the clients sessions ");
	FD_ZERO(&this->_sessions_fd); // TO COMMENT STRAIGHT FROM GPT
	FD_SET(this->getFdSocket(), &this->_sessions_fd); // TO COMMENT STRAIGHT FROM GPT	
}

void Server::mapCommands(void)
{
	Debug::Info("Attempt to map commands ");
	this->_commands["CAP"] = &(Command::cap);
	this->_commands["PASS"] = &(Command::pass);
	this->_commands["NICK"] = &(Command::nick);
	this->_commands["USER"] = &(Command::user);
	
	
}


void Server::handleConnections(void)
{
	int fd_max = this->getFdSocket(); //TO COMMENT
	fd_set session_fd_cpy; //store a copy of session_fd need more explanations
	char buffer[BUFFER_SIZE];

	while(!(this->getKill()))
	{
		session_fd_cpy = this->_sessions_fd;
		if(select(fd_max + 1, &session_fd_cpy, NULL, NULL, &this->_select_timeout) == -1) //CHANGE NULL TO HANDLE TIMEOUT
		{
			throw(Server::SelectCallError()); 
		}

		for(int i = 0; i <= fd_max; i++)
		{
			if(FD_ISSET(i, &session_fd_cpy)) //TO COMMENT I THINK IT LOOP UNTIL FIND A READY FD
			{
				if (i == this->getFdSocket()) // New client found lets make a session
				{
					//MAKE A NEW SESSION JPTA
					Session *tmp_sess = new Session(this);
					socklen_t tmp_size = tmp_sess->getLenSocket();
					tmp_sess->_fd_socket = accept(this->getFdSocket(), (struct sockaddr*)&tmp_sess->_address_socket, &tmp_size);
					if (tmp_sess->getFdSocket() == 0)
					{
						delete tmp_sess;
						throw(Server::SessionCreationError()); 
					}
					else
					{
						FD_SET(tmp_sess->_fd_socket, &this->_sessions_fd);
						if(tmp_sess->_fd_socket > fd_max)
						{
							// Debug::Warning("New value of fd_max");
							fd_max = tmp_sess->_fd_socket;
						}
						if(this->_sessions[tmp_sess->_fd_socket] != NULL)
						{
							Debug::Error("Fatal error, sessions fd duplicated: " + tmp_sess->_fd_socket);
							exit(1);
						}
						this->setNonBlockingFd(tmp_sess->getFdSocket());
						this->_sessions[tmp_sess->_fd_socket] = tmp_sess;

						Debug::Info("New connection from " + std::string(inet_ntoa(tmp_sess->_address_socket.sin_addr)));
					}
				}
				else // if its not a new client
				{
					if(!this->_sessions[i]->getSendBuffer().empty()) //if sendBuffer of the session is not empty
					{
						send(i, this->_sessions[i]->getSendBuffer().c_str(), this->_sessions[i]->getSendBuffer().length() ,MSG_NOSIGNAL);
						this->_sessions[i]->getSendBuffer().clear();
					}
						
					int nbytes = recv(i, buffer, sizeof(buffer), 0);
					if (nbytes <= 0)
					{
						if (nbytes == 0)
						{
							Debug::Warning("Connection closed by: " + std::string(inet_ntoa(this->_sessions[i]->_address_socket.sin_addr)) + " Attempting to close the session server side");
						}
						else
						{
							Debug::Warning("Error with a packet from: " + std::string(inet_ntoa(this->_sessions[i]->_address_socket.sin_addr)) + " closing the connection...");
						}
						this->killSession(i);
					}
					else
					{
						if(nbytes >= this->getBufferSize())
						{
							Debug::Warning("Packet too long from: " + std::string(inet_ntoa(this->_sessions[i]->_address_socket.sin_addr)) + " closing connection...");
							this->killSession(i);
						}
							
						buffer[nbytes] = '\0';
						Debug::Message(std::string(buffer), i);
						
						std::vector<std::string> inBuffer = this->splitBuffer(buffer);
						std::string outBuffer;
						
						for(size_t j = 0; j < inBuffer.size() ; j++)
						{
							
							Message tmp_msg;
							// std::string inBuffer(buffer);
							// inBuffer = this->removeCRLF(inBuffer);
							this->parseMessage(inBuffer[j], tmp_msg);
							if(!(tmp_msg.command.empty()))
							{
								tmp_msg.command = Utils::strToUpper(tmp_msg.command);
								if(this->_commands[tmp_msg.command] != NULL)
									this->_sessions[i]->getSendBuffer() += this->_commands[tmp_msg.command](this, this->_sessions[i], tmp_msg);
								else
									this->_sessions[i]->getSendBuffer() += "ADD HERE CORRECT REPLY COMMAND NOT FOUND";
							}

						}
					}
				}
			}
		}
	}

}

//PUBLIC METHODS//////////////////////////////////////////////////////
void Server::killSession(int const session_fd)
{
	std::string tmp((inet_ntoa(this->_sessions[session_fd]->_address_socket.sin_addr)));

	delete (this->_sessions[session_fd]);
	this->_sessions[session_fd] = NULL;
	close(session_fd);
	FD_CLR(session_fd, &this->_sessions_fd);
	Debug::Success("Session closed from: " + tmp);
}

void Server::parseMessage(const std::string &message, Message &outmessage) 
{
	if(message[0] == '\r' && message[1] == '\n')
		return;
    outmessage.clear();
    
    size_t pos = 0;
    size_t end = message.size();

    // Check for sender (prefix)
    if (message[pos] == ':') {
        size_t prefixEnd = message.find(' ', pos);
        if (prefixEnd != std::string::npos) 
		{
            outmessage.sender = message.substr(pos + 1, prefixEnd - pos - 1);
            pos = prefixEnd + 1;
        } 
		else 
		{
            return; // Invalid message format
        }
    } 
	else 
	{
        outmessage.sender = "";
    }

    // Get command
    size_t commandEnd = message.find(' ', pos);
    if (commandEnd != std::string::npos) 
	{
        outmessage.command = message.substr(pos, commandEnd - pos);
        pos = commandEnd + 1;
    } 
	else 
	{
        outmessage.command = message.substr(pos);
        return;
    }

    // Get params and payload
    while (pos < end) {
        if (message[pos] == ':') 
		{
            // Trailing param (payload)
            outmessage.payload = message.substr(pos + 1);
            break;
        }
        
        size_t paramEnd = message.find(' ', pos);
        if (paramEnd != std::string::npos) 
		{
            outmessage.params.push_back(message.substr(pos, paramEnd - pos));
            pos = paramEnd + 1;
        } 
		else 
		{
            outmessage.params.push_back(message.substr(pos));
            break;
        }
    }
}

void Server::setNonBlockingFd(int fd) 
{
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1) {
        throw std::runtime_error("fcntl F_GETFL failed");
    }
    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1) {
        throw std::runtime_error("fcntl F_SETFL failed");
    }
}


Session *Server::getSession(std::string const &nickname)
{
	std::map<int, Session*>::iterator it;
    Session* foundSession = NULL;
	for (it = this->_sessions.begin(); it != this->_sessions.end(); ++it) 
	{
    	if (Utils::strToUpper(it->second->getNickName()) == Utils::strToUpper(nickname)) 
		{
            foundSession = it->second;
            break;
        }
    }
	return(foundSession);
}



std::vector<std::string>    Server::splitBuffer(std::string const &str)
{
    std::string del = "\r\n";
    std::string tmp2;
    std::string tmp = str;
    size_t  f = 4;
    std::vector<std::string> com;

    while (f != std::string::npos)
    {
        f = tmp.find(del);
        tmp2 = tmp.substr(0, f);
		if (!tmp2.empty())
        	com.push_back(tmp2);
        if (f == std::string::npos)
            break;
        tmp = tmp.substr(f + del.size(), tmp.size() - 1);
    }
    return (com);
}