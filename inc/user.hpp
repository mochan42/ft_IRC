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
		std::list<Channel>		_channelList;
		std::list<std::string>	_inputTokens

	public:
					User(pollfd &client);
		User&		operator=(const User &src);
					~User();

		void		getFd(void);
		void		setNickName(std::string nickName);
		void		getNickName(void);
		void		setUserName(std::string userName);
		void		getUserName(void);
		void		setRealName(std::string realName);
		void		getRealName(void);

		User&		newUser(void);
		void		changeTopic(channel& currentChannel, std::string newTopic);
		channel&	createChannel(std::string channelName);
		void 		inviteUser(channel& currentChannel, std::string nickName);
		void		joinChannel(std::string channelName);
		void		kickUser(channel& channelToBeKickedOutOf, std::string nickName);
		void		leaveChannel(channel& currentChannel);
		void		modifyChannel(std::string channelName, std::string nickName, char mode);
		std::string	sendNotification(const std::string& msg);
		std::string	sendMsg(const std::string& msg);
		std::string	sendPrivateMsg(const std::string& msg);
		std::string	sendPW(Server& ircServer);
		bool		isOperator(channel& channel);
}