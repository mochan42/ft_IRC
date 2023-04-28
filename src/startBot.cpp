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
	bot.send_line("USER bot 0 * :bot");
	bot.send_line("NICK " + nickname);
	bot.send_line("JOIN #BotHome1");

	signal(SIGINT, signal_handler);

    while (!stop) {
        Bot::IRCMsg msg;
        if (bot.get_msg(msg, 5)) {
            std::cout << msg.sender << " @ " << msg.channel << ": " << msg.msg_text << std::endl;
        }
    }
	bot.send_line("QUIT");
    bot.disconnect();

    return 0;
}
