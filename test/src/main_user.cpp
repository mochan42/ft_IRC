/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_user.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 20:01:16 by cudoh             #+#    #+#             */
/*   Updated: 2023/04/18 16:32:30 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# define CATCH_CONFIG_MAIN
# include "../inc/catch.hpp"

/*
 * for proper catch setup. Please watch the youtube video
 * https://www.youtube.com/watch?v=LYKOqZCB6lQ
 *
 */

# include "../../inc/User.hpp"
#include <iostream>

/* TEST_CASE("Test setNick, getNick") {
	User user(4, 0);
	
	user.setNickName("florian_nick");
	REQUIRE(user.getNickName() == "florian_nick");
} */

/* TEST_CASE("Test setUsername, getUsername") {
	User user(4, 0);
	std::vector<std::string> args;
    args.push_back("UserName");

	user.setUserName(args);
	REQUIRE(user.getUserName() == "UserName");
} */

/* TEST_CASE("Test setRealName, getRealName") {
	User user(4, 0);

	user.setRealName("Crazy Name");
	REQUIRE(user.getRealName() == "Crazy Name");
} */

TEST_CASE("Test combine_args") {
	std::vector<std::string> args;
	args.push_back(":Hello");
	args.push_back("i'm");
	args.push_back("a");
	args.push_back(":list");

	User user(4, 255, NULL);
	
	REQUIRE(user.combine_args(args.begin(), args.end()) == (std::string)"Hello i'm a :list");
	REQUIRE(user.combine_args(args.begin() + 3, args.end()) == (std::string)"list");
}