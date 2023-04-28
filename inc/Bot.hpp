#ifndef BOT_HPP
#define BOT_HPP

#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <queue>
#include <iostream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <poll.h>
#include <cstdio>

class Bot {
public:
    struct IRCMsg {
        std::string sender;
        std::string channel;
        std::string msg_type;
        std::string msg_text;
    };

    Bot(const std::string& nickname, const std::string& password);
    void connect(const std::string& server, int port);
    bool get_msg(IRCMsg& msg, int timeout_seconds);
    std::pair<std::string, std::string> process_message(const IRCMsg& msg);
	void send_line(const std::string& line);
	void disconnect();

private:
    std::string 			_nickname;
    std::string 			_password;
    int 					  _socket;
	std::queue<IRCMsg> _message_queue;
};

#endif // BOT_HPP
