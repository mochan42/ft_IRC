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
		bool						_usernameSet;
		std::list<Channel *>		_channelList;
		std::string					_replyMessage;
		int							_userPort;

	public:
		User(int fd, std::string ip, Server *ircserver);
		User&		operator=(User &src);
		~User();

		int			getFd(void);
		std::string	getIP(void);
		int			getPort(void);
		void		setPort(int setUserPort);
		void		setServerPw(const std::vector<std::string>& args);
		void		setNickName(const std::vector<std::string>& args);
		std::string	getNickName(void);
		void		setUserName(std::vector<std::string>& args);
		std::string	getUserName(void);
		void		setRealName(const std::vector<std::string>& args);
		std::string	getRealName(void);

		int			sendMsgToOwnClient(std::string msg);
		int			sendMsgToTargetClient(std::string msg, int targetUserFd);
		void		executeCommand(std::string command, std::vector<std::string>& args);

		void		who(std::vector<std::string>& args);
		void		changeTopic(std::vector<std::string>& args);
		// channel&	createChannel(std::string channelName);
		void 		inviteUser(std::vector<std::string>& args);
		void		joinChannel(std::vector<std::string>& args);
		void		kickUser(std::vector<std::string>& args);
		void		leaveChannel(std::vector<std::string>& args);
		// void		modifyChannel(std::string channelName, std::string nickName, char mode);
		void		mode(std::vector<std::string>& args);

		void		sendNotification(std::vector<std::string>& args);	
		int			sendChannelMsg(std::vector<std::string>& args);
		int			sendPrivateMsg(std::vector<std::string>& args);

		void 		setInviteOnly(const std::string& channel);
		void 		remoInviteOnly(const std::string& channel);
		void 		setTopicRestrictions(const std::string& channel);
		void 		removeTopicRestrictions(const std::string& channel);
		void 		setChannelKey(const std::string& channel, const std::string& key);
		void 		removeChannelKey(const std::string& channel);
		void 		giveChanopPrivileges(const std::string& channel, const std::string& username);
		void 		removeChanopPrivileges(const std::string& channel, const std::string& username);
		void 		setUserLimit(const std::string& channel, int limit);
		void 		removeUserLimit(const std::string& channel);

		// bool		isOperator(channel& channel);

		std::string	argsToString(std::vector<std::string>::iterator iterBegin, std::vector<std::string>::iterator iterEnd);

//		*!* REPLY LIBRARY  *!*
//		----------------------

		std::string		RPY_welcomeToServer(void);
		std::string 	RPY_newNick(std::string oldNick);
		std::string 	RPY_pass(bool registered);
		std::string		RPY_ChannelMsg(std::string message, Channel* channel);
		std::string		RPY_PrivateMsg(std::string message, User* target);
		std::string		RPY_ChannelNotification(std::string message, Channel* channel);
		std::string		RPY_PrivateNotification(std::string message, User* target);
		std::string		RPY_joinChannelBroadcast(Channel* channel, bool op);
		std::string 	RPY_createChannel(Channel* channel);
		std::string 	RPY_Who(Channel* channel);
		std::string 	RPY_joinChannel(Channel* channel);
		std::string		RPY_getModeCreated(Channel *channel);
		std::string		RPY_getModeJoined(Channel *channel);


		std::string		RPY_341_userAddedtoInviteList(std::string otherNick, std::string channel);
		std::string		RPY_inviteMessage(std::string otherNick, std::string channel);
		std::string		RPY_kickedMessage(std::string otherNick, std::string channel);
		std::string		RPY_leaveChannel(std::string channel);
		std::string		RPY_332_channelTopic(std::string channel, std::string topic);
		std::string		RPY_newTopic(std::string channel, std::string newTopic);
		std::string		RPY_352_whoUser(User *user, std::string channel, bool op);
		// std::string		RPY_352_whoUser(std::string recipientNick, std::string channel, bool op);
		std::string		RPY_315_endWhoList(std::string channel);



		std::string 	RPY_ERR_commandNotfound(std::string command);
		std::string		RPY_ERR462_alreadyRegistered();
		std::string 	RPY_ERR401_noSuchNickChannel(std::string nickchannel);
		std::string 	RPY_ERR443_alreadyOnChannel(std::string otherNick, std::string channel);
		std::string		RPY_ERR476_badChannelMask(std::string channel);
		std::string		RPY_ERR475_canNotJoinK(std::string channel);
		std::string		RPY_ERR473_canNotJoinI(std::string channel);
		std::string		RPY_ERR471_canNotJoinL(std::string channel);
		std::string		RPY_ERR482_notChannelOp(std::string channel);
		std::string		RPY_ERR441_kickNotOnChannel(std::string otherNick, std::string channel);
		std::string		RPY_ERR403_noSuchChannel(std::string channel);
		std::string		RPY_ERR442_youreNotOnThatChannel(std::string channel);

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

		class cannotJoinChannelPW : public std::exception
		{
			public:
				virtual const char *what() const throw()
				{
					return ("Cannot join channel (+k)");
				}
		};

		class cannotJoinChannelIn : public std::exception
		{
			public:
				virtual const char *what() const throw()
				{
					return ("Cannot join channel (+i)");
				}
		};

		class channelCapacity : public std::exception
		{
			public:
				virtual const char *what() const throw()
				{
					return ("Cannot join channel (+l)");
				}
		};
};

#endif