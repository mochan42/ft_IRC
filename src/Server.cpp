/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 21:10:05 by pmeising          #+#    #+#             */
/*   Updated: 2023/04/14 21:10:06 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

//======== CONSTRUCTORS =========================================================================
Server::Server()
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

//======== MEMBER FUNCTIONS =====================================================================


//======== FUNCTIONS ============================================================================
int	checkIsDigit(char *s)
{
	int i = 0;

	if (s[i] && (s[i] == '-' || s[i] == '+'))
		i++;
	while (s[i])
	{
		if (isdigit(s[i]) != 1)
			return (1);
		i++;
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

int	checkPortNumber(char *str)
{
	int	err = 0;

	err = checkIsDigit(str) + checkOutOfRange(str);
	return (err);
}