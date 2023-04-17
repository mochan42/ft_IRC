/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_server.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:52:04 by pmeising          #+#    #+#             */
/*   Updated: 2023/04/17 23:01:44 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/catch.hpp"
# include "../../inc/Server.h"

TEST_CASE( "Server : Server Constructor", "[Server]")
{
	SECTION("Server Constructor NULL")
	{
		Server	server();
		REQUIRE("Error: expected number of arguments is 2 : <server port number> <server password>");
	}
	SECTION("Server Constructor Port 50000, Password NULL")
	{
		Server	server(50000, "test");
		REQUIRE("Error: expected number of arguments is 2 : <server port number> <server password>");
	}
}
