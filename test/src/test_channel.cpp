/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_channel.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 18:59:02 by cudoh             #+#    #+#             */
/*   Updated: 2023/04/22 19:31:30 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../inc/catch.hpp"
# include "../../inc/Channel.hpp"


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
        REQUIRE(chnSports.getListPtrInvitedUsers() == NULL);
        REQUIRE(chnSports.getListPtrOperators() == NULL);
        REQUIRE(chnSports.getListPtrOrdinaryUsers() == NULL);
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
        chnSports.addUserToList(chnSports.getListPtrOrdinaryUsers(), &flex);
     
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
        chnSports.removeUserFromList(chnSports.getListPtrOperators(), &flex);
        chnSports.addUserToList(chnSports.getListPtrOrdinaryUsers(), &flex);
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
        chnSports.removeUserFromList(chnSports.getListPtrOperators(), &flex);
        
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
