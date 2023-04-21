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
	this->_usernameSet = false;
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
	this->_usernameSet = src._usernameSet;
	return (*this);
}

User::~User()
{
	std::cout << "User " << this->getUserName() << " removed from server." << std::endl;
}

//		*!* MSG transmission and Command execution *!*
//		----------------------------------------------

/**
 * @brief 
 * function to send a message 'msg' to the client of this user.
 *
 * @param msg std::string
 */
int			User::sendMsgToOwnClient(std::string msg)
{
	std::string str = msg + "\r\n"; 
	try
	{
		if (send(this->_userFd, str.c_str(), str.length(), 0) < 0)
			throw SendToOwnCLientException();
	}
	catch(const std::exception & e)
	{
		std::cerr << e.what() << '\n';
	}
	return (0);
}


/**
 * @brief 
 * function to send a message 'msg' to the user client with fd 'targetUserFd'.
 *
 * @param msg std::string
 * @param targetUserFd int
 */
int			User::sendMsgToTargetClient(std::string msg, int targetUserFd)
{
	try
	{
		if (send(targetUserFd, msg.c_str(), msg.length(), 0) < 0)
			throw SendToTargetCLientException();
	}
	catch(const std::exception & e)
	{
		std::cerr << e.what() << '\n';
	}
	return (0);
}

/**
 * @brief 
 * function to call the received command.
 *
 * @param command std::string
 * @param args std::vector < std::string >
 */
void		User::executeCommand(std::string command, std::vector<std::string>& args)
{
	for (size_t i = 0; i < command.length(); i++)
			command[i] = std::toupper(command[i]);

	std::cout << "User::executeCommand called with command = " << command <<  std::endl;
	if (command == "CAP")
		sendMsgToOwnClient(RPY_welcomeToServer());
	else if (command == "NICK")
		setNickName(args);
	else if (command == "USER")
		setUserName(args);
	else if (command == "REAL")
		setRealName(args);
	else if (command == "PASS")
		setServerPw(args);
	else if (command == "JOIN")
		joinChannel(args);
	// else if (command == "MODE")
	// 	mode(args);
	// else if (command == "WHO")
	// 	who(args);		
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
	else if (command == "NOTICE")
		sendNotification(args);
	else if (command == "PRIVMSG")
	{
		if (args[0].at(0) == '#')
			sendChannelMsg(args);
		else
			sendPrivateMsg(args);
	}
	// else if (command == "")
	// 	isOperator(args);
	else
	{
		sendMsgToOwnClient(RPY_ERR_commandNotfound(command));
		std::cout << _replyMessage << std::endl;
	}
}

//		*!* NAME and ID Handling  *!*
//		-----------------------------

int			User::getFd(void)
{
	return (this->_userFd);
}

std::string		User::getIP(void)
{
	return (this->_ip);
}

void		User::setServerPw(const std::vector<std::string>& args)
{
	_pw = args[0];
	if (this->_server->verifyPassword(_pw))
	{
		_isRegistered = true;
		sendMsgToOwnClient(RPY_pass(true));
	}
	else
		sendMsgToOwnClient(RPY_pass(false));
	std::cout << "User::setServerPw called. The _pw is now:  " << _pw << std::endl;
}

void		User::setNickName(const std::vector<std::string>& args)
{
	std::string oldNick = _nickName;
	_nickName = args[0];
	sendMsgToOwnClient(RPY_newNick(oldNick));
	std::cout << "User::setNickname called. The _nickName is now:  " << this->getNickName() << std::endl;
}

std::string	User::getNickName(void)
{
	return (this->_nickName);
}

void		User::setUserName(std::vector<std::string>& args)
{

	if (_usernameSet == true)
	{
		sendMsgToOwnClient(RPY_ERR462_alreadyRegistered());
	}
	else
	{
		_userName = args[0];
		_realName = argsToString(args.begin() + 3, args.end());
		_usernameSet = true;
		//Welcome Message could be send here
	}
	std::cout << "User::setUserName called. The _UserName is now:  " << this->getUserName() << std::endl;
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


//		*!* CHANNEL interacting  *!*
//		----------------------------


void		User::who(std::vector<std::string>& args)
{
	if (args.size() == 0)
		return;
	if (args[0][0] == '#') //handle channel
	{
		std::string channel = args[0];
		Channel *channelPtr = _server->getChannel(channel);
		if (channelPtr)
		{
			std::list<User *> *userList = channelPtr->getListPtrOperators();
			std::list<User *>::iterator it = userList->begin();
			while (it != userList->end())
			{
				sendMsgToOwnClient((*it)->RPY_352_whoUser(_nickName, channel, channelPtr->isUserInList(channelPtr->getListPtrOperators(), *it)));
				++it;
			}
		}
		sendMsgToOwnClient(RPY_315_endWhoList(channel));
	}
	else //handle single user
	{
		std::string user = args[0];
		User *userptr = _server->getUser(user);

		if (userptr)
			sendMsgToOwnClient(userptr->RPY_352_whoUser(_nickName, "*", false));
		sendMsgToOwnClient(RPY_315_endWhoList(user));
	}
}

void		User::changeTopic(std::vector<std::string>& args)
{
	std::string channel = args[0];
	Channel *chnptr = _server->getChannel(channel);
	if (!chnptr)
		sendMsgToOwnClient(RPY_ERR401_noSuchNickChannel(channel));
	if (args.size() == 1)
	{
		sendMsgToOwnClient(RPY_332_channelTopic(channel, chnptr->getTopic()));
	}
	else
	{
		std::string newTopic = argsToString(args.begin() + 1, args.end());
		chnptr->setTopic(newTopic);
		chnptr->broadcastMsg(RPY_newTopic(channel, newTopic), std::make_pair(false, (User *) NULL));
	}
}


void 		User::inviteUser(std::vector<std::string>& args)
{
	std::string nick = args[0];
	std::string channel = args[1];

	User *user = _server->getUser(nick);
	Channel	*chptr = _server->getChannel(channel);
	if (!user)
		sendMsgToOwnClient(RPY_ERR401_noSuchNickChannel(nick));
	else if (!chptr)
		sendMsgToOwnClient(RPY_ERR401_noSuchNickChannel(channel));
	else
	{
		if (chptr->isUserInChannel(nick) != NULL)
			sendMsgToOwnClient(RPY_ERR443_alreadyOnChannel(nick, channel));
		else
		{
			chptr->addUserToList(chptr->getListPtrInvitedUsers(), user);
			sendMsgToOwnClient(RPY_341_userAddedtoInviteList(nick, channel));
			//!!!     write to other person:   !!!!
			user->sendMsgToOwnClient(RPY_inviteMessage(nick, channel));
			//check if that works later
		}
	}
}


/**
 * @brief
 * function to add a user to a channel
 * or create a new channel and add the user to it
 * @param args All arguments after the cmd
 */
void		User::joinChannel(std::vector<std::string>& args)
{
	std::cout << "USER::joinChannel called." << std::endl;
	try
	{
		if (args[0][0] != '#')
			throw (badChannelMask());
		Channel *chptr = _server->getChannel(args[0]);
		if (chptr == NULL) //Create channel
		{

			std::cout << "Channel don't exists. Server::createChannel called." << std::endl;
			_server->createChannel(args[0], "Topic", this);
			chptr = _server->getChannel(args[0]);									// only necessary because no return of channel
			chptr->addUserToList(chptr->getListPtrOperators(), this);	
			chptr->broadcastMsg(RPY_joinChannelBroadcast(chptr), std::make_pair(false, (User *) NULL));
			sendMsgToOwnClient(RPY_createChannel(chptr));
		}
		else //join channel
		{
			// if (boolean ChannelKey == 1)
			// {
			// 	if (!args[1] || chptr->password != args[1])
			// 		throw (cannotJoinChannelPW());
			// }
			// if (boolean isInviteOnly == 1)
			// {
			// 	if (!chptr->isUserInList(chptr->getListPtrInvitedUsers(), this))
			// 		throw (cannotJoinChannelIn());
			// 	else
			// 		chptr->updateUserList(chptr->getListPtrInvitedUsers(), this, USR_REMOVE);
			// }
			// if (chptr->getChannelCapacity() <= chptr->getUserNum())
			// 	throw (channelCapacity());
			chptr->addUserToList(chptr->getListPtrOrdinaryUsers(), this);
			chptr->broadcastMsg(RPY_joinChannelBroadcast(chptr), std::make_pair(false, (User *) NULL));
			sendMsgToOwnClient(RPY_joinChannel(chptr));
		}
		// std::ostringstream msgadd;
		// msgadd << ":" << _nickName << "!" << _userName << "@" << _ip << " JOIN " << args[0];
		// chptr->broadcastMsg(msgadd.str());
	}
	catch (badChannelMask &e)
	{
		(void)e;
		sendMsgToOwnClient(RPY_ERR476_badChannelMask(args[0]));
	}
	catch (cannotJoinChannelPW &e)
	{
		(void)e;
		sendMsgToOwnClient(RPY_ERR475_canNotJoinK(args[0]));
	}
	catch (cannotJoinChannelIn &e)
	{
		(void)e;
		sendMsgToOwnClient(RPY_ERR473_canNotJoinI(args[0]));
	}
	catch (channelCapacity &e)
	{
		(void)e;
		sendMsgToOwnClient(RPY_ERR471_canNotJoinL(args[0]));
	}
}

/**
 * @brief 
 * Will kick a user from a channel and inform all other user on the channel about it.
 * @param args All arguments after the cmd
 */
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
// 			channelPtr->broadcastMsg(RPY_kickedMessage(nick, channel));
			
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
// 		(void)e;
// 		sendMsgToOwnClient(RPY_ERR482_notChannelOp(channel));
// 	}
// 	catch (notOnTheChannel &e)
// 	{
// 		(void)e;
// 		sendMsgToOwnClient(RPY_ERR441_kickNotOnChannel(nick, channel));
// 	}
// }

/**
 * @brief 
 * Function to leave a channel and inform all user in the channel about it.
 * @param args All arguments after the cmd
 */
// void		User::leaveChannel(std::vector<std::string>& args)
// {
// 	std::string	channel = args[0];
// 	Channel		*chPtr;

// 	try
// 	{
// 		//
// 		if (!(chPtr = _server->searchChannel(channel)))
// 			throw(noSuchChannel());
// 		if (chPtr->isUserInList(chPtr->getListPtrOrdinaryUsers(), this))
// 		{
// 			chPtr->broadcastMsg(RPY_leaveChannel(channel));
// 			chPtr->removeUserFromList(chPtr->getListPtrOrdinaryUsers(), this);
// 		}
// 		else if (chPtr->isUserInList(chPtr->getListPtrOperators(), this))
// 		{
// 			chPtr->broadcastMsg(RPY_leaveChannel(channel));
// 			chPtr->removeUserFromList(chPtr->getListPtrOperators(), this);
// 		}
// 		else
// 			throw(notOnTheChannel());
// 	}
// 	catch(noSuchChannel &e)
// 	{
// 		(void)e;
// 		sendMsgToOwnClient(RPY_ERR403_noSuchChannel(channel));
// 	}
// 	catch(notOnTheChannel &e)
// 	{
// 		(void)e;
// 		sendMsgToOwnClient(RPY_ERR442_youreNotOnThatChannel(channel));
// 	}
// }

// void		User::modifyChannel(std::string channelName, std::string nickName, char mode)
// {

// }

// //		*!* MESSAGES  *!*
// //		-----------------

/**
 * @brief 
 * function to send a notification to all users in a channel or one user.
 *
 * @param args std::vector < std::string >
 */
void	User::sendNotification(std::vector<std::string>& args)
{
	if (args[0].at(0) == '#')
	{
		std::list<Channel *>::iterator iterChannel;
		// for (iterChannel = _channelList.begin(); iterChannel != _channelList.end(); iterChannel++)
		// {
			// if (args[0] == (*iterChannel)->getChannelName())     // with or without # at beginn ?
			// {
					std::ostringstream msgstream;
					std::vector<std::string>::iterator iterString = args.begin() + 1;
					msgstream << ":" << this->getNickName() << "!" << this->getUserName() << "@" << this->getIP() << " NOTICE " << args[0] << " ";
					for (; iterString != args.end(); ++iterString)
						msgstream << *iterString << " ";
					std::string msg = msgstream.str(); 
					std::cout << msg << std::endl;
				// (*iterChannel)->broadcastMsg(msg);     // send to all users in this channel but not to this user
				// std::cout << "User " << this->getUserName() << "with fd = " << this->getFd() << "sends a message to channel \'" << /*(*iterChannel)->getChannelName() << */ "\'." << std::endl;
			// 	break;
			// }
		// }
		// if (iterChannel == _channelList.end())
		// {
		// 	std::ostringstream msgstream;
		// 	msgstream << args[0] << " : No such Channel";
		// 	std::string msg = msgstream.str();
		// 	std::cout << msg << std::endl;
		// 	this->sendMsgToOwnClient(msg);
		// }
	}
	else
	{
		std::list<User *>::iterator iterUser;	
		// for (iterUser = _server.userList.begin(); iterUser != _server.userList.end(); iterUser++)
		// {
		// 	if (args[0] == (*iterUser)->getUserName())
		// 	{
				std::ostringstream msgstream;
				std::vector<std::string>::iterator iterString = args.begin() + 1;
				msgstream << ":" << this->getNickName() << "!" << this->getUserName() << "@" << this->getIP() << " NOTICE " << args[0] << " ";
				for (; iterString != args.end(); ++iterString)
				msgstream << *iterString << " ";
				std::string msg = msgstream.str();
				std::cout << msg << std::endl;
		// 		this->sendMsgToTargetClient(msg, (*iterUser)->getFd());

		// 		break;
				// std::cout << "User " << this->getUserName() << "with fd = " << this->getFd() << "sends a message to User \'" << /* args[2] << */ "\' with fd = " << /*args[3] << */ std::endl;
		// 	}
		// }
		// if (iterUser == _server.userList.end())
		// {
		// 	std::ostringstream msgstream;
		// 	msgstream << args[0] << " : No such user";
		// 	std::string msg = msgstream.str();
		// 	std::cout << msg << std::endl;
		// 	this->sendMsgToOwnClient(msg);
		// }
	}
}

/**
 * @brief 
 * function to send a message to all users in the channel.
 *
 * @param args std::vector < std::string >
 */
int		User::sendChannelMsg(std::vector<std::string>& args)
{
	std::cout << "User::sendChannelMsg called with Channel =      " << args[0] << std::endl;

	Channel *chptr = _server->getChannel(args[0]);
	if (chptr == NULL) 
		(void) chptr;	// execption Channel dont exists
	else
		chptr->broadcastMsg(RPY_ChannelMsg(args[1], chptr), std::make_pair(true, (User *) this));



	// std::ostringstream msgstream;
	// std::vector<std::string>::iterator iterString = args.begin() + 1;
	// msgstream << ":" << this->getNickName() << "!" << this->getUserName() << "@" << this->getIP() << " PRIVMSG " << args[0] << " ";
	// for (; iterString != args.end(); ++iterString)
	// 	msgstream << *iterString << " ";
	// std::string msg = msgstream.str(); 
	// std::cout << msg << std::endl;
			// (*iterChannel)->broadcastMsg(msg);     // send to all users in this channel but not to this user
			// std::cout << "User " << this->getUserName() << "with fd = " << this->getFd() << "sends a message to channel \'" << /*(*iterChannel)->getChannelName() << */ "\'." << std::endl;
		// 	break;
		// }
	// }
	// if (iterChannel == _channelList.end())
	// {
	// 	std::ostringstream msgstream;
	// 	msgstream << args[0] << " : No such Channel";
	// 	std::string msg = msgstream.str();
	// 	std::cout << msg << std::endl;
	// 	this->sendMsgToOwnClient(msg);
	// }
	return (0);
}

/**
 * @brief 
 * function to send a message to one user.
 *
 * @param args std::vector < std::string >
 */
int		User::sendPrivateMsg(std::vector<std::string>& args)
{
	std::cout << std::endl << std::endl << "User::sendPrivateMsg called. The nickname of target is:   <" << args[0] << ">" << std::endl;
	User *target = _server->getUser(args[0]);

	if (target != NULL)
	{
		std::cout << "User found at server !" << std::endl;
		std::ostringstream msgstream;
		std::vector<std::string>::iterator iterString = args.begin() + 1;
		msgstream << ":" << this->getNickName() << "!" << this->getUserName() << "@" << this->getIP() << " PRIVMSG " << args[0] << " ";
		for (; iterString != args.end(); ++iterString)
		msgstream << *iterString << " ";
		std::string msg = msgstream.str();
		std::cout << msg << std::endl;
		this->sendMsgToTargetClient(msg, target->getFd());
		std::cout << "User " << this->getUserName() << " with fd = " << this->getFd() << " sends a message to User \'" << target->getUserName() <<  "\' with fd = " <<  target->getFd() << std::endl;
		std::cout << "The message is: 	" << msg << std::endl;
		// break;
	}
	// else
	// {
	// 	std::ostringstream msgstream;
	// 	msgstream << args[0] << " : No such user";
	// 	std::string msg = msgstream.str();
	// 	std::cout << msg << std::endl;
	// 	this->sendMsgToOwnClient(msg);
	// }
	return (0);
}


// //		*!* OTHERS  *!*
// //		------------------------------------


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
