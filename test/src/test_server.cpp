/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_server.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:52:04 by pmeising          #+#    #+#             */
/*   Updated: 2023/04/20 22:12:35 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/catch.hpp"
# include "../../inc/Server.h"

TEST_CASE( "Server : Server Constructor", "[Server]")
{
	SECTION("Server Constructor Port 50000, Password '' ")
	{
		Server	server(50000, "");
		REQUIRE(server.getPort() == 50000);
		REQUIRE(server.getListeningSocket() == 0);
		REQUIRE(server.fds->fd >= 0);
		REQUIRE(server.fds->events >= 0);
		REQUIRE(server.fds->revents >= 0);
	}
	SECTION("Server createSocket() function valid")
	{
		Server	server(50000, "password");
		server.createSocket();
		REQUIRE(server.getListeningSocket() > 2);
	}
}
TEST_CASE( "Server : Channel Creation", "[Server]")
{
	SECTION("Channel creation and retrieval - valid input")
	{
		Server	server(50000, "PasswordIsGoodToHave");

		Channel 
		server.createChannel()
	}
}
