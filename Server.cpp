#include "Server.hpp"
#include "Session.hpp"
#include "Message.hpp"
#include <fcntl.h>
#include <cstring>
#include <ctime>
#include <cerrno>


void handle_signal_ctrld(int signal) {
    if (signal == SIGINT) {
        Debug::Warning("CTRL-C Pressed, end of the server");
        // Set the flag to indicate Ctrl+C was pressed
        ctrlc_pressed++;
    }
}
//CONSTRUCTOR//////////////////////////////////////////////////
Server::Server(std::string hostname, std::string pwd, uint16_t port): _hostname(hostname), _password(pwd), _port(port) 
{
	//Init
	this->_select_timeout.tv_sec = 1;
	this->_select_timeout.tv_usec = 0;

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
		signal(SIGINT, handle_signal_ctrld);

		this->createSocket();
		this->bindSocket();
		this->launchListen();
		this->mapCommands();
		this->initSessionsFds();
		
		Debug::Header();
		Debug::Success("Launching of " + this->getHostName() + " IRC server was sucessfull " + Utils::getCurrentDate());
		this->handleConnections();//loop until ctrl-c
	}
	catch(const std::exception& e)
	{
		if(!ctrlc_pressed)
		{
			Debug::Error(e.what());
			Server::cleanExit(1);
		}
	}
	this->cleanExit(0);
	
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
	Debug::Info("Attempt to create fd set for the clients sessions ");
	FD_ZERO(&this->_read_sessions_fd); // TO COMMENT STRAIGHT FROM GPT
	FD_SET(this->getFdSocket(), &this->_read_sessions_fd); // TO COMMENT STRAIGHT FROM GPT	

	FD_ZERO(&this->_write_sessions_fd); // TO COMMENT STRAIGHT FROM GPT
	FD_SET(this->getFdSocket(), &this->_write_sessions_fd); // TO COMMENT STRAIGHT FROM GPT	
	
}

void Server::mapCommands(void)
{
	Debug::Info("Attempt to map commands ");
	this->_commands["CAP"] = &(Command::cap);
	this->_commands["PASS"] = &(Command::pass);
	this->_commands["NICK"] = &(Command::nick);
	this->_commands["USER"] = &(Command::user);
	this->_commands["PING"] = &(Command::ping);
	this->_commands["PONG"] = &(Command::pong);
	this->_commands["QUIT"] = &(Command::quit);
	this->_commands["PRIVMSG"] = &(Command::privmsg);
	this->_commands["NOTICE"] = &(Command::notice);
	//this->_commands["ERROR"] = &(Command::error);
}


void Server::handleConnections(void)
{
	int fd_max = this->getFdSocket(); //TO COMMENT
	fd_set read_fd_cpy, write_fd_cpy; //store a copy of session_fd need more explanations


	while(!(this->getKill()))
	{
		read_fd_cpy = this->_read_sessions_fd; //work on copy fdp set because someone told me to do that for an unknown reason
		write_fd_cpy = this->_write_sessions_fd;
		if(select(fd_max + 1, &read_fd_cpy, &write_fd_cpy, NULL, &this->_select_timeout) == -1) //select between read & write fdp with a specified timeout
			throw(Server::SelectCallError()); 

		for(int i = 0; i <= fd_max; i++)
		{	
			if(FD_ISSET(i, &read_fd_cpy)) //Check if FD is in the SET, first itteration trigger the server fd, then all fd put with FD_SET
			{
				if (i == this->getFdSocket()) // New client found lets make a session, basically the read would be on the fd of the server
					this->handleNewSession(fd_max);
				else // if its not a new client
					this->handleReadEvents(i);
			}
			if(FD_ISSET(i, &write_fd_cpy)) //check if current fd is in the write fd_set
				this->handleWriteEvents(i);
		}
		if(ctrlc_pressed)
			this->_should_i_end_this_suffering = true;
	}

}
void Server::handleNewSession(int &fd_max)
{
	Session *tmp_sess = new Session(this);
	socklen_t tmp_size = tmp_sess->getLenSocket();
	tmp_sess->_fd_socket = accept(this->getFdSocket(), (struct sockaddr*)&tmp_sess->_address_socket, &tmp_size);
	this->setNonBlockingFd(tmp_sess->_fd_socket);
	if (tmp_sess->getFdSocket() == 0)
	{
		delete tmp_sess;
		throw(Server::SessionCreationError()); 
	}
	else
	{
		FD_SET(tmp_sess->_fd_socket, &this->_read_sessions_fd); //add client fd to the read fd set
		FD_SET(tmp_sess->_fd_socket, &this->_write_sessions_fd);//add client fd to the write fd set
		if(tmp_sess->_fd_socket > fd_max)
			fd_max = tmp_sess->_fd_socket; //fd max take the last fd to iterate on it
		if(this->_sessions[tmp_sess->_fd_socket] != NULL)
			throw(Server::DuplicatedSessionFd());
		this->_sessions[tmp_sess->_fd_socket] = tmp_sess;
		Debug::Info("New connection from " + std::string(inet_ntoa(tmp_sess->_address_socket.sin_addr)));
	}
}
void Server::handleReadEvents(int cur_fd)
{
	char buffer[BUFFER_SIZE];
	int nbytes = recv(cur_fd, buffer, sizeof(buffer), 0);
	if (nbytes == 0)
	{
		Debug::Warning("Connection closed by: " + std::string(inet_ntoa(this->_sessions[cur_fd]->_address_socket.sin_addr)) + " Attempting to close the session server side");
		this->killSession(cur_fd);
	}
	else if (nbytes < 0)
	{
		Debug::Warning("Error with a packet from: " + std::string(inet_ntoa(this->_sessions[cur_fd]->_address_socket.sin_addr)) + " closing the connection...");
		this->killSession(cur_fd);
	}
	else
	{
		if(nbytes >= BUFFER_SIZE) //IN Packet too long, not clearly explain what to do in rfc, so we choosed to truncate it, client should handle this shit
		{
			Debug::Warning("Packet too long from: " + std::string(inet_ntoa(this->_sessions[cur_fd]->_address_socket.sin_addr)) + " truncate it");
			buffer[BUFFER_SIZE - 2] = '\r';//ADD CR
			buffer[BUFFER_SIZE - 1] = '\n';//ADD LF
		}

		buffer[nbytes] = '\0'; //Terminate buffer with \0, good old char *

		Debug::Message(std::string(buffer), cur_fd);

		this->executeCommands(this->splitBuffer(buffer), cur_fd);
	}
}

void Server::executeCommands(std::vector<std::string> command_to_execute, int cur_fd)
{
	for(size_t i = 0; i < command_to_execute.size() ; i++)
	{
		Message tmp_msg;
		// std::string inBuffer(buffer);
		// inBuffer = this->removeCRLF(inBuffer);
		this->parseMessage(command_to_execute[i], tmp_msg);
		if(!(tmp_msg.command.empty()))
		{
			tmp_msg.command = Utils::strToUpper(tmp_msg.command);
			if(tmp_msg.command == "QUIT") // In case of using QUIT, the session will be deleted before the getting of _sendBuffer, avoid a segfault
				this->_commands[tmp_msg.command](this, this->_sessions[cur_fd], tmp_msg);
			else if(this->_commands[tmp_msg.command] != NULL)
				this->_sessions[cur_fd]->getSendBuffer() += this->_commands[tmp_msg.command](this, this->_sessions[cur_fd], tmp_msg);
			else
				this->_sessions[cur_fd]->getSendBuffer() += "ADD HERE CORRECT REPLY COMMAND NOT FOUND";
		}
	}
}

void Server::handleWriteEvents(int cur_fd)
{
	if(this->_sessions[cur_fd] && !this->_sessions[cur_fd]->getSendBuffer().empty()) //if sendBuffer of the session is not empty
	{
		Debug::Message("[SEND]" + this->_sessions[cur_fd]->getSendBuffer(), cur_fd);
		send(cur_fd, this->_sessions[cur_fd]->getSendBuffer().c_str(), this->_sessions[cur_fd]->getSendBuffer().length() ,MSG_NOSIGNAL);
		this->_sessions[cur_fd]->getSendBuffer().clear();
	}
}
//PUBLIC METHODS//////////////////////////////////////////////////////
void Server::killSession(int const session_fd)
{
	std::string tmp((inet_ntoa(this->_sessions[session_fd]->_address_socket.sin_addr)));

	if(shutdown(session_fd, SHUT_RDWR) == -1)
	{
		Debug::Error("Cannot shutdown session: " + session_fd);
		return;
	}
	delete (this->_sessions[session_fd]);
	this->_sessions.erase(session_fd);
	close(session_fd);
	FD_CLR(session_fd, &this->_read_sessions_fd);
	FD_CLR(session_fd, &this->_write_sessions_fd);
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
    int flags = fcntl(fd, F_SETFL, O_NONBLOCK);
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

void Server::cleanExit(int exitcode)
{
	// for(size_t i = 0; i < this->_sessions.size(); i++)
	// 	this->killSession(this->_sessions[i]->getFdSocket());
	// for(size_t i = 0; i < this->_channels.size(); i++)
		// this->rmchannel;

	std::map<int, Session*>::iterator it;
	if(this->_sessions.size() > 0)
	{
		for (it = this->_sessions.begin(); it != this->_sessions.end(); ++it)
		{
			Debug::Info("[cleanExit] Killing session: " + it->first);
			this->killSession(it->first);
		}
			
	}
    
	this->_should_i_end_this_suffering = true;
	try
	{
		close(this->getFdSocket());
		shutdown(this->getFdSocket(), SHUT_RDWR);
	}
	catch(const std::exception& e)
	{
		Debug::Error(e.what());
		std::exit(1);
	}
	
	
	std::exit(exitcode);
}