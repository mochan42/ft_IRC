/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 21:10:11 by pmeising          #+#    #+#             */
/*   Updated: 2023/04/14 21:25:10 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP
# include <string>
# include <iostream>
# include <map>
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
		

	public:
		Server(/* args */);
		~Server();
};



#endif