#include "../inc/Message.hpp"

Message::Message(const std::string& user_input) {
    parseMessage(user_input);
}

Message::Message(const Message& other) : command(other.command), arguments(other.arguments) {}

Message& Message::operator=(const Message& other) {
    if (this != &other) {
        command = other.command;
        arguments = other.arguments;
    }
    return *this;
}

Message::~Message() {
}

std::string Message::getCommand() const {
    return command;
}

std::vector<std::string> Message::getArguments() const {
    return arguments;
}

void Message::parseMessage(const std::string& user_input) {
    std::istringstream iss(user_input);
    std::string token;

    // Extract the command
    if (std::getline(iss, token, ' ')) {
        command = token;
    }

    // Extract the arguments
    while (std::getline(iss, token, ' ')) {
        arguments.push_back(token);
    }
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

void handleNick(const std::vector<std::string>& args) {
    if (isValidNickname(args)) {
        std::cout << "The Nickname is valid and can be set" << std::endl;
    } else {
        std::cout << "Error in chosen nickname" << std::endl;
    }
}

void handleJoin(const std::vector<std::string>& args) {
    std::cout << "Handling JOIN command" << std::endl;
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