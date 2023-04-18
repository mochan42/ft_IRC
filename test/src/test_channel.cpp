/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_channel.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmollenh <fmollenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 18:59:02 by cudoh             #+#    #+#             */
<<<<<<< HEAD:test/src/main_channel.cpp
/*   Updated: 2023/04/17 18:55:23 by fmollenh         ###   ########.fr       */
=======
/*   Updated: 2023/04/16 10:25:10 by cudoh            ###   ########.fr       */
>>>>>>> main:test/src/test_channel.cpp
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
