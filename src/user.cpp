#include "../inc/user.hpp"

//		*!* CONSTRUCTORS and DESTRUCTOR  *!*
//		------------------------------------


User::User(int fd/*, Server ircserver*/)
{
	// this->_server = ircserver;
	this->_userFd = fd;
	this->_userName = "";
	this->_nickName = "";
	this->_realName = "";
	this->_channelList = std::list<Channel*>();
	this->_isRegistered = false;
	std::cout << "User with fd = " << this->getFd() << " connected with server." << std::endl;
}

User&		User::operator=(User &src)
{
	this->_userFd = src.getFd();
	this->_userName = src.getUserName();
	this->_nickName = src.getNickName();
	this->_realName = src.getRealName();
	this->_channelList = src._channelList;
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

void		User::setNickName(const std::vector<std::string>& args)
{
	_nickName = args[0];
}

std::string		User::getNickName(void)
{
	return (this->_nickName);
}

void		User::setUserName(const std::vector<std::string>& args)
{
	_userName = args[0];
}

std::string		User::getUserName(void)
{
	return (this->_userName);
}

void		User::setRealName(const std::vector<std::string>& args)
{
	_realName = args[0];
}

std::string		User::getRealName(void)
{
	return (this->_realName);
}

//		*!* Command execution  *!*
//		---------------------------

void		User::executeCommand(std::string command, std::vector<std::string>& args)
{
	if (command == "NICK")
		setNickName(args);
	else if (command == "USER")
		setUserName(args);
	else if (command == "REAL")
		setRealName(args);
	// else if (command == "JOIN")
	// 	joinChannel(args);
	// else if (command == "")
	// 	changeTopic(args);
	// else if (command == "")
	// 	inviteUser(args);
	// else if (command == "JOIN")
	// 	joinChannel(args);
	// else if (command == "KICK")
	// 	kickUser(args);
	// else if (command == "PART")
	// 	leaveChannel(args);
	// else if (command == "")
	// 	modifyChannel(args);
	// else if (command == "")
	// 	sendNotification(args);
	else if (command == "PRIVMSG")
	{
		if (args[0].at(0) == '#')
			sendMsg(args);
		else
			sendPrivateMsg(args);
	}
	// else if (command == "PASS")
	// 	sendPW(args);
	// else if (command == "")
	// 	isOperator(args);
	else
	{
		std::cout << "Command \'" << command << "\' not found." << std::endl;
		// send("Command \'" << command << "\' not found.")
	}

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

// void		User::joinChannel(std::string channelName)
// {

// }

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

int		User::sendMsg(std::vector<std::string>& args)
{
	std::list<Channel *>::iterator iterChannel;
	std::list<Channel>::iterator iterChannel2;
	std::vector<std::string>::iterator iterString = args.begin() + 1;

	std::ostringstream msgstream;
	// msgstream << args[1].replace(args[1].find(":"), 1, "");
	msgstream << args[1] << " ";
	for (; iterString != args.end(); ++iterString)
		msgstream << *iterString << " ";
	std::string msg = msgstream.str(); 
	


	for (iterChannel = _channelList.begin(); iterChannel != _channelList.end(); iterChannel++)
	{
		// if (args[0] == (*iterChannel)->getChannelName())
		{
			// (*iterChannel)->broadcastMsg(msg);
			break;
		}
		// Errormessage when no Channel with that name;
	}
	// std::cout << "User " << this->getUserName() << "with fd = " << this->getFd() << "sends a message to channel \'" << /*(*iterChannel)->getChannelName() << */ "\'." << std::endl;
	return (0);


}


int		User::sendPrivateMsg(std::vector<std::string>& args)
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

// bool		User::isOperator(channel& channel)
// {

// }


