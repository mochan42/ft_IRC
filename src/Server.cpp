# include "../inc/Server.h"

volatile sig_atomic_t prgrm_stop = 0;

// #################### SIG HANDLER FUNCTION ######################

void custom_signal_handler(int signal)
{
    if (signal == SIGINT) {
        prgrm_stop = 1;
    }
}

//======== CONSTRUCTORS =========================================================================
Server::Server(unsigned int port, const std::string& password) :
    _port(port), _listeningSocket(0), _password(password), _serverName("ourIRCServer")
{
	for (int i = 0; i <= MAX_CONNECTIONS; i++)
	{
		this->fds[i].fd = 0;
		this->fds[i].events = 0;
		this->fds[i].revents = 0;
	}
}

//======== DESTRUCTOR ===========================================================================
Server::~Server()
{
	if (!this->_channels.empty())
	{
		std::map<std::string, Channel*>::iterator begin_it = _channels.begin();
		std::map<std::string, Channel*>::iterator end_it = _channels.end();
		for (std::map<std::string, Channel*>::iterator it = begin_it; it != end_it; it++)
		{
			if (it->second)
				delete it->second;
		}	
	}
	if (!this->_users.empty())
	{
		std::map<int, User*>::iterator	it_begin = this->_users.begin();
		for (std::map<int, User*>::iterator it = it_begin; it != _users.end(); it++)
		{
			if (it->second)
				delete it->second;
		}	
	}
    _messages.clear();
}

//======== GETTERS / SETTERS ====================================================================
unsigned int	Server::getPort(void) const
{
    return (this->_port);
}

void 	Server::setPort(int inputPortNumber)
{
    this->_port = inputPortNumber;
}

bool	Server::verifyPassword(const std::string& password) const
{
    if (!password.empty() && password == this->_password)
		return (true);
	return (false);
}

int 	Server::getListeningSocket() const
{
	return (this->_listeningSocket);
}

void	Server::setListeningSocket (int n)
{
	this->_listeningSocket = n;
}

std::string		Server::getServerName()
{
	return(this->_serverName);
}

User* Server::getUser(std::string nickName)
{
    std::map<int, User*>::iterator it;
    for (it = this->_users.begin(); it != this->_users.end(); it++)
    {
        if (nickName == (*it).second->getNickName())
		{
            std::cout << "Nickname of found User is : " << (*it).second->getNickName() << "\n";
			return (*it).second;
		}
    }
    std::cout << BLUE << "User " << nickName << " not found" << D << "\n";
    return (NULL);
}

void	Server::setServerIP(std::string setServerIP)
{
	this->_serverIP = setServerIP;
}

std::string	Server::getServerIP()
{
	return (this->_serverIP);
}

Channel*	Server::getChannel(const std::string& channel_name) const
{
	std::map<std::string, Channel*>::const_iterator	it = this->_channels.find(channel_name);
	if (it != this->_channels.end())
		return (it->second);
	return (NULL);
}

Channel*	Server::createChannel(const std::string& channel_name, User* user)
{
	if (user->getFd() < 3 || user->getFd() > 1024)
		return (NULL);
	else if (channel_name == "")
		return (NULL);
	std::map<std::string, Channel*>::iterator	it = this->_channels.find(channel_name);
	if (it == this->_channels.end())
	{
		Channel	*channel = new Channel(channel_name, user);
		this->_channels[channel_name] = channel;
		return (channel);
	}
	return (NULL);
}

void	Server::remChannel(const std::string& channel_name)
{
	std::map<std::string, Channel*>::iterator	it = this->_channels.find(channel_name);
	if (it != this->_channels.end())
	{
		Channel	*temp = it->second;
		this->_channels.erase(it);
		if (temp)
			delete temp;
	}
}

//======== MEMBER FUNCTIONS =====================================================================

/* Creates a stream socket to receive incoming connections on */
/* AF_INET : for IPv4 protocol*/
/* We use TCP Protocol, hence SOCK_STREAM being a stream socket*/
/* protocol = 0 beacuase there is only one protocol available for UNIX domain sockets */
void	Server::createSocket()
{
    int listening;
	
	listening = socket(AF_INET, SOCK_STREAM, 0);
	this->setListeningSocket(listening);
	if (this->getListeningSocket() == -1)
		throw ErrorInternal();
	else
	{
		#ifdef DEBUG
			std::cout << GREEN << "Listening Socket successfully created : "  << this->getListeningSocket() << D <<"\n";
		#endif
	}

}

/* Allow listening socket file description to be reuseable
	https://beej.us/guide/bgnet/html/#getaddrinfoprepare-to-launch 5.3 bind()
	Intends to prevent the socket from blocking the port for longer than neccessary.
*/
void	Server::makeListeningSocketReusable()
{
	int	reuse, on = 1;

	reuse = setsockopt(this->_listeningSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));
	if (reuse < 0)
		throw ErrorInternal();
	else
	{
		#ifdef DEBUG
			std::cout << GREEN << "Listening Socket successfully set to reusable" << D << "\n";
		#endif
	}
}

/* Set listening socket to be non blocking. All of the sockets for the incoming 
connections will also be non blocking since they will inherit that state
from the listening socket */
void	Server::setSocketToNonBlocking()
{
	int nonblock = 0;

	nonblock = fcntl(this->getListeningSocket(), F_SETFL, O_NONBLOCK);
	if (nonblock == -1)
		throw ErrorInternal();
	else
	{
		#ifdef DEBUG
			std::cout << GREEN << "Listening Socket successfully set to non blocking" << D << "\n";
		#endif
	}
}

/* Bind the listening socket to the server port*/
void	Server::bindListeningSocketToServerPort(sockaddr_in addr)
{
	int	rbind;
	rbind = bind(this->getListeningSocket(), (sockaddr *)&addr, sizeof(sockaddr));
	if (rbind == -1)
		throw ErrorInternal();
	else
	{
		#ifdef DEBUG
			std::cout << GREEN << "Listening Socket sucessfully bound to server port" << D << "\n";
		#endif
	}

}


/* Listen the request from client (queues the requests). 
BACKLOG : how many requests can be in the active queue */
void	Server::listenToClients()
{
	int rlisten;
	rlisten = listen(this->getListeningSocket(), BACKLOG);
	if (rlisten == -1)
		throw ErrorInternal();
	else
	{
		#ifdef DEBUG
			std::cout << GREEN << "Listening Socket started listening to IRC clients..." << D << "\n";
		#endif
	}
}

void	Server::remUser(const int& user_fd)
{
	std::map<int, User*>::iterator	it = this->_users.find(user_fd);
	if (it != this->_users.end())
	{
		#ifdef DEBUG
		std::cout << "========= List of fds BEFORE removing fd : " << user_fd <<  " from fds =========\n";
		for (int i = 0; i < (MAX_CONNECTIONS + 1); i++)
		{
			std::cout << "client socket fd is : " << this->fds[i].fd << "\n";
		}
		#endif
		for (int i = 0; i <= num_fds; i++)
        {
            if (this->fds[i].fd == (*it).first)
            {
                for(int j = i; j <= num_fds && j <= MAX_CONNECTIONS; j++)
                {
                    if (j == MAX_CONNECTIONS)
					{
						this->fds[j].fd = 0;
						this->fds[i].events = 0;
						this->fds[i].revents = 0;
					}
					else
                        this->fds[j] = this->fds[j + 1];
                }
                num_fds--;
                break;
            }
        }
		#ifdef DEBUG
		std::cout << "========= List of fds AFTER removing fd : " << user_fd <<  " from fds =========\n";
		for (int i = 0; i < (MAX_CONNECTIONS + 1); i++)
		{
			std::cout << "client socket fd is : " << this->fds[i].fd << "\n";
		}
		#endif
		this->_users.erase(user_fd);
	}
}

void	Server::deleteChannel(Channel *channelPtr)
{
	std::cout << RED << "TEST PRINT OUT\n" << D;
	std::map<std::string, Channel*>::iterator iter = _channels.begin();
	std::map<std::string, Channel*>::iterator iterTemp;
	while (iter != _channels.end())
	{
		if (channelPtr->getChannelName() == (*iter).second->getChannelName())
		{
			iterTemp = iter;
			++iter; 
			_channels.erase(iterTemp);
		}
		else
			++iter;
	}
	delete channelPtr;
}


/* Function to handle new client connections */
void	Server::handle_new_connection(int server_socket, struct pollfd *fds, int *num_fds)
{
    struct sockaddr_in	client_addr;
    socklen_t 			addr_len = sizeof(client_addr);
	int 	client_socket = accept(server_socket, (struct sockaddr *) &client_addr, &addr_len);

    if (client_socket < 0 || (client_socket >= 0 && *num_fds > MAX_CONNECTIONS))
	{
        std::cout << RED << "Error accepting new connection" << D << "\n";
        return;
    }

	/* instantiate User class for new client, store IP address, fd = client_socket */
    
    /* Add the new client socket to the list of fds to poll */
    fds[*num_fds].fd = client_socket;
    fds[*num_fds].events = POLLIN;
	std::string ipAddress = inet_ntoa(client_addr.sin_addr);
	User* new_user = new User(client_socket, ipAddress, this);
	this->_users[client_socket] = new_user;
	(*num_fds)++;
	std::cout << "New client connected from :" << inet_ntoa(client_addr.sin_addr) << ":" << ntohs(client_addr.sin_port) << "\n";
	std::cout << "IP Address (long) :" << new_user->getIP() << "\n";
}

/* Function to handle data from a client socket */
void	Server::handle_client_data(int client_socket, char *buffer, int buffer_size)
{
	std::string *input = this->getUserByFd(client_socket)->getInput();
	int num_bytes = recv(client_socket, buffer, buffer_size, 0);
	if (num_bytes < 0)
	{
		std::cout << RED << "Error receiving data from client" << D  << "\n";
		return;
	}
	else if (num_bytes == 0)
	{
		/* Client has disconnected */
		std::cout << "Client disconnected\n";
		std::_Rb_tree_iterator<std::pair<const int, User *> > it = this->_users.find(client_socket);
		if (it->first == client_socket)
		{
			User *user = this->_users.find(client_socket)->second;
			user->quitServer();
			return;
		}
		close(client_socket);
	}
	else
	{
		buffer[num_bytes] = '\0';
		*input += std::string(buffer, 0, num_bytes);
		if (input->find("\n") == std::string::npos)
		{
			std::cout << "received partial input: \"" << input << "\", nothing to execute yet" <<std::endl;
			return;
		}
	}
	if (input->find("\n") != std::string::npos)
	{
		this->_messages[client_socket] = *input;
		input->clear();
	}
	#if DEBUG
	std::cout << "Stored message from client: " << this->_messages[client_socket] << "\n";
	#endif
	// Create a Message instance using the buffer content
	Message msg(this->_messages[client_socket]);
	// Extract the command and arguments from the Message instance
	std::vector<std::string> command = msg.getCommand();
	std::vector<std::vector<std::string> > args = msg.getArguments();
	if (args.size() == 0)
		return;
	#if DEBUG
	// Print the command and arguments for debugging purposes
	for (unsigned int i = 0; i < command.size(); i++){
		std::cout << "Command: " << command[i] << "\n";
		std::cout << "Parsed arguments: ";
		for (unsigned int j = 0; j < args[i].size(); j++)
		{
				std::cout << j << "- " << args[i][j];
		}}
	std::cout << "\n";
	#endif
	std::map<int, User*>::iterator user_it = _users.find(client_socket);
	if (user_it != _users.end())
	{
		User *user = user_it->second;
		int i = 0;
		for (std::vector<std::string>::iterator iter = command.begin(); iter != command.end(); ++iter)
		{
			user->executeCommand(command[i], args[i]);
			i++;
		}
	}
}

/*
*	Is called whenever the poll() functions finds that there is a readable Socket available.
*	1.	First checks, whether the fd that is ready to read from is the listening socket from the server.
*		if so it starts the connections and calls handle_new_connection();
*	2.	Then walks through the file descriptors (i.e. sockets) and checks if any of them are ready
*		to be read from. If so, it reads in the data (handle_client_data()) and  reduces the count of 
*		read-ready fds by one.
*/
void	Server::connectUser(int* ptrNum_fds, int* ptrNum_ready_fds, char* buffer)
{
	/* Check for new connections on the server socket */
	if (num_fds <= MAX_CONNECTIONS && (this->fds[0].revents & POLLIN)) // & : bitwise AND operator.
	{
		this->handle_new_connection(this->getListeningSocket(), this->fds, ptrNum_fds);
		(*ptrNum_ready_fds)--;
	}
	
	/* Check for activity on any of the client sockets */
	for (int i = 1; i < *ptrNum_fds && *ptrNum_ready_fds > 0; i++) // start at i=1 to skip Listening socket
	{
		if (this->fds[i].revents & POLLIN)
		{
			this->handle_client_data(this->fds[i].fd, buffer, BUFFER_SIZE);
			(*ptrNum_ready_fds)--;
		}
	}
}

User*	Server::getUserByFd(int client_socket)
{
	std::map<int, User*>::iterator it;
	for(it = this->_users.begin(); it != this->_users.end(); it++)
	{
		if (it->first == client_socket)
			return (it->second);
	}
	std::cout << "User : " << client_socket << " not found.\n";
	return (NULL);
}

void	Server::pingClient(int client_socket)
{
	std::string	pingMessage = "PING";
	send(client_socket, pingMessage.c_str(), pingMessage.length(), 0);

	std::stringstream ss;
	ss << "PING :" << std::time(NULL) << "\n";
	std::string msg = ss.str();

	std::map<int, User*>::iterator it;
	for (it = this->_users.begin(); it != this->_users.end(); it++)
		write(it->first, msg.c_str(), msg.length());
}

/* setup IRC server */
void	Server::setupServer()
{
	#ifdef DEBUG
		std::cout << "Server Name is\t\t: " << this->getServerName() << "\n";
		std::cout << "Server Port Number is\t: " << this->getPort() << "\n";
		std::cout << "Server Password is\t: " << this->_password << "\n";
		std::cout << "listening socket\t: " <<  this->getListeningSocket()<< "\n";
	#endif
	signal(SIGINT, custom_signal_handler);
	/* Creating server socket... */
	try
	{
		this->createSocket();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << RED << "Error: server listening socket failed" << D "\n";
		return ;
	}
	/* setup a server that listens to the host IP address 's_addr' with port 'sin_port' */
	struct sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(this->getPort());
	hint.sin_addr.s_addr = htonl(INADDR_ANY); //  the server will listen on all available network interfaces, including the loopback interface (127.0.0.1)
	std::string ourIRCServerIP = inet_ntoa(hint.sin_addr);
	this->setServerIP(ourIRCServerIP);
	#ifdef DEBUG
		std::cout << "IRC Server IP and port are <IP:Port> : " << this->getServerIP() << ":" << this->getPort() << "\n";
	#endif
	/* Making socket reusable... */
	try
	{
		this->makeListeningSocketReusable();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << RED << "Error: could not make listening socket re-usable." << D << "\n";
		return ;
	}
	/* Setting the listening socket to none blocking */
	try
	{
		this->setSocketToNonBlocking();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << RED << "Error: could not make the listening socket non blocking." << D << "\n";
		return ;
	}
	/* Binding socket to sockaddr... */
	try
	{
		this->bindListeningSocketToServerPort(hint);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << RED << "Error: Listening Socket could not bind to Server port." << D << "\n";
		return ;
	}
	/* Mark the socket for listening... */
	try
	{
		this->listenToClients();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << RED << "Error: Listening Socket could not listen to clients." << D << "\n";
		return ;
	}
	this->num_fds = 1;
	this->fds[0].fd = this->getListeningSocket();
    this->fds[0].events = POLLIN; // instructs poll() to monitor Listening socket 'fds[0]' for incoming connection or data.
    char buffer[BUFFER_SIZE]; // to store message from client(s).

    while (prgrm_stop == 0)
	{
        /* Use poll to wait for activity on any of the sockets */
		int num_ready_fds = poll(this->fds, this->num_fds, TIME_OUT);
		int *ptrNum_ready_fds = &num_ready_fds;
		if (prgrm_stop == 0)
		{
			switch (num_ready_fds) // poll returns the number of elements in the fds array. -1 means waiting forever.
			{
				case -1:
					std::cout << RED << "Error : polling for events" << D << "\n";
					break;
				case 0 :
					this->pingClient(this->fds[this->num_fds].fd);
					break;
				default:
					this->connectUser(&(this->num_fds), ptrNum_ready_fds, buffer);
					break;
			}
		}
	}
    close(this->getListeningSocket());
}

//======== FUNCTIONS ============================================================================
int	checkIsDigit(char *s)
{
	for (int i = 0; s[i]; i++)
	{
		if (std::isdigit(s[i]) == 0)
			return (1);
	}
	return (0); 
}

int	checkOutOfRange(char *s)
{
	long	c;

	c = strtol(s, NULL, 10);
	if (c < MIN_PORT_NUMBER || c > MAX_PORT_NUMBER || strlen(s) > 11)
		return (1);
	return (0);
}

int	checkPort(char *port)
{
	int	err = 0;

	err = checkIsDigit(port) + checkOutOfRange(port);
	return (err);
}
