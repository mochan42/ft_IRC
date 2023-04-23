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
    while ((end = user_input.find_first_of("\r\n", start)) != std::string::npos) {
    std::string line = user_input.substr(start, end - start);
    if (end < user_input.length() && user_input[end] == '\r' && user_input[end+1] == '\n') {
        end += 2;
    } else if (end < user_input.length() && user_input[end] == '\n') {
        end += 1;
    }
    input_lines.push_back(line);
    start = end;
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
       std::cout << "Parsed command: " << command.back() << std::endl;
       std::cout << "Parsed arguments: ";
       for (std::vector<std::string>::const_iterator it = args.back().begin(); it != args.back().end(); ++it) {
           std::cout << *it << " ";
       }
       std::cout << std::endl;
    }
}

// Constructors
modeParser::modeParser(const std::vector<std::string>& args) {
    parseCommand(args);
}

// Copy constructor
modeParser::modeParser(const modeParser& other) : channel(other.channel), flagArgsPairs(other.flagArgsPairs) {
}

// Assignment operator
modeParser& modeParser::operator=(const modeParser& other) {
    if (this != &other) {
        channel = other.channel;
        flagArgsPairs = other.flagArgsPairs;
    }
    return *this;
}

// Destructor
modeParser::~modeParser() {
}

// Getters
std::string modeParser::getChannel() const {
    return channel;
}

std::vector<std::pair<std::string, std::string> > modeParser::getflagArgsPairs() const {
    return flagArgsPairs;
}

//Parses all flags into pairs with username they belong to, in case of multiple commands applied for same user
// one pair for each flag is used.
// in case the flag is l the second half of the pair will be std::string with limit stored.
void modeParser::parseCommand(const std::vector<std::string>& args) {
    std::vector<std::string>::const_iterator it = args.begin();

    if (it != args.end()) {
        channel = *it++;
    }

    while (it != args.end()) {
        std::string modePart = *it++;
        char sign = modePart[0];
        std::string user = "";
        if (it != args.end()) {
            user = *it++;
        }
        for (size_t i = 1; i < modePart.size(); ++i) {
            std::string flag(1, sign);
            flag += modePart[i];
            flagArgsPairs.push_back(std::make_pair(flag, user));
        }
    }
}
