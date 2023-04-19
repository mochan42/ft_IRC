#include "../inc/user.hpp"

//		*!* CONSTRUCTORS and DESTRUCTOR  *!*
//		------------------------------------

User::User(pollfd &client)
{
	this->_userFd = client.fd;
	this->_userName = "";
	this->_nickName = "";
	// this->_realName = "";
	this->_channelList = std::list<Channel>();
	this->_isRegistered = false;
	this->_inputTokens = std::list<std::string>();
}

User::User&		operator=(const User &src)
{
	this->_userFd = src.getFd();
	this->_userName = src.getUserName();
	this->_nickName = src.getNickName();
	// this->_realName = src.getRealName();
	this->_channelList = src._channelList;
	this->_isRegistered = src._isRegistered;
	this->_inputTokens = src._inputTokens;
}

User::~User()
{
	std::cout << "User " << this->getUserName() << " removed from server." << std::endl;
}

//		*!* NAME and ID Handling  *!*
//		-----------------------------

void		User::getFd(void)
{
	return (this->_userFd);
}

void		User::setNickName(std::string nickName)
{
	_nickName = nickName;
}

void		User::getNickName(void)
{
	return (this->_nickName);
}

void		User::setUserName(std::string userName)
{
	_userName = userName;
}

void		User::getUserName(void)
{
	return (this->_userName);
}

void		User::setRealName(std::string realName)
{
	_realName = realName;
}

void		User::getRealName(void)
{
	return (this->_realName);
}

//		*!* CHANNEL interacting  *!*
//		----------------------------


void		User::changeTopic(channel& currentChannel, std::string newTopic)
{

}

channel&	User::createChannel(std::string channelName)
{

}

void 		User::inviteUser(channel& currentChannel, std::string nickName)
{

}

void		User::joinChannel(std::string channelName)
{

}

void		User::kickUser(channel& channelToBeKickedOutOf, std::string nickName)
{

}

void		User::leaveChannel(channel& currentChannel)
{

}

void		User::modifyChannel(std::string channelName, std::string nickName, char mode)
{

}

//		*!* MESSAGES  *!*
//		------------------------------------


std::string	User::sendNotification(const std::string& msg)
{

}

std::string	User::sendMsg(const std::string& msg)
{

}

std::string	User::sendPrivateMsg(const std::string& msg)
{

}


//		*!* OTHERS  *!*
//		------------------------------------


std::string	User::sendPW(Server& ircServer)
{

}

bool		User::isOperator(channel& channel)
{

}
