/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moninechan <moninechan@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 17:20:54 by mochan            #+#    #+#             */
/*   Updated: 2023/04/10 10:05:43 by moninechan       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Server.hpp"


int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << "Error: expected number of arguments is 2 : <server port number> <server password>\n";
		return (0);
	}
	if (!argv[1])
	{
		std::cout << "Error: port server missing\n";
		return (0);
	}
	if (argv[1])
	{
		int                 errPortNumber = 0;
		const std::string   portStr(argv[1]);
		struct sockaddr_in	addr = {};

		errPortNumber = checkPort(argv[1]);
		if (errPortNumber > 0)
		{
			std::cout << "Error: port server number invalid, should be between 1025 and 65535\n";
			return (0);
		}
		Server IrcServer(atoi(argv[1]), argv[2]);
		std::cout << "Server Port Number is : " << IrcServer.getPort() << "\n";
		std::cout << "Server Password is : " << IrcServer.getPassword() << "\n";
		std::cout << "listening socket : " <<  IrcServer.getListeningSocket()<< "\n";
		try
		{
			IrcServer.makeListeningSocketReusable();
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << "Error: could not make listening socket re-usable\n";
		}
		try
		{
			IrcServer.setSocketToNonBlocking();
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << "Error: could not make the listening socket non blocking\n";
		}
		/* Initialize the environment for sockaddr structure */
		memset(&addr, 0, sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_port = htons(IrcServer.getPort());
		addr.sin_addr.s_addr = htonl(INADDR_ANY); // assigning the IP address of my own local machine (loopback address)

		/* Bind the listening socket to the server port*/
		int	rbind = 0;
		rbind = bind(IrcServer.getListeningSocket(), (sockaddr *)&addr, sizeof(sockaddr));
		if (rbind == -1)
		{
			std::cout << "Error: binding socket failed\n";
			return (0);
		}
		std::cout << "rbind = " << rbind <<"\n";
	}
	return (0);
}