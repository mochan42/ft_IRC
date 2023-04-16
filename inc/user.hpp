#ifndef USER_HPP
# define USER_HPP

# include "server.hpp"
# include "channel.hpp"
# include <string.h>
# include <iostream>
# include <list>
# include <poll.h>


class User
{
	private:
		int						_userFd;
		std::string				_userName;
		std::string				_nickName;
		std::string				_realName;
		bool					_isRegistered;
		std::list<Channel*>		_channelList;
		std::list<std::string>	_inputTokens;

	public:
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
		// void		joinChannel(std::string channelName);
		// void		kickUser(channel& channelToBeKickedOutOf, std::string nickName);
		// void		leaveChannel(channel& currentChannel);
		// void		modifyChannel(std::string channelName, std::string nickName, char mode);
		// std::string	sendNotification(const std::string& msg);
		std::vector<std::string>	sendMsg(const std::vector<std::string> args);
		std::vector<std::string>	sendPrivateMsg(const std::vector<std::string> args);
		// std::string	sendPW(Server& ircServer);
		// bool		isOperator(channel& channel);
};

#endif