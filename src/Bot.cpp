#include "../inc/Bot.hpp"

Bot::Bot(const std::string& nickname, const std::string& password) :
        _nickname(nickname), _password(password), _socket(-1),  _nickname_in_use(false) {
}

bool Bot::connect(const std::string& server, int port) {
_socket = socket(AF_INET, SOCK_STREAM, 0);
if (_socket < 0) {
perror("socket");
return false;
}

struct hostent *he;
struct sockaddr_in their_addr;

if ((he = gethostbyname(server.c_str())) == NULL) {
    perror("gethostbyname");
    return false;
}

their_addr.sin_family = AF_INET;
their_addr.sin_port = htons(port);
their_addr.sin_addr = *((struct in_addr *) he->h_addr);
memset(&(their_addr.sin_zero), 0, 8);

if (::connect(_socket, (struct sockaddr *) &their_addr, sizeof(struct sockaddr)) == -1) {
    perror("connect");
    return false;
}

return true;
}


void Bot::set_answers(const std::string& file_name) {
    try {
        std::ifstream file(file_name.c_str());
        if (!file.is_open()) {
            throw std::runtime_error("Error opening file");
        }

        std::string line;
        while (std::getline(file, line)) {
            _answers.push_back(line);
        }
        file.close();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

bool Bot::get_nickname_in_use() const {
    return _nickname_in_use;
}

std::string Bot::get_answer(size_t index) const {
    if (index >= _answers.size()) {
        return "";
    }
    return _answers[index];
}

size_t Bot::get_answers_size() const {
    return _answers.size();
}

bool Bot::get_msg(IRCMsg& msg, int timeout_seconds) {
    struct pollfd pfd;
    pfd.fd = _socket;
    pfd.events = POLLIN;

    int poll_result = poll(&pfd, 1, timeout_seconds * 1000);
    if (poll_result > 0 && (pfd.revents & POLLIN)) {
        char buffer[1024];
        ssize_t bytes_received = recv(_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received > 0) {
            buffer[bytes_received] = '\0';
            std::string line(buffer);
            std::istringstream iss(line);

            std::string tmp;
            iss >> tmp;
            if (tmp == "PING") {
                iss >> tmp;
                send_line("PONG " + tmp.substr(1));
            } else if (tmp.substr(0, 1) == ":") {
                msg.sender = tmp.substr(1, tmp.find("!") - 1);
                iss >> tmp;
                msg.msg_type = tmp;
                iss >> msg.channel;

                if (iss.peek() == ' ') {
                    iss.ignore(1); // Ignore the space before the message text
                }
                std::getline(iss, msg.msg_text);

                _message_queue.push(msg); // Add the message to the queue
            }
        }
    }

    if (!_message_queue.empty()) {
        msg = _message_queue.front();
        _message_queue.pop();
        return true;
    }

    return false;
}




std::pair<std::string, std::string> Bot::process_message(const IRCMsg& msg) {
    std::string target;
    std::string response;

    // Process the received message and generate a response
    if (msg.msg_text.substr(0, 3) == "Bot" && msg.msg_text.find("?") == msg.msg_text.length() - 2) {
        if(this->get_answers_size()){
        int random_index = std::rand() % this->get_answers_size();
        response = "Hello, " + msg.sender + ", if in need of motivation, remember following: " + get_answer(random_index);
        }
        else{
        response = "Hello, " + msg.sender + ", I can´t answer that yet, but I´ll find out soon.";
        }
    }
    if (msg.msg_text.find(":Nickname is already in use") != std::string::npos) {
        std::cerr << "Error: nickname is already in use" << std::endl;
        _nickname_in_use = true;
        return std::make_pair("", "");
    }

    // If the message came from a channel, set the target to the channel
    if (!msg.channel.empty() && msg.channel[0] == '#') {
        target = msg.channel;
    } else {
        target = msg.sender;
    }

    return std::make_pair(target, response);
}


void Bot::send_line(const std::string& line) {
    std::string data = line + "\r\n";
    ssize_t bytes_sent = send(_socket, data.c_str(), data.length(), 0);
    if (bytes_sent == -1) {
        std::cerr << "Failed to send data: " << strerror(errno) << std::endl;
    }
}

void Bot::disconnect() {
    if (_socket != -1) {
        close(_socket);
        _socket = -1;
    }
}
