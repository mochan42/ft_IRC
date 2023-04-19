/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_channel.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 18:59:02 by cudoh             #+#    #+#             */
/*   Updated: 2023/04/19 18:17:49 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../inc/catch.hpp"
# include "../../inc/Channel.hpp"


TEST_CASE( "Channel : Channel Constructor", "[Channel]")
{
    
    SECTION("Initialise with valid argument data")
    {
        Channel chnSports("Football", "Bundesliga rocks!");
        REQUIRE(chnSports.getChannelName() == "Football");
        REQUIRE(chnSports.getTopic() == "Bundesliga rocks!");
        REQUIRE(chnSports.getChannelCapacity() == CHN_MAX_USERS);
        REQUIRE(chnSports.getListPtrInvitedUsers() != NULL);
        REQUIRE(chnSports.getListPtrOperators() != NULL);
        REQUIRE(chnSports.getListPtrBannedUsers() != NULL);
        REQUIRE(chnSports.getListPtrOrdinaryUsers() != NULL);
    }
    SECTION("Initialise with Invalid argument data")
    {
        Channel chnSports("", "");
        REQUIRE(chnSports.getChannelName() == "");
        REQUIRE(chnSports.getTopic() == "Bundesliga rocks!");
        REQUIRE(chnSports.getChannelCapacity() == CHN_MAX_USERS);
        REQUIRE(chnSports.getListPtrInvitedUsers() != NULL);
        REQUIRE(chnSports.getListPtrOperators() != NULL);
        REQUIRE(chnSports.getListPtrBannedUsers() != NULL);
        REQUIRE(chnSports.getListPtrOrdinaryUsers() != NULL);
    }
}
