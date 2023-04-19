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
		Server						*_server;
		int							_userFd;
		long						_ip;
		std::string					_pw;
		std::string					_userName;
		std::string					_nickName;
		std::string					_realName;
		bool						_isRegistered;
		std::list<Channel *>		_channelList;

	public:
					User(int fd, long ip, Server* ircserver);
		User&		operator=(User &src);
					~User();

		int			getFd(void);
		long		getIP(void);
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
		// void		joinChannel(std::vector<std::string>& args);
		// void		kickUser(channel& channelToBeKickedOutOf, std::string nickName);
		// void		leaveChannel(std::vector<std::string>& args);
		// void		modifyChannel(std::string channelName, std::string nickName, char mode);


		void		sendNotification(std::vector<std::string>& args);	
		int			sendMsg(std::vector<std::string>& args);
		int			sendPrivateMsg(std::vector<std::string>& args);


		// bool		isOperator(channel& channel);


		//Exceptions
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