/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_server.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:52:04 by pmeising          #+#    #+#             */
/*   Updated: 2023/04/18 21:08:17 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/catch.hpp"
# include "../../inc/Server.h"

TEST_CASE( "Server : Server Constructor", "[Server]")
{
	SECTION("Server Constructor NULL")
	{
		Server	server();
		REQUIRE(server.);
	}
	SECTION("Server Constructor Port 50000, Password '' ")
	{
		Server	server(50000, "");
		REQUIRE("Error: expected number of arguments is 2 : <server port number> <server password>");
	}
	SECTION("Server Constructor Port 50000, Password '' ")
	{
		Server	server(50000, ".");
		REQUIRE("Server Password is      : .");
	}
}
