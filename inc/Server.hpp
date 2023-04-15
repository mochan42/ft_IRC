/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 21:10:11 by pmeising          #+#    #+#             */
/*   Updated: 2023/04/15 11:53:28 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP
# include <exception>
# include <string>
# include <cstdlib> // for strtol
# include <cctype> // for isdigit
# include <cstring> // for strlen
# include <limits.h> // for INT_MAX and INT_MIN
# include <iostream>
# include <fstream>
# include <map>
# include <list>
# include <sys/socket.h>  // to create socket
# include <netinet/in.h> // to use struct addr_in which is used to represnt an IP address and port number.
# include <fcntl.h>
//# include "User.hpp"
//# include "Channel.hpp"

#define MIN_PORT_NUMBER 1025
#define MAX_PORT_NUMBER 65535
#define BACKLOG         5
#define BUF_SIZE		30

//class User;

//class Channel;

class Server
{
	private:
		Server();
		//std::map<int, User*>			_users;
		//std::map<std::string, Channel*>	_channels;
		//std::map<t_err, std::string>	_errors;
		Server(const Server& obj);
		Server&	operator=(const Server& rhs);

		
		unsigned int					_port;
		int								_listeningSocket;
		const std::string				_password;
		const std::string				_errorFile;
		std::list<std::string>			_operators;



		//void			readErrorCodes(std::map<t_err, std::string>& errors);

	public:
		Server(unsigned int port, const std::string& password);
		~Server();
		// void			startServer(void);
		// void			closeServer(void);
		
		void					createChannel(const std::string& channel) const;
		void					pingClient(void) const;
		
		// getters
		//Channel*				getChannel(const std::string& channel) const;
		unsigned int			getPort(void) const;
		const std::string		getPassword(void) const;
		int						getListeningSocket(void) const;
		//User*					getUser(void) const;


		// setters
		void					setPort(int inputPortNumber);
		void					checkPassword(const std::string& password) const;

		// member functions
		void					createSocket();
		void					makeListeningSocketReusable();
		void					setSocketToNonBlocking();

		// exception class
		class ErrorInternal : public std::exception
		{
			virtual const char *what() const throw()
			{
				return exception::what();
			}
		};

};

int	checkIsDigit(char *s);
int	checkOutOfRange(char *s);
int	checkPort(char *port);

#endif