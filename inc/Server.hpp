/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 21:10:11 by pmeising          #+#    #+#             */
/*   Updated: 2023/04/15 10:51:15 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP
# include <string>
# include <cstdlib> // for strtol
# include <cctype> // for isdigit
# include <cstring> // for strlen
# include <limits.h> // for INT_MAX and INT_MIN
# include <iostream>
# include <exception>
# include <map>
# include <list>
//# include "User.hpp"
//# include "Channel.hpp"

#define MIN_PORT_NUMBER 1025
#define MAX_PORT_NUMBER 65535


//class User;

//class Channel;

class Server
{
	private:
		//std::map<int, User*>			_users;
		//std::map<std::string, Channel*>	_channels;
		//std::map<t_err, std::string>	_errors;
		Server(const Server& obj);
		Server&	operator=(const Server& rhs);
		Server(const std::string& port, const std::string& password);
		std::list<std::string>			_operators;
		unsigned int					_port;
		const std::string				_password;
		const std::string				_errorFile;

		void			checkPort(const std::string& port) const;
		void			checkPassword(const std::string& password) const;
		//void			readErrorCodes(std::map<t_err, std::string>& errors);

	public:
		Server();
		~Server();
		// void			startServer(void);
		// void			closeServer(void);
		
		void					createChannel(const std::string& channel) const;
		void					pingClient(void) const;
		
		// getters
		//Channel*				getChannel(const std::string& channel) const;
		unsigned int			getPort(void) const;
		//User*					getUser(void) const;


		// setters
		void					setPort(int inputPortNumber);

		// exception class
		class Exception : public std::exception
		{
			virtual const char *what() const throw()
			{
				return exception::what();
			}
		};

};

int	checkIsDigit(char *s);
int	checkOutOfRange(char *s);
int	checkPortNumber(char *str);

#endif