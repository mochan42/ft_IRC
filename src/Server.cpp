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


#include "Server.hpp"

//======== CONSTRUCTORS =========================================================================
Server::Server(unsigned int port, const std::string& password) :
    _port(port), _password(password), _errorFile("ErrorCodes.txt"), _operators() 

{
	try
	{
		this->createSocket();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << "Error: server listening socket failed\n";
	}
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


//======== MEMBER FUNCTIONS =====================================================================

/* AF_INET : for IPv4 protocol*/
/* We use TCP Protocol, hence SOCK_STREAM */
/* protocol = 0 beacuase there is only one protocol available for UNIX domain sockets */
void	Server::createSocket()
{
    this->_listeningSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_listeningSocket == -1)
		throw Exception();
}

//======== FUNCTIONS ============================================================================
int	checkIsDigit(char *s)
{
    for (int i = 0; s[i]; i++)
    {
        if (std::isdigit(s[i]) == 0)
        {
            std::cout << "Error!\n";
            return (1);
        }
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
