/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_user.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 20:01:16 by cudoh             #+#    #+#             */
/*   Updated: 2023/04/17 15:04:26 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# define CATCH_CONFIG_MAIN
# include "../inc/catch.hpp"

/*
 * for proper catch setup. Please watch the youtube video
 * https://www.youtube.com/watch?v=LYKOqZCB6lQ
 *
 */

# include "../../inc/user.hpp"

TEST_CASE("Test setNick, getNick") {
	User user;

	user.setNickName("florian");
	REQUIRE(user.getNickName() == "florian");
}

TEST_CASE("Test setUsername, getUsername") {
	User user;

	user.setUserName("UserName");
	REQUIRE(user.getUserName() == "UserName");
}

TEST_CASE("Test setRealName, getRealName") {
	User user;

	user.setRealName("Crazy Name");
	REQUIRE(user.getRealName() == "Crazy Name");
}
