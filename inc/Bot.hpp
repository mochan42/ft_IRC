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
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <poll.h>
#include <cstdio>
#include <ctime>

class Bot {
public:
    struct IRCMsg {
        std::string 					sender;
        std::string 					channel;
        std::string						msg_type;
        std::string						msg_text;
    };

    Bot(const std::string& nickname, const std::string& password);
    bool                                connect(const std::string& server, int port);
    bool                                get_nickname_in_use() const;
    bool                                get_msg(IRCMsg& msg, int timeout_seconds);
    std::pair<std::string, std::string> process_message(const IRCMsg& msg);
    void                                set_answers(const std::string& file_name);
    std::string                         get_answer(size_t index) const;
    size_t                              get_answers_size() const;
	void                                send_line(const std::string& line);
	void                                disconnect();

private:
    std::string 			              _nickname;
    std::string 			              _password;
    int 					                  _socket;
	std::queue<IRCMsg>                _message_queue;
    std::vector<std::string>        _answers;
    bool                            _nickname_in_use;
};

#endif
