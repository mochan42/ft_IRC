#include"../inc/Message.hpp"
#include"../inc/Utils.hpp"

bool isValidNickname(const std::vector<std::string>& args) {
    if (args.empty()) {
        return false;
    }

    const std::string& nickname = args[0];
    size_t maxLength = 9;

    if (nickname.length() < 1 || nickname.length() > maxLength) {
        return false;
    }

    // Check the first character.
    if (!std::isalpha(nickname[0]) && nickname[0] != '[' && nickname[0] != ']') {
        return false;
    }

    // Check the rest of the characters.
    for (size_t i = 1; i < nickname.length(); ++i) {
        if (!std::isalnum(nickname[i]) && nickname[i] != '[' && nickname[i] != ']' &&
            nickname[i] != '-' && nickname[i] != '_') {
            return false;
        }
    }

    return true;
}

bool isValidChannelName(const std::string& channelName) {
    size_t maxLength = 50; // According to RFC 2812, a channel name can be up to 50 characters long.

    if (channelName.length() < 2 || channelName.length() > maxLength) {
        return false;
    }

    // Check the first character.
    if (channelName[0] != '#' && channelName[0] != '&' && channelName[0] != '+' && channelName[0] != '!') {
        return false;
    }

    // Check the rest of the characters.
    for (size_t i = 1; i < channelName.length(); ++i) {
        if (channelName[i] == ' ' || channelName[i] == ',' || channelName[i] == '\x07') {
            return false;
        }
    }

    return true;
}

void handleNick(const std::vector<std::string>& args) {
    if (isValidNickname(args)) {
        std::cout << "The Nickname is valid and can be set" << std::endl;
		//additional code to actually set the nickname
    } else {
        std::cout << "Error in chosen nickname" << std::endl;
    }
}

void handleJoin(const std::vector<std::string>& args) {
    if (args.empty()) {
        std::cout << "No channel selected" << std::endl;
        return;
    }

    if (isValidChannelName(args[0])) {
        std::cout << "The channel name is valid" << std::endl;
    } else {
        std::cout << "Error in channel name" << std::endl;
    }
}

void handlePrivmsg(const std::vector<std::string>& args) {
    std::cout << "Handling PRIVMSG command" << std::endl;
}

void processIRCCommand(const Message& msg) {
    std::string command = msg.getCommand();
    std::vector<std::string> args = msg.getArguments();

    // Convert the command to uppercase for case-insensitive comparison
    std::transform(command.begin(), command.end(), command.begin(), ::toupper);

    if (command == "NICK") {
        handleNick(args);
    } else if (command == "JOIN") {
        handleJoin(args);
    } else if (command == "PRIVMSG") {
        handlePrivmsg(args);
    } else {
        std::cout << "Unknown command: " << command << std::endl;
    }
}
