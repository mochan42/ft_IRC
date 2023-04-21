/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmollenh <fmollenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 21:10:05 by pmeising          #+#    #+#             */
/*   Updated: 2023/04/21 17:02:34 by fmollenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.h"
#include "User.hpp"

//======== CONSTRUCTORS =========================================================================
Server::Server(unsigned int port, const std::string& password) :
    _port(port), _password(password), _errorFile("ErrorCodes.txt"), _operators(), _messages(), _serverName("ourIRCServer")
{
	for (int i = 0; i <= MAX_CONNECTIONS; i++)
	{
		this->fds[i].fd = 0;
		this->fds[i].events = 0;
		this->fds[i].revents = 0;
	}
}

//======== OVERLOAD OPERATORS ===================================================================


//======== DESTRUCTOR ===========================================================================
Server::~Server()
{
	for (std::map<int, User*>::iterator it = _users.begin(); it != _users.end(); ++it)
	{
		delete it->second;
		this->_users.erase(it);
	}
    _messages.clear();
	// delete[] _messages;
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
    if (password == this->_password)
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
    std::cout << RED << "User " << nickName << " not found" << D << "\n";
    return (NULL);
}

Channel*	Server::getChannel(const std::string& channel_name) const
{
	std::map<std::string, Channel*>::const_iterator	it = this->_channels.find(channel_name);
	if (it != this->_channels.end())
		return (it->second);
	// else
	// 	throw ErrorInternal();
	return (NULL);
}

void	Server::createChannel(const std::string& channel_name, const std::string& topic, User* user)
{
	std::map<std::string, Channel*>::iterator	it = this->_channels.find(channel_name);
	if (it == this->_channels.end())
	{
		Channel	*channel = new Channel(channel_name, topic, user);
		this->_channels[channel_name] = channel;
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
		std::cout << GREEN << "Listening Socket successfully created : "  << this->getListeningSocket() << D <<"\n";
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
		std::cout << GREEN << "Listening Socket successfully set to reusable" << D << "\n";
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
		std::cout << GREEN << "Listening Socket successfully set to non blocking" << D << "\n";
}

/* Bind the listening socket to the server port*/
void	Server::bindListeningSocketToServerPort(sockaddr_in addr)
{
	int	rbind;
	rbind = bind(this->getListeningSocket(), (sockaddr *)&addr, sizeof(sockaddr));
	if (rbind == -1)
		throw ErrorInternal();
	else
		std::cout << GREEN << "Listening Socket sucessfully bound to server port" << D << "\n";
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
		std::cout << GREEN << "Listening Socket started listening to IRC clients..." << D << "\n";
}


/* Function to handle new client connections */
void	Server::handle_new_connection(int server_socket, struct pollfd *fds, int *num_fds)
{
    struct sockaddr_in	client_addr;
    socklen_t 			addr_len = sizeof(client_addr);
    int 				client_socket = accept(server_socket, (struct sockaddr *) &client_addr, &addr_len);
    
    if (client_socket < 0)
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
    // this->_users.insert(std::make_pair(client_socket, new_user));
	(*num_fds)++;
    // Respond with welcome message to user RPLY Code 001
	std::cout << "New client connected from :" << inet_ntoa(client_addr.sin_addr) << ":" << ntohs(client_addr.sin_port) << "\n";
	std::cout << "IP Address (long) :" << new_user->getIP() << "\n";
}

/* Function to handle data from a client socket */
void Server::handle_client_data(int client_socket, char *buffer, int buffer_size)
{
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
		// Freeing allocated memory of User object in std::map<> _user and erasing the entrance from the map.
		delete this->_users.find(client_socket)->second;
		this->_users.erase(client_socket);
        close(client_socket);
    }
	else
	{
        /* Output the received message */
		// Check if CTRL + D
        buffer[num_bytes] = '\0';
		this->_messages[client_socket] = std::string(buffer, 0, num_bytes);
		std::cout << "Stored message from client: " << this->_messages[client_socket] << "\n";
		/* parse buffer */
		// Create a Message instance using the buffer content
		Message msg(this->_messages[client_socket]);
		
		// Extract the command and arguments from the Message instance
		std::vector<std::string> command = msg.getCommand();
		std::vector<std::vector<std::string> > args = msg.getArguments();
		
		// Print the command and arguments for debugging purposes
		for (unsigned int i = 0; i < command.size(); i++)
			std::cout << "Command: " << command[i] << "\n";
   		//for debugging
    	std::cout << "Parsed arguments: ";
    	for (unsigned int i = 0; i < args.size(); i++)
		{
			for (unsigned int j = 0; j < args[i].size(); j++)
				std::cout << args[i][j];
		}
		std::cout << "\n";
		/* client_socket execute cmd */
		std::map<int, User*>::iterator user_it = _users.find(client_socket);
		if (user_it != _users.end()) {
    		User *user = user_it->second;
			int i = 0;
			for (std::vector<std::string>::iterator iter = command.begin(); iter != command.end(); ++iter)
			{
				user->executeCommand(command[i], args[i]);
				i++;
			}
    			
		} 
		else {
    	// Handle the case when the user is not found
		}
    }
}

// /* Function to handle data from a client socket */
// void Server::handle_client_data(int client_socket, char *buffer, int buffer_size)
// {
//     int num_bytes = recv(client_socket, buffer, buffer_size, 0);
// 	if (num_bytes < 0)
// 	{
//         std::cout << RED << "Error receiving data from client" << D  << "\n";
//         return;
//     }
// 	else if (num_bytes == 0)
// 	{
//         /* Client has disconnected */
//         std::cout << "Client disconnected\n";
// 		// Freeing allocated memory of User object in std::map<> _user and erasing the entrance from the map.
// 		delete this->_users.find(client_socket)->second;
// 		this->_users.erase(client_socket);
//         close(client_socket);
//     }
// 	else
// 	{
//         /* Output the received message */
// 		// Check if CTRL + D
//         buffer[num_bytes] = '\0';
// 		this->_messages[client_socket] = std::string(buffer, 0, num_bytes);
// 		std::cout << "Stored message from client: " << this->_messages[client_socket] << "\n";
// 		/* parse buffer */
// 		// Create a Message instance using the buffer content
// 		Message msg(this->_messages[client_socket]);
		
// 		// Extract the command and arguments from the Message instance
// 		std::string command = msg.getCommand();
// 		std::vector<std::string> args = msg.getArguments();
		
// 		// Print the command and arguments for debugging purposes
// 		std::cout << "Command: " << command << "\n";
//    		 //for debugging
//     std::cout << "Parsed arguments: ";
//     for (std::vector<std::string>::const_iterator it = args.begin(); it != args.end(); ++it)
// 		{
//         	std::cout << *it << " ";
// 		}
// 		/* client_socket execute cmd */
// 		std::map<int, User*>::iterator user_it = _users.find(client_socket);
// 		if (user_it != _users.end()) {
//     		//User *user = user_it->second;
//     		//user->executeCommand(commands[1], args[1]);
// 		} 
// 		else {
//     	// Handle the case when the user is not found
// 		}
//     }
// }

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
	if (this->fds[0].revents & POLLIN) // & : bitwise AND operator.
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

/* setup IRC server */
void	Server::setupServer()
{
	std::cout << "Server Name is\t\t: " << this->getServerName() << "\n";
	std::cout << "Server Port Number is\t: " << this->getPort() << "\n";
	std::cout << "Server Password is\t: " << this->_password << "\n";
	std::cout << "listening socket\t: " <<  this->getListeningSocket()<< "\n";

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
	std::cout << "IRC Server IP and port are <IP:Port> : " << inet_ntoa(hint.sin_addr) << ":" << this->getPort() << "\n";

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
 
    int num_fds = 1; // The first element of the array is the Listening socket so there the number of sockets is 1.
    int *ptrNum_fds = &num_fds;
	this->fds[0].fd = this->getListeningSocket();
    this->fds[0].events = POLLIN; // instructs poll() to monitor Listening socket 'fds[0]' for incoming connection or data.
    char buffer[BUFFER_SIZE]; // to store message from client(s).

    while (true)
	{
        /* Use poll to wait for activity on any of the sockets */
		int num_ready_fds = poll(this->fds, num_fds, -1);
		int *ptrNum_ready_fds = &num_ready_fds;
        switch (num_ready_fds) // poll returns the number of elements in the fds array. -1 means waiting forever.
		{
			case -1:
			    std::cout << RED << "Error : polling for events" << D << "\n";
				return ;
			case 0 :
				continue;
			default:
				this->connectUser(ptrNum_fds, ptrNum_ready_fds, buffer);
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
