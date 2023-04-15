/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 21:10:11 by pmeising          #+#    #+#             */
/*   Updated: 2023/04/15 10:27:00 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP
# include <string>
# include <iostream>
# include <map>
# include <list>
# include "User.hpp"
# include "Channel.hpp"

class User;

class Channel;

class Server
{
	private:
		std::map<int, User*>			_users;
		std::map<std::string, Channel*>	_channels;
		std::map<t_err, std::string>	_errors;
		std::list<std::string>			_operators;
		unsigned int					_port;
		const std::string				_password;
		Server();
		Server(const Server& obj);
		Server&	operator=(const Server& rhs);
		void			checkPort(const std::string& port) const;
		void			checkPassword(const std::string& password) const;

	public:
		Server(const std::string& port, const std::string& password);
		~Server();
		// void			startServer(void);
		// void			closeServer(void);
		
		void					createChannel(const std::string& channel) const;
		
		// getters
		unsigned int			getPort(void) const;
		std::map<int, User*>&	getUsers(void) const;

		
};



#endif