/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_channel.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 18:59:02 by cudoh             #+#    #+#             */
/*   Updated: 2023/04/15 20:12:00 by cudoh            ###   ########.fr       */
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
