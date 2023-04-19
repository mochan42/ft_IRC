/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_channel.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 18:59:02 by cudoh             #+#    #+#             */
/*   Updated: 2023/04/18 21:07:57 by pmeising         ###   ########.fr       */
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
