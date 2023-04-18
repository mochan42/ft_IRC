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
