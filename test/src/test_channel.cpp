/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_channel.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 18:59:02 by cudoh             #+#    #+#             */
/*   Updated: 2023/04/16 10:25:10 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/catch.hpp"
//# include "../../inc/Channel.hpp"


TEST_CASE( "Channel : Channel Constructor", "[Channel]")
{
    
    SECTION("Check that Initialization is ok")
    {
        //Channel sport("Football", "Bundesliga rocks!");
        int numbers = 50;
        std::string sportName = "Football";
        REQUIRE(numbers == 50);
    }
}
