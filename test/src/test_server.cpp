/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_server.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:52:04 by pmeising          #+#    #+#             */
/*   Updated: 2023/04/20 23:23:29 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/catch.hpp"
# include "../../inc/Server.h"
# include "../../inc/Channel.hpp"
# include "../../inc/User.hpp"

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

		User	user(3, "127.0.0.0", &server);
		server.createChannel("newChannel", "SpaceTravel", &user);
		Channel	*channel = server.getChannel("newChannel");
		REQUIRE(channel != NULL);
		REQUIRE(channel->isUserInList(channel->getListPtrOrdinaryUsers(), &user) == true);
		std::cout << channel->getTopic() << "\n";
	}
}
