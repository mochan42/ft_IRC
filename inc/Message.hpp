#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>

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

class modeParser {
public:
    // Constructors
    explicit modeParser(const std::vector<std::string>& args);

    // Copy constructor
    modeParser(const modeParser& other);

    // Assignment operator
    modeParser& operator=(const modeParser& other);

    // Destructor
    ~modeParser();

    // Getters
    std::string getChannel() const;
    std::vector<std::pair<std::string, std::string> > getflagArgsPairs() const;

private:
    bool extractModeArgsPairs(const std::string& modeString, std::vector<std::string>::const_iterator& it,
        const std::vector<std::string>::const_iterator& end);
    void parseCommand(const std::vector<std::string>& args);
    std::string channel;
    std::vector<std::pair<std::string, std::string> > flagArgsPairs;
};

#endif
