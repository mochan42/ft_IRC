#include "../inc/User.hpp"

//		*!* CONSTRUCTORS and DESTRUCTOR  *!*
//		------------------------------------

User::User(int fd, std::string ip, Server *ircserver)
{
	this->_server = ircserver;
	this->_userFd = fd;
	this->_ip = ip;
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

std::string	User::getIP(void)
{
	return (this->_ip);
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
	//Notice: Some Arguments like Pass can be written like: PASS, pass, Pass ...
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


// void 		User::inviteUser(channel& currentChannel, std::string nickName)
// {

// }

// void		User::joinChannel(std::vector<std::string>& args)
// {
// 	try
// 	{
// 		if (args[0][0] != '#')
// 			throw (badChannelMask());
// 		Channel *chptr = _server->searchChannel(args[0]);
// 		if (chptr == NULL) //Create channel
// 		{
// 			chptr = _server->createChannel(args[0]);
// 			chptr->addUserToList(chptr->getListPtrOperators(), this);
// 		}
// 		else
// 		{ //join channel
// 			//check if we are allowed to join (invite only)
// 			chptr->addUserToList(chptr->getListPtrOrdinaryUsers(), this);
// 		}
// 	}
// 	catch (badChannelMask &e)
// 	{
// 		(void)e;
// 		//:master.ircgod.com 476 flori test :Bad Channel Mask
// 		std::ostringstream msg;
// 		msg << ":" <</* _server->getServerName() <<*/ " 476 " << _nickName << " " << args[0] << " :Bad Channel Mask";
// 		//SEND MESSAGE HERE: msg.str();
// 	}
// }

// void		User::kickUser(std::vector<std::string>& args)
// {
// 	std::string channel = args[0];
// 	std::string nick = args[1];
// 	std::string reason = argsToString(args.begin() + 2, args.end());
// 	Channel *channelPtr;
// 	User	*tmpUser;
	
// 	try
// 	{
// 		channelPtr = _server->searchChannel(channel);
// 		if (!channelPtr->isUserInList(channelPtr->getListPtrOperators(), this))
// 			throw (notAnOperator());

// 		if (tmpUser = channelPtr->isUserInChannel(nick))
// 		{
// 			//write broadcastmessage: ":<Nick>!<Nick_USER@IP> KICK <channel> <kickedNick> <kickedNick>"
// 			std::ostringstream brmsg;
// 			brmsg << ":" << _nickName << "!" << _userName << "@" << _ip << " KICK " << channel << nick;
// 			//SEND MSG
			
// 			if (channelPtr->isUserInList(channelPtr->getListPtrOperators(), tmpUser))
// 				channelPtr->removeUserFromList(channelPtr->getListPtrOperators(), tmpUser);
// 			if (channelPtr->isUserInList(channelPtr->getListPtrOrdinaryUsers(), tmpUser))
// 				channelPtr->removeUserFromList(channelPtr->getListPtrOrdinaryUsers(), tmpUser);
// 		}
// 		else
// 			throw (notOnTheChannel());
// 	}
// 	catch (notAnOperator &e)
// 	{
// 		//write error: :<ServerName> 482 <Nick> <channel> :You're not channel operator
// 		std::ostringstream msg;
// 		msg << ":" <</* _server->getServerName() <<*/ " 482 " << _nickName << " " << channel << " :You're not channel operator";
// 		//SEND ERROR MESSAGE!!!
// 	}
// 	catch (notOnTheChannel &e)
// 	{
// 		//write error: ":<ServerName> 441 <Nick> <kickedNick> :Is not on channel <channel>"
// 		std::ostringstream msg;
// 		msg << ":" <</* _server->getServerName() <<*/ " 441 " << _nickName << " " << nick << " :Is not on channel " << channel;
// 		//SEND ERROR MSG!!!!
// 	}
// }

// void		User::leaveChannel(std::vector<std::string>& args)
// {
// 	std::string	channel = args[0];
// 	Channel		*chPtr;

// 	//:<NICK>!<User@IP> PART <channel> :Leaving
// 	std::ostringstream msgstream;
// 	msgstream << ":" << _nickName << "!" << _userName << "@" << _ip << " PART " << channel << " :Leaving";
// 	try
// 	{
// 		//
// 		if (!(chPtr = _server->searchChannel(channel)))
// 			throw(noSuchChannel());
// 		if (chPtr->isUserInList(chPtr->getListPtrOrdinaryUsers(), this))
// 		{
// 			//broadcast msgstream
// 			chPtr->removeUserFromList(chPtr->getListPtrOrdinaryUsers(), this);
// 		}
// 		else if (chPtr->isUserInList(chPtr->getListPtrOperators(), this))
// 		{
// 			//broadcast msgstream
// 			chPtr->removeUserFromList(chPtr->getListPtrOperators(), this);
// 		}
// 		else
// 			throw(notOnTheChannel());
// 	}
// 	catch(noSuchChannel &e)
// 	{
// 		//:master.ircgod.com 403 nick1 #miau :No such channel
// 		std::ostringstream msg;
// 		msg << ":" <</* _server->getServerName() <<*/ " 403 " << _nickName << " " << channel << " :No such channel";
// 		//SEND ERROR MESSAGE!!!
// 	}
// 	catch(notOnTheChannel &e)
// 	{
// 		//:master.ircgod.com 442 nick1 #mychannel :You're not on that channel
// 		std::ostringstream msg;
// 		msg << ":" <</* _server->getServerName() <<*/ " 442 " << _nickName << " " << channel << " :You're not on that channel";
// 		//SEND ERROR MESSAGE!!!
// 	}
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
	std::vector<std::string>::iterator iterString = args.begin() + 1;

	std::ostringstream msgstream;
	msgstream << args[1].replace(args[1].find(":"), 1, "");
	// msgstream << args[1] << " ";
	for (; iterString != args.end(); ++iterString)
		msgstream << *iterString << " ";
	std::string msg = msgstream.str(); 
	
	std::cout << msg << std::endl;

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

std::string	User::argsToString(std::vector<std::string>::iterator iterBegin, std::vector<std::string>::iterator iterEnd)
{
	std::ostringstream msgstream;
	if ((*iterBegin)[0] == ':')
	{
		msgstream << (*iterBegin).replace((*iterBegin).find(":"), 1, "");
		++iterBegin;
		if (iterBegin != iterEnd && iterBegin + 1 != iterEnd)
			msgstream << " ";
	}
	for (; iterBegin != iterEnd; ++iterBegin)
	{
		msgstream << *iterBegin;
		if (iterBegin + 1 != iterEnd)
			msgstream << " ";
	}
	return (msgstream.str());
}
