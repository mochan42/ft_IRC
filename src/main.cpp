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
    Server       IrcServer;

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
        int errPortNumber = 0;
        
        errPortNumber = checkPortNumber(argv[1]);
        if (errPortNumber > 0)
        {
            std::cout << "Error: port server number invalid, should be between 1025 and 65535\n";
            return (0);
        }
        IrcServer.setPort(atoi(argv[1]));
        std::cout << "Server Port Number is : " << IrcServer.getPort() << "\n";
    }

    return (0);
}