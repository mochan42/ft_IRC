#ifndef MESSAGE_HPP
 #define MESSAGE_HPP

#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Message {
public:
    Message(const std::string& user_input);
    Message(const Message& other);
    Message& operator=(const Message& other);
    ~Message();

    std::string getPrefix() const;
    std::string getCommand() const;
    std::vector<std::string> getArguments() const;

private:
    void parse(const std::string& user_input);

    std::string prefix;
    std::string command;
    std::vector<std::string> args;
};

#endif //MESSAGE_HPP