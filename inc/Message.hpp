#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

class Message {
public:
    explicit Message(const std::string& user_input);

    Message(const Message& other);

    Message& operator=(const Message& other);

    ~Message();

    std::string getCommand() const;

    std::vector<std::string> getArguments() const;

private:
    std::string command;
    std::vector<std::string> arguments;

    void parseMessage(const std::string& user_input);
};

void processIRCCommand(const Message& msg);

#endif //MESSAGE_HPP