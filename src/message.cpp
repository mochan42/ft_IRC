#include "../inc/Message.hpp"

Message::Message(const std::string& user_input) {
    parse(user_input);
}

Message::Message(const Message& other) {
    prefix = other.prefix;
    command = other.command;
    args = other.args;
}

Message& Message::operator=(const Message& other) {
    if (this == &other) {
        return *this;
    }

    prefix = other.prefix;
    command = other.command;
    args = other.args;

    return *this;
}

Message::~Message() {
}

std::string Message::getPrefix() const {
    return prefix;
}

std::string Message::getCommand() const {
    return command;
}

std::vector<std::string> Message::getArguments() const {
    return args;
}

void Message::parse(const std::string& user_input) {
    std::istringstream iss(user_input);
    std::string token;
    bool hasPrefix = false;
    bool hasCommand = false;

    while (iss >> token) {
        if (!hasPrefix && token[0] == ':') {
            prefix = token.substr(1);
            hasPrefix = true;
        } else if (!hasCommand) {
            command = token;
            hasCommand = true;
        } else {
            args.push_back(token);
        }
    }

    std::transform(command.begin(), command.end(), command.begin(), ::toupper);
}

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
