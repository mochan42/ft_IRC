/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 17:20:54 by mochan            #+#    #+#             */
/*   Updated: 2023/04/18 12:59:11 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Server.h"
#include "../inc/User.hpp"

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << RED << "Error: expected number of arguments is 2 : <server port number> <server password>" << D << "\n";
		return (0);
	}
	if (!argv[1])
	{
		std::cout << RED << "Error: port server missing\n" << D << "\n";
		return (0);
	}
	if (argv[1])
	{
		int                 errPortNumber = 0;
		const std::string   portStr(argv[1]);

		errPortNumber = checkPort(argv[1]);
		if (errPortNumber > 0)
		{
			std::cout << RED << "Error: port server number invalid, should be between 49152 and 65535" << D << "\n";
			return (0);
		}
		Server IrcServer(atoi(argv[1]), argv[2]);
		IrcServer.setupServer();
	}
	return (0);
}