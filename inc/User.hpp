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

	public:
		User(int fd, std::string ip, Server *ircserver);
		User&		operator=(User &src);
		~User();

		int			getFd(void);
		std::string	getIP(void);
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


		void		sendNotification(std::vector<std::string>& args);	
		int			sendMsg(std::vector<std::string>& args);
		int			sendPrivateMsg(std::vector<std::string>& args);


		// bool		isOperator(channel& channel);

		std::string	argsToString(std::vector<std::string>::iterator iterBegin, std::vector<std::string>::iterator iterEnd);

//		*!* REPLY LIBRARY  *!*
//		----------------------

		const char		*RPY_welcomeToServer(void);
		const char		*RPY_341_userAddedtoInviteList(std::string otherNick, std::string channel);
		const char		*RPY_inviteMessage(std::string otherNick, std::string channel);
		const char		*RPY_kickedMessage(std::string otherNick, std::string channel);
		const char		*RPY_leaveChannel(std::string channel);
		const char		*RPY_332_channelTopic(std::string channel, std::string topic);
		const char		*RPY_newTopic(std::string channel, std::string newTopic);
		const char		*RPY_352_whoUser(std::string ownNick, std::string channel);
		const char		*RPY_315_endWhoList(std::string channel);

		const char 		*RPY_ERR_commandNotfound(std::string command);
		const char		*RPY_ERR462_alreadyRegistered();
		const char 		*RPY_ERR401_noSuchNickChannel(std::string nickchannel);
		const char 		*RPY_ERR443_alreadyOnChannel(std::string otherNick, std::string channel);
		const char		*RPY_ERR476_badChannelMask(std::string channel);
		const char		*RPY_ERR475_canNotJoinK(std::string channel);
		const char		*RPY_ERR473_canNotJoinI(std::string channel);
		const char		*RPY_ERR471_canNotJoinL(std::string channel);
		const char		*RPY_ERR482_notChannelOp(std::string channel);
		const char		*RPY_ERR441_kickNotOnChannel(std::string otherNick, std::string channel);
		const char		*RPY_ERR403_noSuchChannel(std::string channel);
		const char		*RPY_ERR442_youreNotOnThatChannel(std::string channel);

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