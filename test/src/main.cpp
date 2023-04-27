/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 20:01:16 by cudoh             #+#    #+#             */
/*   Updated: 2023/04/27 10:16:06 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# define CATCH_CONFIG_MAIN
# include "../inc/catch.hpp"

/*
 * for proper catch setup. Please watch the youtube video
 * https://www.youtube.com/watch?v=LYKOqZCB6lQ
 *
 */



/* catch2 unit test framework - setup
 * ----------------------------------
 * github link -> https://github.com/catchorg/Catch2/tree/v2.x
 * ! Do not clone using http or ssh link
 * Rather Download as zip file as shown in the video link above
*/



/* usage 
 * -----
 * prg_name -o log.txt      : execute test program and save result in file log.txt
 * 
 * prg_name -s -o log.txt   : execute test program and save result in file log.txt
 *                          : -s -> includes the successful test in the log.txt
 * 
 * prg_name --list-tests    : list all/matching test cases
 * prg_name --list-tags     : list all/matching tag 
 */

# include "../../inc/Server.h"
# include "../../inc/Bot.hpp"
# include "../../inc/Channel.hpp"
# include "../../inc/Message.hpp"
# include "../../inc/User.hpp"
# include "../../inc/Utils.hpp"

TEST_CASE(" User : Test setNick, getNick", "[User]")
{
	SECTION("first case")
	{
		User user(4, 0, NULL);

		std::vector<std::string> args;
		args.push_back("florian_nick");
		user.setNickName(args);
		REQUIRE(user.getNickName() == "florian_nick");
	}
	// SECTION("Test setUsername, getUsername")
	// {
	// 	User user(4, 0);
	// 	std::vector<std::string> args;
	// 	args.push_back("UserName");

	// 	user.setUserName(args);
	// 	REQUIRE(user.getUserName() == "UserName");
	// }
	SECTION()
}


TEST_CASE("Test setRealName, getRealName") {
	User user(4, 255, NULL);

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

	User user(4, 255, NULL);
	
	REQUIRE(user.argsToString(args.begin(), args.end()) == (std::string)"Hello i'm a :list");
	REQUIRE(user.argsToString(args.begin() + 3, args.end()) == (std::string)"list");
}