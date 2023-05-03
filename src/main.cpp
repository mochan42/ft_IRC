#include <iostream>
#include "../inc/Server.h"
#include "../inc/User.hpp"
#include "../inc/Channel.hpp"

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
			std::cout << RED << "Error: port server number invalid, should be between " << MIN_PORT_NUMBER << " and " << MAX_PORT_NUMBER << D << "\n";
			return (0);
		}
		Server IrcServer(atoi(argv[1]), argv[2]);
		IrcServer.setupServer();
	}
	return (0);
}