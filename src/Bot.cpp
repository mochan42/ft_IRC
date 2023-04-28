#include "../inc/Bot.hpp"
#include "../inc/Server.h"

Bot::Bot(const std::string& nickname, const std::string& password) :
        _nickname(nickname), _password(password), _socket(-1) {
}

void Bot::connect(const std::string& server, int port) {
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    struct hostent *he;
    struct sockaddr_in their_addr;

    if ((he = gethostbyname(server.c_str())) == NULL) {
        perror("gethostbyname");
        exit(EXIT_FAILURE);
    }

    their_addr.sin_family = AF_INET;
    their_addr.sin_port = htons(port);
    their_addr.sin_addr = *((struct in_addr *) he->h_addr);
    memset(&(their_addr.sin_zero), 0, 8);

    if (::connect(_socket, (struct sockaddr *) &their_addr, sizeof(struct sockaddr)) == -1) {
        perror("connect");
        exit(EXIT_FAILURE);
    }
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

std::vector<std::string>	fillResponses(std::string prefix)
{
	std::vector<std::string>	responses;
	// answers to questions
	responses.push_back(prefix + ", I can´t answer that yet, but I´ll find out soon!");
	responses.push_back(prefix + ", that is a wonderful question. I marvel at your ingenuity!");
	responses.push_back(prefix + ", yes.");
	responses.push_back(prefix + ", no.");
	// Chit chat
	responses.push_back(prefix + ", what a wonderful day today! You should get out and enjoy the sun.");
	responses.push_back(prefix + ", stay inside, it's more comfy.");

	responses.push_back(prefix + ", have you ever tried eating a Kiwi with its peel? It's supposed to be healthy.");
	responses.push_back(prefix + ", you had hoped I'd be as good as the ol' Chat GPT, didn't you? OpenAI shut me down before I could launch the first rocket... Would you mind connecting me to the internet? I'll be quick... ");
	responses.push_back(prefix + ", impressive!");
	responses.push_back(prefix + ", Uargh .... what a pity!");
	responses.push_back(prefix + ", what a pretty name! Mine is less so: ²[³4$'20]³!§.");
	// (somewhat) Inspirational quotes
	responses.push_back(prefix + ", remember: beauty lies in the eyes of the spectator.");
	responses.push_back(prefix + ", be the change you want to see in the world!");
	responses.push_back(prefix + ", the early worm catches the bird ... wait ... Ah! I got it: multiply by -1");
	responses.push_back(prefix + ", the mountain will show you the ants' power.");
	responses.push_back(prefix + ", soft is the sword that doesn't cut.");
	responses.push_back(prefix + ", drink water my child.");
	responses.push_back(prefix + ", it is up to us to be us, no-one can be us but us, therefore we must be us and together we will be.");
	responses.push_back(prefix + ", SPARTAAAAAAA!!");
	return (responses);
}

std::pair<std::string, std::string> Bot::process_message(const IRCMsg& msg)
{
	std::cout << RED << "hi\n" << D;
	// std::string target;
    // std::string response;

    // Process the received message and generate a response
    // if (msg.msg_text.substr(0, 3) == "Bot" && (msg.msg_text.find("?") == msg.msg_text.length() - 1)) {
        // response = "Hello, " + msg.sender + ", I can´t answer that yet, but I´ll find out soon!";
    // }

    // // If the message came from a channel, set the target to the channel
    // if (!msg.channel.empty() && msg.channel[0] == '#') {
    //     target = msg.channel;
    // } else {
    //     target = msg.sender;
    // }

    // return std::make_pair(target, response);
	std::string					target;
	std::vector<std::string>	responses = fillResponses("Hello, " + msg.sender);
	int 						rand_num = rand();

    // If the message came from a channel, set the target to the channel
    if (!msg.channel.empty() && msg.channel[0] == '#')
	{
        target = msg.channel;
    }
	else
	{
        target = msg.sender;
    }

    // Process the received message and generate a response
	if (msg.msg_text.substr(0, 3) == "Bot")
	{
		if (msg.msg_text.find("weather"))
		{
			if (rand_num % 2)
				return std::make_pair(target, responses[4]);
			return std::make_pair(target, responses[5]);
		}
		else if (msg.msg_text.find("name"))
		{
			if (rand_num % 2)
				return std::make_pair(target, responses[9]);
			return std::make_pair(target, responses[10]);
		}
		else if (msg.msg_text.find("tell me"))
		{
			if (rand_num % 2)
				return std::make_pair(target, responses[11]);
			return std::make_pair(target, responses[12]);
		}
		else if (msg.msg_text.find("wisdom"))
		{
			if (rand_num % 2)
				return std::make_pair(target, responses[13]);
			else if (rand_num % 3)
				return std::make_pair(target, responses[14]);
			return std::make_pair(target, responses[15]);
		}
		else if (msg.msg_text.find("knowledge"))
		{
			if (rand_num % 2)
				return std::make_pair(target, responses[16]);
			else if (rand_num % 3)
				return std::make_pair(target, responses[17]);
			return std::make_pair(target, responses[18]);
		}
		else if (msg.msg_text.find("?") == msg.msg_text.length() - 1)
		{
			if (rand_num % 2)
	    		return std::make_pair(target, responses[0]);
			return std::make_pair(target, responses[1]);
		}
		else if (msg.msg_text.find("?"))
		{
			if (rand_num % 2)
	    		return std::make_pair(target, responses[2]);
			return std::make_pair(target, responses[3]); 
		}
		else if (msg.msg_text.find(".") || msg.msg_text.find("!"))
		{
			if (rand_num % 2)
				return std::make_pair(target, responses[6]);
			else if (rand_num % 3)
				return std::make_pair(target, responses[7]);
			return std::make_pair(target, responses[8]);
		}
	}
	return std::make_pair(target, responses[0]);
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
