/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startBot.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjairus <tjairus@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 23:20:23 by tjairus           #+#    #+#             */
/*   Updated: 2023/05/04 13:48:07 by tjairus          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <signal.h>
#include "../inc/Bot.hpp"

volatile sig_atomic_t stop = 0;

void signal_handler(int signal) {
    if (signal == SIGINT) {
        stop = 1;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <nickname> <port> <password>" << std::endl;
        return 1;
    }

    std::string nickname(argv[1]);
    int port = atoi(argv[2]);
    std::string password(argv[3]);

    Bot bot(nickname, password);
    if (!bot.connect("localhost", port)) {
    std::cerr << "Error connecting to server" << std::endl;
    return 1;
    }
    bot.set_answers("src/botlib");
	bot.send_line("PASS " + password);
	bot.send_line("NICK " + nickname);
    bot.send_line("USER Bot");
	bot.send_line("JOIN #Bot");

	signal(SIGINT, signal_handler);

    while (!stop && !bot.get_nickname_in_use()) {
        Bot::IRCMsg msg;
        if (bot.get_msg(msg, 5)) {
            std::cout << msg.sender << " @ " << msg.channel << ": " << msg.msg_text << std::endl;

            // Call process_message
            std::pair<std::string, std::string> result = bot.process_message(msg);
            std::string target = result.first;
            std::string response = result.second;

            // If the response is not empty, send it to the target (channel or sender)
            if (!response.empty()) {
                std::string privmsg = "PRIVMSG " + target + " :" + response;
                bot.send_line(privmsg);
            }
        }
    }
    if (bot.get_nickname_in_use()) {
        bot.disconnect();
    }
    return 1;
	bot.send_line("QUIT");
    bot.disconnect();

    return 0;
}
