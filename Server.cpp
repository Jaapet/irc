#include "Server.hpp"
#include "Session.hpp"
#include <cstring>
//CONSTRUCTOR//////////////////////////////////////////////////
Server::Server(std::string hostname, std::string pwd, uint16_t port): _hostname(hostname), _password(pwd), _port(port) 
{
	//Init
	Debug::Info("Persue the server to not commit suicide");
	this->_should_i_end_this_suffering = false;

	Debug::Info("Attempt to initialize " + this->getHostName() + " IRC server");
	try
	{
		this->createSocket();
		this->bindSocket();
		this->launchListen();
		this->initSessionsFds();
		Debug::Success("Launching of " + this->getHostName() + " IRC server was sucessfull");
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

void Server::handleConnections(void)
{
	int fd_max = this->getFdSocket(); //TO COMMENT
	fd_set session_fd_cpy; //store a copy of session_fd need more explanations
	char buffer[BUFFER_SIZE];

	while(!(this->getKill()))
	{
		session_fd_cpy = this->_sessions_fd;
		if(select(fd_max + 1, &session_fd_cpy, NULL, NULL, NULL) == -1) //CHANGE NULL TO HANDLE TIMEOUT
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
						this->_sessions[tmp_sess->_fd_socket] = tmp_sess;

						Debug::Info("New connection from " + std::string(inet_ntoa(tmp_sess->_address_socket.sin_addr)));
						//Clear variables for new cnx
						tmp_sess = NULL;
						tmp_size = 0;
					}
				}
				else // if its not a new client
				{
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
							Debug::Warning("Packet too long from: " + std::string(inet_ntoa(this->_sessions[i]->_address_socket.sin_addr)) + " it will be truncated");
						buffer[nbytes] = '\0';
						Debug::Message(std::string(buffer), i);
						//DO SOMETHIN JPTA

						//CMD FROM HEXCHAT
						// CAP //Ignore 	
						// NICK
						// USER
						// PASS
						// QUIT
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