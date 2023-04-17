/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 21:10:05 by pmeising          #+#    #+#             */
/*   Updated: 2023/04/15 12:14:29 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.h"

//======== CONSTRUCTORS =========================================================================
Server::Server(unsigned int port, const std::string& password) :
    _port(port), _password(password), _errorFile("ErrorCodes.txt"), _operators(), clients() 
{

}


//======== OVERLOAD OPERATORS ===================================================================


//======== DESTRUCTOR ===========================================================================
Server::~Server()
{
}

//======== GETTERS / SETTERS ====================================================================
unsigned int    Server::getPort(void) const
{
    return (this->_port);
}

void    Server::setPort(int inputPortNumber)
{
    this->_port = inputPortNumber;
}

const std::string	Server::getPassword(void) const
{
    return (this->_password);
}

int Server::getListeningSocket() const
{
	return (this->_listeningSocket);
}

void	Server::setListeningSocket (int n)
{
	this->_listeningSocket = n;
}


//======== MEMBER FUNCTIONS =====================================================================

/* Creates a stream socket to receive incoming connections on */
/* AF_INET : for IPv4 protocol*/
/* We use TCP Protocol, hence SOCK_STREAM */
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

/* Allow listening socket file description to be reuseable */
void	Server::makeListeningSocketReusable()
{
	int	reuse, on = 1;

	reuse = setsockopt(this->_listeningSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));
	if (reuse < 0)
		throw ErrorInternal();
	else
		std::cout << GREEN << "Listening Socket successfully set to reusable." << D << "\n";
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
		std::cout << GREEN << "Listening Socket successfully set to non blocking." << D << "\n";
}

/* Bind the listening socket to the server port*/
void	Server::bindListeningSocketToServerPort(sockaddr_in addr)
{
	int	rbind;
	rbind = bind(this->getListeningSocket(), (sockaddr *)&addr, sizeof(sockaddr));
	if (rbind == -1)
		throw ErrorInternal();
	else
		std::cout << GREEN << "Listening Socket sucessfully bound to server port." << D << "\n";
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
		std::cout << GREEN << "Listening Socket started listening to IRC clients." << D << "\n";
}


/* Function to handle new client connections */
void Server::handle_new_connection(int server_socket, struct pollfd *fds, int *num_fds)
{
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);
    int client_socket = accept(server_socket, (struct sockaddr *) &client_addr, &addr_len);
    
    if (client_socket < 0) {
        std::cerr << "Error accepting new connection" << std::endl;
        return;
    }
    
    /* Add the new client socket to the list of fds to poll */
    fds[*num_fds].fd = client_socket;
    fds[*num_fds].events = POLLIN;
    (*num_fds)++;
    
    std::cout << "New client connected from " << inet_ntoa(client_addr.sin_addr) << ":" << ntohs(client_addr.sin_port) << std::endl;
}

/* Function to handle data from a client socket */
void Server::handle_client_data(int client_socket, char *buffer, int buffer_size)
{
    int num_bytes = recv(client_socket, buffer, buffer_size, 0);
    
    if (num_bytes < 0) {
        std::cerr << "Error receiving data from client" << std::endl;
        return;
    } else if (num_bytes == 0) {
        /* Client has disconnected */
        std::cout << "Client disconnected" << std::endl;
        close(client_socket);
    } else {
        /* Output the received message */
        buffer[num_bytes] = '\0';
        std::cout << "Received message from client: " << buffer << std::endl;
    }
}

/* setup IRC server */
void	Server::setupServer()
{
	std::cout << "Server Port Number is\t: " << this->getPort() << "\n";
	std::cout << "Server Password is\t: " << this->getPassword() << "\n";
	std::cout << "listening socket\t: " <<  this->getListeningSocket()<< "\n";
	char buffer[BUFFER_SIZE];

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

	struct sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(this->getPort());
	hint.sin_addr.s_addr = htonl(INADDR_ANY); // assigning the IP address of my own local machine (loopback address)

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

	/* We cannot use non blocking unless we use poll simultaneously, otherwise, accept() will not block and always return an error and the serer will exit without accepting any clients */
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

	struct pollfd fds[MAX_CONNECTIONS + 1];
    int num_fds = 1;
    fds[0].fd = this->getListeningSocket();
    fds[0].events = POLLIN;
    
    while (true)
	{
        /* Use poll to wait for activity on any of the sockets */
        int num_ready_fds = poll(fds, num_fds, -1);
        if (num_ready_fds < 0)
		{
            std::cout << RED << "Error : polling for events" << D << "\n";
            return ;
        }
		else if (num_ready_fds == 0)
		{
            continue;
        }
        
        /* Check for new connections on the server socket */
        if (fds[0].revents & POLLIN)
		{
            this->handle_new_connection(this->getListeningSocket(), fds, &num_fds);
            num_ready_fds--;
        }
        
        /* Check for activity on any of the client sockets */
        for (int i = 1; i < num_fds && num_ready_fds > 0; i++) {
            if (fds[i].revents & POLLIN) {
                this->handle_client_data(fds[i].fd, buffer, BUFFER_SIZE);
                num_ready_fds--;
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
