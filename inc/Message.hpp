#ifndef MESSAGE_HPP
#define MESSAGE_HPP

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

    std::vector<std::string> getPrefix() const;
    std::vector<std::string> getCommand() const;
    std::vector<std::vector<std::string> > getArguments() const;

private:
    std::vector<std::string> prefix;
    std::vector<std::string> command;
    std::vector<std::vector<std::string> > args;

    void parse(const std::string& user_input);
};

#endif
