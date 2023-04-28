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
        if (token[0] == '/') {
            token = token.substr(1);
        }
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
       #if DEBUG
       // Debug output to see the command and arguments as they are parsed
       std::cout << "Parsed command: " << command.back() << std::endl;
       std::cout << "Parsed arguments: ";
       for (std::vector<std::string>::const_iterator it = args.back().begin(); it != args.back().end(); ++it) {
           std::cout << *it << " ";
       }
       std::cout << std::endl;
       #endif
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

//Parses all flags into pairs with args
bool modeParser::extractModeArgsPairs(const std::string& modeString, std::vector<std::string>::const_iterator& it, const std::vector<std::string>::const_iterator& end) {
    char sign = modeString[0];
    for (size_t i = 1; i < modeString.size(); ++i) {
        if (modeString[i] == '+' || modeString[i] == '-') {
            sign = modeString[i];
            continue;
        }
        
        std::string flag(1, sign);
        flag += modeString[i];
        std::string user = "NULL";

        // Check if the mode requires an argument
        if ((modeString[i] == 'k' && sign == '+') ||
            (modeString[i] == 'k' && sign == '-') ||
            (modeString[i] == 'l' && sign == '+') ||
            (modeString[i] == 'o' && (sign == '+' || sign == '-'))) {

            if (it + 1 != end && (*(it + 1))[0] != '+' && (*(it + 1))[0] != '-') {
                user = *(++it);
            } else {
                if ((modeString[i] == 'l' && sign == '+') || modeString[i] == 'k') {
                    flagArgsPairs.push_back(std::make_pair("+e", flag));
                    #if DEBUG
                    std::cout << "Added pair: error, not enough parameters" << std::endl;
                    #endif
                    return false;
                }
            }
        }

        flagArgsPairs.push_back(std::make_pair(flag, user));
        #if DEBUG
        std::cout << "Added pair: (" << flag << ", " << user << ")" << std::endl;
        #endif
    }
    return true;
}



void modeParser::parseCommand(const std::vector<std::string>& args) {
    std::vector<std::string>::const_iterator it = args.begin();

    if (it != args.end()) {
        channel = *it++;
    }

    flagArgsPairs.clear();
    // Process each mode string
    while (it != args.end()) {
        // Skip non-mode strings
        while (it != args.end() && ((*it)[0] != '+' && (*it)[0] != '-')) {
            ++it;
        }
        
        if (it != args.end()) {
            std::vector<std::string>::const_iterator prev_it = it;
            if (!extractModeArgsPairs(*it, it, args.end())) {
                #if DEBUG
                std::cout << "Invalid arguments for command /mode" << std::endl;
                #endif
                break;
            }
            // Increment it only if it wasn't incremented in extractModeArgsPairs
            if (it == prev_it) {
                ++it;
            }
        }
    }
}



