/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_user.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 20:01:16 by cudoh             #+#    #+#             */
/*   Updated: 2023/04/30 21:21:22 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../inc/catch.hpp"
# include "../../inc/User.hpp"

/*
 * for proper catch setup. Please watch the youtube video
 * https://www.youtube.com/watch?v=LYKOqZCB6lQ
 *
 */


TEST_CASE("Test setNick, getNick") {
	User user(4, "0", NULL);

	std::vector<std::string> args;
	args.push_back("florian_nick");
	user.setNickName(args);
	REQUIRE(user.getNickName() == "florian_nick");
}

/* TEST_CASE("Test setUsername, getUsername") {
	User user(4, 0);
	std::vector<std::string> args;
    args.push_back("UserName");

	user.setUserName(args);
	REQUIRE(user.getUserName() == "UserName");
} */

TEST_CASE("Test setRealName, getRealName") {
	User user(4, "255", NULL);

	std::vector<std::string> args;
	args.push_back("Crazy Name");
	user.setRealName(args);
	REQUIRE(user.getRealName() == "Crazy Name");
}

TEST_CASE("Test argsToString") {
	std::vector<std::string> args;
	args.push_back(":Hello");
	args.push_back("i'm");
	args.push_back("a");
	args.push_back(":list");

	User user(4, "255", NULL);
	
	REQUIRE(user.argsToString(args.begin(), args.end()) == (std::string)"Hello i'm a :list");
	REQUIRE(user.argsToString(args.begin() + 3, args.end()) == (std::string)"list");
}