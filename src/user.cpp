include "../inc/user.hpp"

//		*!* CONSTRUCTORS and DESTRUCTOR  *!*
//		------------------------------------

User::User()
{

}

User::User&		operator=(const User &src)
{

}

User::~User()
{

}

//		*!* NAME and ID Handling  *!*
//		-----------------------------

void		User::getFd(void)
{

}

void		User::setNickName(std::string nickName)
{

}

void		User::getNickName(void)
{

}

void		User::setUserName(std::string nickName)
{

}

void		User::getUserName(void)
{

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
