#ifndef USER_HPP
# define USER_HPP

# include "server.hpp"
// # include "Channel.hpp"
# include <string.h>
# include <iostream>
# include <list>
# include <vector>
# include <poll.h>


class User
{
	private:
		int							_userFd;
		std::string					_userName;
		std::string					_nickName;
		std::string					_realName;
		bool						_isRegistered;
		//Server						*server;
		//std::list<Channel*>			_channelList;

	public:
					User();
					User(pollfd &client);
		User&		operator=(User &src);
					~User();

		int			getFd(void);
		void		setNickName(std::string nickName);
		std::string	getNickName(void);
		void		setUserName(std::string userName);
		std::string	getUserName(void);
		void		setRealName(std::string realName);
		std::string	getRealName(void);

		void		executeCommand(std::string command, std::vector<std::string> args);
		// void		changeTopic(channel& currentChannel, std::string newTopic);
		// channel&	createChannel(std::string channelName);
		// void 		inviteUser(channel& currentChannel, std::string nickName);
		void		joinChannel(std::string channelName);
		// void		kickUser(channel& channelToBeKickedOutOf, std::string nickName);
		// void		leaveChannel(channel& currentChannel);
		// void		modifyChannel(std::string channelName, std::string nickName, char mode);
		// std::string	sendNotification(const std::string& msg);
		int			sendMsg(const std::vector<std::string> args);
		int			sendPrivateMsg(const std::vector<std::string> args);
		// std::string	sendPW(Server& ircServer);
		// bool		isOperator(channel& channel);


		//Exceptions
		class channelNotFoundException : public std::exception {
			public:
				virtual const char *what() const throw() {
					return ("Channel doesn't exist");
				}
		};
};

#endif