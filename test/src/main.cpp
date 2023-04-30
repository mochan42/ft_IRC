/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 20:01:16 by cudoh             #+#    #+#             */
/*   Updated: 2023/04/30 12:32:56 by cudoh            ###   ########.fr       */
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

// TEST_CASE(" User : Test setNick, getNick", "[User]")
// {
// 	SECTION("first case")
// 	{
// 		User user(4, 0, NULL);

// 		std::vector<std::string> args;
// 		args.push_back("florian_nick");
// 		user.setNickName(args);
// 		REQUIRE(user.getNickName() == "florian_nick");
// 	}
// 	// SECTION("Test setUsername, getUsername")
// 	// {
// 	// 	User user(4, 0);
// 	// 	std::vector<std::string> args;
// 	// 	args.push_back("UserName");

// 	// 	user.setUserName(args);
// 	// 	REQUIRE(user.getUserName() == "UserName");
// 	// }
// 	// SECTION("Test setRealName, getRealName")
// 	// {
// 	// 	User user(4, 255, NULL);

// 	// 	std::vector<std::string> args;
// 	// 	args.push_back("Crazy Name");
// 	// 	user.setRealName(args);
// 	// 	REQUIRE(user.getRealName() == "Crazy Name");
// 	// }
// 	// SECTION("Test argsToString")
// 	// {
// 	// 	std::vector<std::string> args;
// 	// 	args.push_back(":Hello");
// 	// 	args.push_back("i'm");
// 	// 	args.push_back("a");
// 	// 	args.push_back(":list");

// 	// 	User user(4, 255, NULL);
		
// 	// 	REQUIRE(user.argsToString(args.begin(), args.end()) == (std::string)"Hello i'm a :list");
// 	// 	REQUIRE(user.argsToString(args.begin() + 3, args.end()) == (std::string)"list");
// 	// }
// }

#if 0
TEST_CASE( "Channel : Channel Constructor", "[Channel]")
{
    
    SECTION("Initialise with valid argument data")
    {
        Server server(5566, "default");
        User flex(1, "127.0.0.1", &server);
        Channel chnSports("Football", "Bundesliga rocks!", &flex);
        REQUIRE(chnSports.getChannelName() == "Football");
        REQUIRE(chnSports.getTopic() == "Bundesliga rocks!");
        REQUIRE(chnSports.getChannelCapacity() == CHN_MAX_USERS);
        REQUIRE(chnSports.getListPtrInvitedUsers() != NULL);
        REQUIRE(chnSports.getListPtrOperators() != NULL);
        REQUIRE(chnSports.getListPtrOrdinaryUsers() != NULL);
    }
    SECTION("Initialise with Invalid argument data")
    {
        Server server(5566, "default");
        User flex(1, "127.0.0.1", &server);
        Channel chnSports("", "", &flex);
        REQUIRE(chnSports.getChannelName() == CHN_DEFAULT_NAME);
        REQUIRE(chnSports.getTopic() == CHN_DEFAULT_TOPIC);
        REQUIRE(chnSports.getChannelCapacity() == CHN_MAX_USERS);
        REQUIRE(chnSports.getListPtrInvitedUsers() != NULL);
        REQUIRE(chnSports.getListPtrOperators() != NULL);
        REQUIRE(chnSports.getListPtrOrdinaryUsers() != NULL);
    }
}
TEST_CASE( "Channel : isUserInChannel", "[Channel]")
{
    SECTION("Add user to empty list")
    {
        Server server(5566, "default");
        User flex(1, "127.0.0.1", &server);
        std::vector<std::string> namelist;
        namelist.push_back("flex");
        Channel chnSports("Tennis", "Selena williams wins big", &flex);
     
        flex.setNickName(namelist);
        chnSports.updateUserList(chnSports.getListPtrOrdinaryUsers(), &flex, USR_ADD);
     
        REQUIRE(chnSports.isUserInChannel(flex.getNickName()) == &flex);
    }
}

TEST_CASE( "Channel : promoteUser", "[Channel]")
{
    SECTION("promote a user : user exist in ordinary user list")
    {
        Server server(5566, "default");
        User flex(1, "127.0.0.1", &server);
        std::vector<std::string> namelist;
        namelist.push_back("flex");
        Channel chnSports("Tennis", "Selena williams wins big", &flex);
     
        flex.setNickName(namelist);
        chnSports.updateUserList(chnSports.getListPtrOperators(), &flex, USR_REMOVE);
        chnSports.updateUserList(chnSports.getListPtrOrdinaryUsers(), &flex, USR_ADD);
        REQUIRE(chnSports.promoteUser("flex") == 0);
        REQUIRE(chnSports.isUserInChannel(flex.getNickName()) == &flex);
        REQUIRE(chnSports.isUserInList(chnSports.getListPtrOperators(), &flex) == true);
        REQUIRE(chnSports.isUserInList(chnSports.getListPtrOrdinaryUsers(), &flex) == false);
    }
    SECTION("promote a user: user does not exist in ordinary user list")
    {
        Server server(5566, "default");
        User flex(1, "127.0.0.1", &server);
        std::vector<std::string> namelist;
        namelist.push_back("flex");
        Channel chnSports("Tennis", "Selena williams wins big", &flex);
     
        flex.setNickName(namelist);
        REQUIRE(chnSports.promoteUser("flex") == CHN_ERR_UserDoesNotExist);
        REQUIRE(chnSports.isUserInChannel(flex.getNickName()) == &flex);
        REQUIRE(chnSports.isUserInList(chnSports.getListPtrOperators(), &flex) == true);
        REQUIRE(chnSports.isUserInList(chnSports.getListPtrOrdinaryUsers(), &flex) == false);
    }
}

TEST_CASE( "Channel : demoteUser", "[Channel]")
{
    SECTION("demote a user : user exist in operator list")
    {
        Server server(5566, "default");
        User flex(1, "127.0.0.1", &server);
        std::vector<std::string> namelist;
        namelist.push_back("flex");
        Channel chnSports("Tennis", "Selena williams wins big", &flex);
     
        flex.setNickName(namelist);
        
        REQUIRE(chnSports.demoteUser("flex") == 0);
        REQUIRE(chnSports.isUserInChannel(flex.getNickName()) == &flex);
        REQUIRE(chnSports.isUserInList(chnSports.getListPtrOrdinaryUsers(), &flex) == true);
        REQUIRE(chnSports.isUserInList(chnSports.getListPtrOperators(), &flex) == false);
    }
    SECTION("demote a user : user does not exist in operator list")
    {
        Server server(5566, "default");
        User flex(1, "127.0.0.1", &server);
        std::vector<std::string> namelist;
        namelist.push_back("flex");
        Channel chnSports("Tennis", "Selena williams wins big", &flex);
     
        flex.setNickName(namelist);
        chnSports.updateUserList(chnSports.getListPtrOperators(), &flex, USR_REMOVE);
        
        REQUIRE(chnSports.demoteUser("flex") == CHN_ERR_UserDoesNotExist);
        REQUIRE(chnSports.isUserInChannel(flex.getNickName()) != &flex);
        REQUIRE(chnSports.isUserInList(chnSports.getListPtrOrdinaryUsers(), &flex) == false);
        REQUIRE(chnSports.isUserInList(chnSports.getListPtrOperators(), &flex) == false);
    }
}

TEST_CASE( "Channel : ChannelCapacity", "[Channel][ChannelCapacity]")
{
    SECTION("Set Channel Capacity : valid input")
    {
        Server server(5566, "default");
        User flex(1, "127.0.0.1", &server);
        Channel club("Bikers", "Trip to Madagascar", &flex);
        
        REQUIRE(club.getChannelCapacity() == CHN_MAX_USERS);
        club.setChannelCapacity(3);
        REQUIRE(club.getChannelCapacity() == 3);
        club.setChannelCapacity(1024);
        REQUIRE(club.getChannelCapacity() == 1024);
        club.setChannelCapacity(100);
        REQUIRE(club.getChannelCapacity() == 100);
    }
    SECTION("Set Channel Capacity : Invalid input")
    {
        Server server(5566, "default");
        User flex(1, "127.0.0.1", &server);
        Channel club("Bikers", "Trip to Madagascar", &flex);
        
        REQUIRE(club.getChannelCapacity() == CHN_MAX_USERS);
        club.setChannelCapacity(1025);
        REQUIRE(club.getChannelCapacity() != 1025);
        club.setChannelCapacity(2);
        REQUIRE(club.getChannelCapacity() != 2);
        club.setChannelCapacity(0);
        REQUIRE(club.getChannelCapacity() != 0);
        REQUIRE(club.getChannelCapacity() == CHN_MAX_USERS);
    }
}

TEST_CASE( "Channel : getNbrOfActiveUser", "[Channel][getNbrOfActiveUser]")
{
    SECTION("get the number of current user in channel : No user ")
    {
        Server server(5566, "default");
        User flex(1, "127.0.0.1", &server);
        Channel club("Bikers", "Trip to Madagascar", &flex);
        
        
        club.updateUserList(club.getListPtrOperators(), &flex, USR_REMOVE);
        REQUIRE(club.getNbrofActiveUsers() == 0);
    }
    SECTION("get the number of current user in channel : 1 operator user ")
    {
        Server server(5566, "default");
        User flex(1, "127.0.0.1", &server);
        Channel club("Bikers", "Trip to Madagascar", &flex);
        
        
        REQUIRE(club.getNbrofActiveUsers() == 1);
    }
    SECTION("get the number of current user in channel : 1 ordinary user ")
    {
        Server server(5566, "default");
        User flex(1, "127.0.0.1", &server);
        Channel club("Bikers", "Trip to Madagascar", &flex);
        
        club.demoteUser(flex.getNickName());
        REQUIRE(club.getNbrofActiveUsers() == 1);
    }
    SECTION("get the number of current user in channel : (2users) 1 ordinary & 1 operator user ")
    {
        Server server(5566, "default");
        User flex(1, "127.0.0.1", &server);
        User speeder(1, "127.0.0.1", &server);
        Channel club("Bikers", "Trip to Madagascar", &flex);
        
        club.updateUserList(club.getListPtrOrdinaryUsers(), &speeder, USR_ADD);
        
        /* flex (operator), speeder(ordinary) => 2 users */
        REQUIRE(club.getNbrofActiveUsers() == 2);
    }
}


TEST_CASE( "Channel : setMode", "[Channel][Mode]")
{
    SECTION("set mode to default : full channel features")
    {
        Server server(5566, "default");
        User flex(1, "127.0.0.1", &server);
        Channel club("Bikers", "Trip to Madagascar", &flex);
        
        club.setMode(CHN_MODE_Invite);
        REQUIRE(club.getMode() == CHN_MODE_Invite);
        club.setMode(CHN_MODE_Default);
        REQUIRE(club.getMode() == CHN_MODE_Default);
    }
    SECTION("set mode to invite : Invite only channel")
    {
        Server server(5566, "default");
        User flex(1, "127.0.0.1", &server);
        Channel club("Bikers", "Trip to Madagascar", &flex);
        
        // Invite is on bit 1(0) : value should be 1
        club.setMode(CHN_MODE_Invite);
        REQUIRE(club.getMode() == 1);
    }
    SECTION("set mode to password protected : channel is protected with password")
    {
        Server server(5566, "default");
        User flex(1, "127.0.0.1", &server);
        Channel club("Bikers", "Trip to Madagascar", &flex);
        
        // Invite is on bit 2(1) : value should be 2
        club.setMode(CHN_MODE_Protected);
        REQUIRE(club.getMode() == 2);
    }
    SECTION("set mode to AdminSetUserLimit : Set channel capacity adjustable by operator only" )
    {
        Server server(5566, "default");
        User flex(1, "127.0.0.1", &server);
        Channel club("Bikers", "Trip to Madagascar", &flex);
        
        // adminSetUserLimit is on bit 3(2) : value should be 4 
        club.setMode(CHN_MODE_CustomUserLimit);
        REQUIRE(club.getMode() == 4);
    }
    SECTION("set mode to AdminSetTopic : Set channel topic adjustable by operator only" )
    {
        Server server(5566, "default");
        User flex(1, "127.0.0.1", &server);
        Channel club("Bikers", "Trip to Madagascar", &flex);
        
        // adminSetTopic is on bit 4(3) : value should be 8 
        club.setMode(CHN_MODE_AdminSetTopic);
        REQUIRE(club.getMode() == 8);
    }
    SECTION("set all mode : Expected outcome is 15 (0x0F)" )
    {
        Server server(5566, "default");
        User flex(1, "127.0.0.1", &server);
        Channel club("Bikers", "Trip to Madagascar", &flex);
         
        club.setMode(CHN_MODE_Invite); club.setMode(CHN_MODE_Protected); club.setMode(CHN_MODE_CustomUserLimit);
        club.setMode(CHN_MODE_AdminSetTopic);
        REQUIRE(club.getMode() == 0x0F);
    }
    SECTION("set all mode : Expected outcome is 15 (0x0F)" )
    {
        Server server(5566, "default");
        User flex(1, "127.0.0.1", &server);
        Channel club("Bikers", "Trip to Madagascar", &flex);
         
        REQUIRE(club.setMode(CHN_MODE_Invite) == CHN_ERR_SUCCESS);
        REQUIRE(club.setMode(CHN_MODE_Protected) == CHN_ERR_SUCCESS);
        REQUIRE(club.setMode(CHN_MODE_CustomUserLimit) == CHN_ERR_SUCCESS);
        REQUIRE(club.setMode(CHN_MODE_AdminSetTopic) == CHN_ERR_SUCCESS);
        REQUIRE(club.getMode() == 0x0F);
    }
    SECTION("set mode without defined constants: " )
    {
        Server server(5566, "default");
        User flex(1, "127.0.0.1", &server);
        Channel club("Bikers", "Trip to Madagascar", &flex);
         
        REQUIRE(club.setMode(15) == CHN_ERR_SUCCESS);
        REQUIRE(club.getMode() == 0x0F);
        club.setMode(CHN_MODE_Default);
        REQUIRE(club.setMode(5) == CHN_ERR_SUCCESS);
        REQUIRE(club.getMode() == 5);
        club.setMode(CHN_MODE_Default);
        REQUIRE(club.setMode(7) == CHN_ERR_SUCCESS);
        REQUIRE(club.getMode() == 7);        
        REQUIRE(club.setMode(10) == CHN_ERR_SUCCESS);
        REQUIRE(club.getMode() == 10);        
    }
    SECTION("set mode : wrong inputs " )
    {
        Server server(5566, "default");
        User flex(1, "127.0.0.1", &server);
        Channel club("Bikers", "Trip to Madagascar", &flex);

        club.setMode(CHN_MODE_Default);
        REQUIRE(club.setMode(16) == CHN_ERR_InvalidMode);
    } 
}


TEST_CASE( "Channel : isModeSet", "[Channel][Mode]")
{
    SECTION("check mode exclusively : check if only a mode is set")
    {
        Server server(5566, "default");
        User flex(1, "127.0.0.1", &server);
        Channel club("Bikers", "Trip to Madagascar", &flex);
        
        club.setMode(CHN_MODE_Default);
        REQUIRE(club.isModeSet(CHN_MODE_Default, CHN_OPT_CTRL_Exclusive) == true);
        club.setMode(CHN_MODE_Invite);
        REQUIRE(club.isModeSet(CHN_MODE_Invite, CHN_OPT_CTRL_Exclusive) == true);
        
        /* Reset mode */
        club.setMode(CHN_MODE_Default); 
        club.setMode(CHN_MODE_Protected);
        REQUIRE(club.isModeSet(CHN_MODE_Protected, CHN_OPT_CTRL_Exclusive) == true);
        
        /* Reset mode */
        club.setMode(CHN_MODE_Default); 
        club.setMode(CHN_MODE_CustomUserLimit);
        REQUIRE(club.isModeSet(CHN_MODE_CustomUserLimit, CHN_OPT_CTRL_Exclusive) == true);
        
        /* Reset mode */
        club.setMode(CHN_MODE_Default); 
        club.setMode(CHN_MODE_AdminSetTopic);
        COUT << (int)(club.getMode()) << ENDL;
        REQUIRE(club.isModeSet(CHN_MODE_AdminSetTopic, CHN_OPT_CTRL_Exclusive) == true);
    }
    SECTION("check mode non-exclusive : check if mode is set regardless of other modes")
    {
        Server server(5566, "default");
        User flex(1, "127.0.0.1", &server);
        Channel club("Bikers", "Trip to Madagascar", &flex);
        
        club.setMode(15);   /* set all modes */
        REQUIRE(club.isModeSet(CHN_MODE_Invite, CHN_OPT_CTRL_NotExclusive) == true);
        REQUIRE(club.isModeSet(CHN_MODE_Protected, CHN_OPT_CTRL_NotExclusive) == true);
        REQUIRE(club.isModeSet(CHN_MODE_CustomUserLimit, CHN_OPT_CTRL_NotExclusive) == true);
        REQUIRE(club.isModeSet(CHN_MODE_AdminSetTopic, CHN_OPT_CTRL_NotExclusive) == true);
        

    }
    SECTION("check mode exclusive : check if only a mode is set regardless of other modes")
    {
        Server server(5566, "default");
        User flex(1, "127.0.0.1", &server);
        Channel club("Bikers", "Trip to Madagascar", &flex);

        /* check that they fail if option control is set to exclusive*/
        club.setMode(15);   /* set all modes */
        REQUIRE(club.isModeSet(CHN_MODE_Invite, CHN_OPT_CTRL_Exclusive) != true);
        REQUIRE(club.isModeSet(CHN_MODE_Protected, CHN_OPT_CTRL_Exclusive) != true);
        REQUIRE(club.isModeSet(CHN_MODE_CustomUserLimit, CHN_OPT_CTRL_Exclusive) != true);
        REQUIRE(club.isModeSet(CHN_MODE_AdminSetTopic, CHN_OPT_CTRL_Exclusive) != true);
    }
    SECTION("check mode exclusive and non exclusive : Invalid mode inputs ")
    {
        Server server(5566, "default");
        User flex(1, "127.0.0.1", &server);
        Channel club("Bikers", "Trip to Madagascar", &flex);

        /* check that they fail if option control is set to exclusive*/
        club.setMode(15);   /* set all modes */
        REQUIRE(club.isModeSet(16, CHN_OPT_CTRL_Exclusive) != true);
        REQUIRE(club.isModeSet(0, CHN_OPT_CTRL_Exclusive) != true);
        REQUIRE(club.isModeSet(9, CHN_OPT_CTRL_Exclusive) != true);
        REQUIRE(club.isModeSet(12, CHN_OPT_CTRL_Exclusive) != true);
        REQUIRE(club.isModeSet(16, CHN_OPT_CTRL_NotExclusive) != true);
        REQUIRE(club.isModeSet(0, CHN_OPT_CTRL_NotExclusive) != true);
        REQUIRE(club.isModeSet(9, CHN_OPT_CTRL_NotExclusive) != true);
        REQUIRE(club.isModeSet(12, CHN_OPT_CTRL_NotExclusive) != true);
        REQUIRE(club.isModeSet(15, CHN_OPT_CTRL_NotExclusive) == true);
    }
}

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
	SECTION("Channel creation - valid input")
	{
		Server	server(50000, "PasswordIsGoodToHave");

		User	user(3, "127.0.0.0", &server);
		server.createChannel("newChannel", "SpaceTravel", &user);
		Channel	*channel = server.getChannel("newChannel");
		REQUIRE(channel != NULL);
		REQUIRE(channel->getChannelName() == "newChannel");
		REQUIRE(channel->isUserInChannel(user.getNickName()) == &user);
	}
	SECTION("Channel creation - invalid input")
	{
		Server	server(50000, "PasswordIsGoodToHave");

		User	*user = new User(3, "127.0.0.0", &server);
		delete user;
		REQUIRE(server.createChannel("newChannel", "topic", user) == NULL);
		User user_1(3, "127.0.0.1", &server);
		REQUIRE(server.createChannel("", "topic", &user_1) == NULL);
		REQUIRE(server.createChannel("newChannel", "", &user_1) == NULL);
	}
}
#endif