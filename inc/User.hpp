#ifndef USER_HPP
# define USER_HPP

# include "Server.hpp"
# include "Channel.hpp"
# include <string.h>
# include <sstream>
# include <vector>
# include <poll.h>

class User
{
	private:
		Server 						*_server;
		int							_userFd;
		long						_ip;
		std::string					_userName;
		std::string					_nickName;
		std::string					_realName;
		bool						_isRegistered;
		std::list<Channel *>		_channelList;

	public:
		User(int fd, long ip, Server *ircserver);
		User&		operator=(User &src);
		~User();

		int			getFd(void);
		long		getIP(void);
		void		setNickName(const std::vector<std::string>& args);
		std::string	getNickName(void);
		void		setUserName(const std::vector<std::string>& args);
		std::string	getUserName(void);
		void		setRealName(const std::vector<std::string>& args);
		std::string	getRealName(void);




		/**
		 * @brief 
		 * function to call the received command.
		 *
		 * @param command std::string
		 * @param args std::vector < std::string >
		 */
		void		executeCommand(std::string command, std::vector<std::string>& args);


		// void		changeTopic(channel& currentChannel, std::string newTopic);
		// channel&	createChannel(std::string channelName);
		// void 		inviteUser(channel& currentChannel, std::string nickName);
		void		joinChannel(std::vector<std::string>& args);
		void		kickUser(std::vector<std::string>& args);
		// void		leaveChannel(channel& currentChannel);
		// void		modifyChannel(std::string channelName, std::string nickName, char mode);
		// std::string	sendNotification(const std::string& msg);

		/**
		 * @brief 
		 * function to send a message to all users in the channel.
		 *
		 * @param args std::vector < std::string >
		 */
		int			sendMsg(std::vector<std::string>& args);


		/**
		 * @brief 
		 * function to send a message to one user.
		 *
		 * @param args std::vector < std::string >
		 */
		int			sendPrivateMsg(std::vector<std::string>& args);


		// std::string	sendPW(Server& ircServer);
		// bool		isOperator(channel& channel);

		std::string	combine_args(std::vector<std::string>::iterator iterBegin, std::vector<std::string>::iterator iterEnd);

		//Exceptions
		class badChannelMask : public std::exception {
			public:
				virtual const char *what() const throw() {
					return ("Bad Channel Mask");
				}
		};
};

#endif