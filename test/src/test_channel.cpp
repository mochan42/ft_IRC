/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_channel.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 18:59:02 by cudoh             #+#    #+#             */
/*   Updated: 2023/04/20 23:01:15 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// # include "../inc/catch.hpp"
// # include "../../inc/Channel.hpp"


// TEST_CASE( "Channel : Channel Constructor", "[Channel]")
// {
    
//     SECTION("Initialise with valid argument data")
//     {
//         Channel chnSports("Football", "Bundesliga rocks!");
//         REQUIRE(chnSports.getChannelName() == "Football");
//         REQUIRE(chnSports.getTopic() == "Bundesliga rocks!");
//         REQUIRE(chnSports.getChannelCapacity() == CHN_MAX_USERS);
//         REQUIRE(chnSports.getListPtrInvitedUsers() != NULL);
//         REQUIRE(chnSports.getListPtrOperators() != NULL);
//         REQUIRE(chnSports.getListPtrBannedUsers() != NULL);
//         REQUIRE(chnSports.getListPtrOrdinaryUsers() != NULL);
//     }
//     SECTION("Initialise with Invalid argument data")
//     {
//         Channel chnSports("", "");
//         REQUIRE(chnSports.getChannelName() == "");
//         REQUIRE(chnSports.getTopic() == "Bundesliga rocks!");
//         REQUIRE(chnSports.getChannelCapacity() == CHN_MAX_USERS);
//         REQUIRE(chnSports.getListPtrInvitedUsers() != NULL);
//         REQUIRE(chnSports.getListPtrOperators() != NULL);
//         REQUIRE(chnSports.getListPtrBannedUsers() != NULL);
//         REQUIRE(chnSports.getListPtrOrdinaryUsers() != NULL);
//     }
// }



// TEST_CASE( "Channel : isUserInChannel", "[Channel]")
// {
//     SECTION("Add user to empty list")
//     {
//         User flex(1, "127.0.0.1");
//         std::vector<std::string> namelist;
//         namelist.push_back("flex");
//         Channel chnSports("Tennis", "Selena williams wins big");
        
//         flex.setNickName(namelist);
//         chnSports.addUserToList(chnSports.getListPtrOrdinaryUsers(), &flex);
        
//         REQUIRE(chnSports.isUserInChannel(flex.getNickName()) == &flex);
//     }
// }

// TEST_CASE( "Channel : promoteUser", "[Channel]")
// {
//     SECTION("promote a user")
//     {
//         User flex(1, "127.0.0.1");
//         std::vector<std::string> namelist;
//         namelist.push_back("flex");
//         Channel chnSports("Tennis", "Selena williams wins big");
        
//         flex.setNickName(namelist);
//         chnSports.addUserToList(chnSports.getListPtrOrdinaryUsers(), &flex);
//         REQUIRE(chnSports.promoteUser("flex") == 0);
//         REQUIRE(chnSports.isUserInChannel(flex.getNickName()) == &flex);
//         REQUIRE(chnSports.isUserInList(chnSports.getListPtrOperators(), &flex) == true);
//         REQUIRE(chnSports.isUserInList(chnSports.getListPtrOrdinaryUsers(), &flex) == false);
//     }
// }

// TEST_CASE( "Channel : demoteUser", "[Channel]")
// {
//     SECTION("demote a user")
//     {
//         User flex(1, "127.0.0.1");
//         std::vector<std::string> namelist;
//         namelist.push_back("flex");
//         Channel chnSports("Tennis", "Selena williams wins big");
        
//         flex.setNickName(namelist);
//         chnSports.addUserToList(chnSports.getListPtrOperators(), &flex);
//         REQUIRE(chnSports.demoteUser("flex") == 0);
        
//         REQUIRE(chnSports.isUserInChannel(flex.getNickName()) == &flex);
//         REQUIRE(chnSports.isUserInList(chnSports.getListPtrOrdinaryUsers(), &flex) == true);
//         REQUIRE(chnSports.isUserInList(chnSports.getListPtrOperators(), &flex) == false);
//     }
// }
