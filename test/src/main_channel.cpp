/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_channel.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmollenh <fmollenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 18:59:02 by cudoh             #+#    #+#             */
/*   Updated: 2023/04/17 18:55:23 by fmollenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/catch.hpp"
# include "../../inc/Channel.hpp"


TEST_CASE( "Channel : Channel Constructor", "[Channel]")
{
    
    SECTION("Check that Initialization is ok")
    {
        Channel sport("Football", "Bundesliga rocks!");
        std::string sportName = "Football";
        REQUIRE(sport.getTopic == sportName);
    }
}
