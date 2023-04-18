#include "../inc/user.hpp"

//		*!* CONSTRUCTORS and DESTRUCTOR  *!*
//		------------------------------------

User::User(int fd, long ip)
{
	this->_userFd = fd;
	this->_ip = ip; //as a string or can we save it differently?
	this->_userName = "";
	this->_nickName = "";
	this->_realName = "";
	// this->_channelList = std::list<Channel*>();
	this->_isRegistered = false;
	std::cout << "User with fd = " << this->getFd() << " connected with server." << std::endl;
}

User&		User::operator=(User &src)
{
	this->_userFd = src.getFd();
	this->_userName = src.getUserName();
	this->_nickName = src.getNickName();
	this->_realName = src.getRealName();
	// this->_channelList = src._channelList;
	this->_isRegistered = src._isRegistered;
	return (*this);
}

User::~User()
{
	std::cout << "User " << this->getUserName() << " removed from server." << std::endl;
}

//		*!* NAME and ID Handling  *!*
//		-----------------------------

int		User::getFd(void)
{
	return (this->_userFd);
}

void		User::setNickName(std::string nickName)
{
	_nickName = nickName;
}

std::string		User::getNickName(void)
{
	return (this->_nickName);
}

void		User::setUserName(std::string userName)
{
	_userName = userName;
}

std::string		User::getUserName(void)
{
	return (this->_userName);
}

void		User::setRealName(std::string realName)
{
	_realName = realName;
}

std::string		User::getRealName(void)
{
	return (this->_realName);
}

//		*!* Command execution  *!*
//		---------------------------

void		User::executeCommand(std::string command, std::vector<std::string> args)
{
	if (command == "sendMsg")
		sendMsg(args);
	else if (command == "sendPrivateMsg")
		sendPrivateMsg(args);
	else
		std::cout << "Command \'" << command << "\' not found." << std::endl;
}


//		*!* CHANNEL interacting  *!*
//		----------------------------


// void		User::changeTopic(channel& currentChannel, std::string newTopic)
// {

// }

// channel&	User::createChannel(std::string channelName)
// {

// }

// void 		User::inviteUser(channel& currentChannel, std::string nickName)
// {

// }

/* void		User::joinChannel(std::string channelName)
{
	channel *chptr = server->searchChannel(channelName);
	if (chptr == NULL) //Create channel
	{
		chptr = server->createChannel(channelName);
		chptr->addUserToList(*this);
		chptr->addUserOperatorList(*this);
	}
	else { //join channel
		//check if we are allowed to join (invite only)
		chptr->addUserToList(*this);
	}
} */

// void		User::kickUser(channel& channelToBeKickedOutOf, std::string nickName)
// {

// }

// void		User::leaveChannel(channel& currentChannel)
// {

// }

// void		User::modifyChannel(std::string channelName, std::string nickName, char mode)
// {

// }

// //		*!* MESSAGES  *!*
// //		------------------------------------


// std::string	User::sendNotification(const std::string& msg)
// {

// }

int		User::sendMsg(const std::vector<std::string> args)
{
	(void) args;
	std::cout << "User " << this->getUserName() << "with fd = " << this->getFd() << "sends a message to channel \'" << /* args[2] << */ "\'." << std::endl;
	return (0);
}

int		User::sendPrivateMsg(const std::vector<std::string> args)
{
	(void) args;
	std::cout << "User " << this->getUserName() << "with fd = " << this->getFd() << "sends a message to User \'" << /* args[2] << */ "\' with fd = " << /*args[3] << */ std::endl;
	return (0);
}


// //		*!* OTHERS  *!*
// //		------------------------------------


// std::string	User::sendPW(Server& ircServer)
// {

// }
