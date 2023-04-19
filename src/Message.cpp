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
    iss >> token;
    command = token;

    while (iss >> token) {
        if (token[0] == ':') {
            std::string trailing = token.substr(1);
            while (iss >> token) {
                trailing += " " + token;
            }
            args.push_back(trailing);
            break;
        } else {
            args.push_back(token);
        }
    }

    // Debug output to see the command and arguments as they are parsed
    std::cout << "Parsed command: " << command << std::endl;
    std::cout << "Parsed arguments: ";
    int i = 0;
    for (std::vector<std::string>::const_iterator it = args.begin(); it != args.end(); ++it) {
        std::cout <<i <<" "<< *it << "\n";
        i++;
    }
    std::cout << std::endl;
}
