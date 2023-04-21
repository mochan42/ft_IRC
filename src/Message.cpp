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

std::vector<std::string> Message::getPrefix() const {
    return prefix;
}

std::vector<std::string> Message::getCommand() const {
    return command;
}

std::vector<std::vector<std::string> > Message::getArguments() const {
    return args;
}

void Message::parse(const std::string& user_input) {
    std::vector<std::string> input_lines;

    // Split the input into lines
    size_t start = 0, end = 0;
    while ((end = user_input.find("\r\n", start)) != std::string::npos) {
        input_lines.push_back(user_input.substr(start, end - start));
        start = end + 2;
    }

    // Parse each line into a command and arguments
    for (size_t i = 0; i < input_lines.size(); i++) {
        std::istringstream iss(input_lines[i]);
        std::string token;

        // Get the command
        iss >> token;
        command.push_back(token);

        // Parse the arguments
        std::vector<std::string> arg_vec;
        while (iss >> token) {
            if (token[0] == ':') {
                // Argument with spaces, treat as trailing argument
                std::string trailing_arg = token.substr(1);
                while (iss >> token) {
                    trailing_arg += " " + token;
                }
                arg_vec.push_back(trailing_arg);
            } else {
                arg_vec.push_back(token);
            }
        }

        args.push_back(arg_vec);

       // // Debug output to see the command and arguments as they are parsed
       // std::cout << "Parsed command: " << command.back() << std::endl;
       // std::cout << "Parsed arguments: ";
       // for (std::vector<std::string>::const_iterator it = args.back().begin(); it != args.back().end(); ++it) {
       //     std::cout << *it << " ";
       // }
       // std::cout << std::endl;
    }
}
