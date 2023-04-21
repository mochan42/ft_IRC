#ifndef USER_HPP
# define USER_HPP

# include "Server.hpp"
# include "Channel.hpp"
# include <string.h>
# include <sstream>
# include <vector>
# include <poll.h>

class Server;

class User
{
	private:
		Server 						*_server;
		int							_userFd;
		std::string					_ip;
		std::string					_pw;
		std::string					_userName;
		std::string					_nickName;
		std::string					_realName;
		bool						_isRegistered;
		std::list<Channel *>		_channelList;
		std::string					_replyMessage;
		bool						_channelMode;						// variable if last channel was joined or created -- true == created

	public:
		User(int fd, std::string ip, Server *ircserver);
		User&		operator=(User &src);
		~User();

		int			getFd(void);
		std::string	getIP(void);
		void		setPw(const std::vector<std::string>& args);
		void		setNickName(const std::vector<std::string>& args);
		std::string	getNickName(void);
		void		setUserName(const std::vector<std::string>& args);
		std::string	getUserName(void);
		void		setRealName(const std::vector<std::string>& args);
		std::string	getRealName(void);

		int			sendMsgToOwnClient(std::string msg);
		int			sendMsgToTargetClient(std::string msg, int targetUserFd);
		void		executeCommand(std::string command, std::vector<std::string>& args);


		// void		changeTopic(channel& currentChannel, std::string newTopic);
		// channel&	createChannel(std::string channelName);
		// void 		inviteUser(channel& currentChannel, std::string nickName);
		void		joinChannel(std::vector<std::string>& args);
		// void		kickUser(std::vector<std::string>& args);
		// void		leaveChannel(std::vector<std::string>& args);
		// void		modifyChannel(std::string channelName, std::string nickName, char mode);


		void		sendNotification(std::vector<std::string>& args);	
		int			sendMsg(std::vector<std::string>& args);
		int			sendPrivateMsg(std::vector<std::string>& args);

		// bool		isOperator(channel& channel);

		std::string	argsToString(std::vector<std::string>::iterator iterBegin, std::vector<std::string>::iterator iterEnd);

//		*!* REPLY LIBRARY  *!*
//		----------------------

		std::string		RPY_welcomeToServer(void);
		std::string 	RPY_newNick(std::string oldNick);
		std::string 	RPY_pass(bool registered);
		std::string 	RPY_createChannel(Channel* channel);
		std::string 	RPY_joinChannel(Channel* channel);
		std::string		RPY_who(Channel *channel);
		std::string		RPY_getModeCreated(Channel *channel);
		std::string		RPY_getModeJoined(Channel *channel);

		std::string		RPY_ERR_commandNotfound(std::string command);

//		*!* EXCEPTIONS  *!*
//		-------------------

		class badChannelMask : public std::exception {
			public:
				virtual const char *what() const throw() {
					return ("Bad Channel Mask");
				}
		};

		class notAnOperator : public std::exception {
			public:
				virtual const char *what() const throw() {
					return (":You're not channel operator");
				}
		};

		class notOnTheChannel : public std::exception {
			public:
				virtual const char *what() const throw() {
					return (":Is not on channel");
				}
		};

		class noSuchChannel : public std::exception {
			public:
				virtual const char *what() const throw()
				{
					return (":No such channel");
				}
		};

		class channelNotFoundException : public std::exception
		{
			public:
				virtual const char *what() const throw()
				{
					return ("Channel doesn't exist.");
				}
		};

		class SendToTargetCLientException : public std::exception
		{
			public:
				virtual const char *what() const throw()
				{
					return ("Error while sending message to target client.");
				}
		};

		class SendToOwnCLientException : public std::exception
		{
			public:
				virtual const char *what() const throw()
				{
					return ("Error while sending message to own client.");
				}
		};
};

#endif