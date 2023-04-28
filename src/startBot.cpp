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
    bot.connect("localhost", port);
	bot.send_line("PASS " + password);
	bot.send_line("NICK " + nickname);
    bot.send_line("USER Bot");
	bot.send_line("JOIN #BotHome1");

	signal(SIGINT, signal_handler);

    while (!stop) {
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
	bot.send_line("QUIT");
    bot.disconnect();

    return 0;
}
