/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 20:01:16 by cudoh             #+#    #+#             */
/*   Updated: 2023/04/16 11:43:20 by cudoh            ###   ########.fr       */
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
