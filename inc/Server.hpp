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
# include <unistd.h> 
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
#include <netdb.h> // for getnameinfo()
# include <netinet/in.h> // to use struct addr_in which is used to represnt an IP address and port number.
# include <fcntl.h>
# include <poll.h>
# include <arpa/inet.h> // for inet_ntop()
# include "User.hpp"
# include "Channel.hpp"


#define MIN_PORT_NUMBER	49152      //1025 Registered Ports (1.024 - 49.151) -----   Dynamically Allocated Ports (49.152 - 65.535):
#define MAX_PORT_NUMBER	65535
#define BACKLOG			5
#define BUFFER_SIZE		1024
#define MAX_CONNECTIONS	10

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
		std::map<int, std::string>		_messages;
		std::map<int, std::string>		_userIPs;

		//void			readErrorCodes(std::map<t_err, std::string>& errors);

	public:
		struct pollfd					fds[MAX_CONNECTIONS + 1]; // +1 is to acommodate the Listening socket for the server.
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
		void					setListeningSocket (int n);
		//User*					getUser(void) const;


		// setters
		void					setPort(int inputPortNumber);
		void					checkPassword(const std::string& password) const;

		// member functions
		void					createSocket();
		void					makeListeningSocketReusable();
		void					setSocketToNonBlocking();
		void					bindListeningSocketToServerPort(sockaddr_in addr);
		void					listenToClients();
		void					handle_new_connection(int server_socket, struct pollfd *fds, int *num_fds);
		void					handle_client_data(int client_socket, char *buffer, int buffer_size);
		void					connectUser(int* ptrNum_fds, int* ptrNum_ready_fds, char* buffer);
		void					setupServer();

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