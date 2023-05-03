#ifndef SERVER_HPP
# define SERVER_HPP
# include <unistd.h> 
# include <exception>
# include <string>
# include <cstdlib> // for strtol
# include <cctype> // for isdigit
# include <cstring> // for strlen
# include <limits.h> // for INT_MAX and INT_MIN
# include <iostream>
# include <sstream> // for pingClient()
# include <fstream>
# include <map>
# include <list>
# include <sys/socket.h>  // to create socket
# include <netdb.h> // for getnameinfo()
# include <netinet/in.h> // to use struct addr_in which is used to represnt an IP address and port number.
# include <fcntl.h>
# include <poll.h>
# include <arpa/inet.h> // for inet_ntop()
# include "User.hpp"
# include "Channel.hpp"
# include "Message.hpp"
# include <ctime> // for pingClient()


#define MIN_PORT_NUMBER	1024      // Registered Ports (1.024 - 49.151) -----   Dynamically Allocated Ports (49.152 - 65.535):
#define MAX_PORT_NUMBER	65535
#define BACKLOG			5
#define BUFFER_SIZE		1024
#define MAX_CONNECTIONS	1024
#define TIME_OUT		30000    // Server will ping client if no data is received from client after 2 min

class User;

class Channel;

class Server
{
	private:
		Server();
		Server(const Server& obj);
		Server&	operator=(const Server& rhs);

		unsigned int					_port;
		int								_listeningSocket;
		const std::string				_password;
		std::string						_serverName;
		std::string						_serverIP;
		std::map<int, User*>			_users;
		std::list<std::string>			_operators;
		std::map<int, std::string>		_messages;
		std::map<std::string, Channel*>	_channels;

	public:
		int								num_fds;
		struct pollfd					fds[MAX_CONNECTIONS + 1]; // +1 is to acommodate the Listening socket for the server.
		Server(unsigned int port, const std::string& password);
		~Server();

		
		// getters
		Channel*						getChannel(const std::string& channel) const;
		unsigned int					getPort(void) const;
		int								getListeningSocket(void) const;
		User*							getUser(std::string nickName);
		User*							getUserByFd(int client_socket);
		std::string						getServerName();
		std::string						getServerIP();

		// setters
		void							setListeningSocket (int n);
		void							setPort(int inputPortNumber);
		void							setServerIP(std::string setServerIP);

		// member functions
		bool							verifyPassword(const std::string& password) const;
		void							pingClient(int client_socket);
		Channel*						createChannel(const std::string& channel_name, User* user);
		void							createSocket();
		void							makeListeningSocketReusable();
		void							setSocketToNonBlocking();
		void							bindListeningSocketToServerPort(sockaddr_in addr);
		void							listenToClients();
		void							handle_new_connection(int server_socket, struct pollfd *fds, int *num_fds);
		void							handle_client_data(int client_socket, char *buffer, int buffer_size);
		void							connectUser(int* ptrNum_fds, int* ptrNum_ready_fds, char* buffer);
		void							setupServer();
		void							remUser(const int& user_fd);
		void							remChannel(const std::string& channel_name);
		void							deleteChannel(Channel *channelPtr);

		// exception class
		class ErrorInternal : public std::exception
		{
			virtual const char *what() const throw()
			{
				return exception::what();
			}
		};
};

int	checkIsDigit(char *s);
int	checkOutOfRange(char *s);
int	checkPort(char *port);

#endif
