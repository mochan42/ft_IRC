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
	std::string str = msg + "\n";
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
	std::string str = msg + "\n";
	try
	{
		if (send(targetUserFd, str.c_str(), str.length(), 0) < 0)
			throw SendToTargetCLientException();
	}
	catch(const std::exception & e)
	{
		std::cerr << e.what() << '\n';
	}
	return (0);
}

int	User::getPort(void)
{
	return(this->_userPort);
}

void	User::setPort(int setUserPort)
{
	this->_userPort = setUserPort;
}

//		*!* Command execution  *!*
//		---------------------------

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
	else if (command == "MODE")
	 	mode(args);
	else if (command == "WHO")
		who(args);		
	// else if (command == "")
	// 	changeTopic(args);
	else if (command == "INVITE")
		inviteUser(args);
	else if (command == "KICK")
		kickUser(args);
	else if (command == "PART")
		leaveChannel(args);
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
	//check if the nick already exist
	//Send to all Users who are in the channel with this user!!!
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
			sendMsgToOwnClient(RPY_who(channelPtr));
			// std::list<User *> *opList = channelPtr->getListPtrOperators();
			// std::list<User *> *ordinaryList = channelPtr->getListPtrOrdinaryUsers();
			// std::list<User *>::iterator it = opList->begin();


			// while (it != opList->end())
			// {
			// 	sendMsgToOwnClient((*it)->RPY_352_whoUser(_nickName, channel, channelPtr->isUserInList(opList, *it)));
			// 	++it;
			// }
			// it = ordinaryList->begin();
			// while (it != ordinaryList->end())
			// {
			// 	sendMsgToOwnClient((*it)->RPY_352_whoUser(_nickName, channel, channelPtr->isUserInList(ordinaryList, *it)));
			// 	++it;
			// }

			// while (it != opList->end())											// same loop like the above, but with RPY_352 with pointer instead of string, only one should be used
			// {
			// 	sendMsgToOwnClient(RPY_352_whoUser(*it, channel, true));						
			// 	++it;
			// }
			// it = ordinaryList->begin();
			// while (it != ordinaryList->end())
			// {
			// 	sendMsgToOwnClient(RPY_352_whoUser(*it, channel, false));
			// 	++it;
			// }
		}
		sendMsgToOwnClient(RPY_315_endWhoList(channel));
	}
	else //handle single user
	{
		std::string user = args[0];
		User *userptr = _server->getUser(user);

		if (userptr)
			sendMsgToOwnClient(userptr->RPY_352_whoUser(userptr, "*", false));
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
			chptr->updateUserList(chptr->getListPtrInvitedUsers(), user, USR_ADD);
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
			_server->createChannel(args[0], "", this);
			chptr = _server->getChannel(args[0]);									// only necessary because no return of channel			

			chptr->broadcastMsg(RPY_joinChannelBroadcast(chptr, true), std::make_pair(false, (User *) NULL));
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
			chptr->updateUserList(chptr->getListPtrOrdinaryUsers(), this, USR_ADD);
			sendMsgToOwnClient(RPY_joinChannel(chptr));
			chptr->broadcastMsg(RPY_joinChannelBroadcast(chptr, false), std::make_pair(false, (User *) NULL));
			
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
void		User::kickUser(std::vector<std::string>& args)
{
	std::string channel = args[0];
	std::string nick = args[1];
	std::string reason = argsToString(args.begin() + 2, args.end());
	Channel *channelPtr;
	User	*tmpUser;
	
	try
	{
		channelPtr = _server->getChannel(channel);
		if (!channelPtr->isUserInList(channelPtr->getListPtrOperators(), this))
			throw (notAnOperator());

		if ((tmpUser = channelPtr->isUserInChannel(nick)))
		{
			channelPtr->broadcastMsg(RPY_kickedMessage(nick, channel), std::make_pair(false, (User *) NULL));
			if (channelPtr->isUserInList(channelPtr->getListPtrOperators(), tmpUser))
				channelPtr->updateUserList(channelPtr->getListPtrOperators(), tmpUser, USR_REMOVE);
			if (channelPtr->isUserInList(channelPtr->getListPtrOrdinaryUsers(), tmpUser))
				channelPtr->updateUserList(channelPtr->getListPtrOrdinaryUsers(), tmpUser, USR_REMOVE);
		}
		else
			throw (notOnTheChannel());
	}
	catch (notAnOperator &e)
	{
		(void)e;
		sendMsgToOwnClient(RPY_ERR482_notChannelOp(channel));
	}
	catch (notOnTheChannel &e)
	{
		(void)e;
		sendMsgToOwnClient(RPY_ERR441_kickNotOnChannel(nick, channel));
	}
}

/**
 * @brief 
 * Function to leave a channel and inform all user in the channel about it.
 * @param args All arguments after the cmd
 */
void		User::leaveChannel(std::vector<std::string>& args)
{
	std::string	channel = args[0];
	Channel		*chPtr;

	try
	{
		//
		if (!(chPtr = _server->getChannel(channel)))
			throw(noSuchChannel());
		if (chPtr->isUserInList(chPtr->getListPtrOrdinaryUsers(), this))
		{
			chPtr->broadcastMsg(RPY_leaveChannel(channel), std::make_pair(false, (User *) NULL));
			chPtr->updateUserList(chPtr->getListPtrOrdinaryUsers(), this, USR_REMOVE);
		}
		else if (chPtr->isUserInList(chPtr->getListPtrOperators(), this))
		{
			chPtr->broadcastMsg(RPY_leaveChannel(channel), std::make_pair(false, (User *) NULL));
			chPtr->updateUserList(chPtr->getListPtrOperators(), this, USR_REMOVE);
		}
		else
			throw(notOnTheChannel());
	}
	catch(noSuchChannel &e)
	{
		(void)e;
		sendMsgToOwnClient(RPY_ERR403_noSuchChannel(channel));
	}
	catch(notOnTheChannel &e)
	{
		(void)e;
		sendMsgToOwnClient(RPY_ERR442_youreNotOnThatChannel(channel));
	}
}

// void		User::modifyChannel(std::string channelName, std::string nickName, char mode)
// {

// }
void 	User::setInviteOnly(const std::string& channel){
		std::cout << "set Channel " << channel <<" to invite only, if enough rights."<< std::endl;
		}

void 	User::remoInviteOnly(const std::string& channel){
		std::cout << "remove Channel " << channel <<" from invite only, if enough rights."<< std::endl;
		}

void 	User::setTopicRestrictions(const std::string& channel){
		std::cout << "set to Channel " << channel <<" topic restrictions, if enough rights."<< std::endl;
		}

void 	User::removeTopicRestrictions(const std::string& channel){
		std::cout << "remove from Channel " << channel <<" topic restrictions, if enough rights."<< std::endl;
		}

void 	User::setChannelKey(const std::string& channel, const std::string& key){
		std::cout << "set to Channel " << channel <<" password " << key << ", if enough rights."<< std::endl;
		}

void 	User::removeChannelKey(const std::string& channel){
		std::cout << "remove from Channel " << channel <<" password, if enough rights."<< std::endl;
		}

void 	User::giveChanopPrivileges(const std::string& channel, const std::string& username){
		std::cout << "Give user " << username << " chanop rights on Channel " << channel <<", if enough rights."<< std::endl;
		}

void 	User::removeChanopPrivileges(const std::string& channel, const std::string& username){
		std::cout << "Remove user " << username << " chanop rights on Channel " << channel <<", if enough rights."<< std::endl;
		}

void 	User::setUserLimit(const std::string& channel, int limit){
		std::cout << "Set userlimit on Channel " << channel <<" to " << limit << ", if enough rights."<< std::endl;
		}

void 	User::removeUserLimit(const std::string& channel){
		std::cout << "Remove userlimit on Channel " << channel <<", if enough rights."<< std::endl;
		}


void	User::mode(std::vector<std::string>& args)
{
 	modeParser parser(args);
	std::vector<std::pair<std::string, std::string> > flagArgsPairs = parser.getflagArgsPairs();
    for (size_t i = 0; i < flagArgsPairs.size(); ++i) {
        std::string flag = flagArgsPairs[i].first;
        std::string arguments = flagArgsPairs[i].second;
        std::string channel = parser.getChannel();

        switch (flag[1]) {
            case 'i': //Set/remove Invite-only channel
                if (flag[0] == '+') {
                    setInviteOnly(channel);
                } else {
                    remoInviteOnly(channel);
                }
                break;
			case 't': //Set/remove the restrictions of the TOPIC command to channel operators
                if (flag[0] == '+') {
                    setTopicRestrictions(channel);
                } else {
                    removeTopicRestrictions(channel);
                }
                break;
			
			case 'k': //Set/remove the channel key (password)
                if (flag[0] == '+') {
                    setChannelKey(channel, arguments);
                } else {
                    removeChannelKey(channel);
                }
                break;
			
			case 'o': //Give/take channel operator privilege
                if (flag[0] == '+') {
                    giveChanopPrivileges(channel, arguments);
                } else {
                    removeChanopPrivileges(channel, arguments);
                }
                break;
			
			case 'l': //Set/remove the user limit to channel
                if (flag[0] == '+') {
                    setUserLimit(channel, std::atoi(arguments.c_str()));
                } else {
                    removeUserLimit(channel);
                }
                break;	
            
            default:
                std::cout << "Unknown mode: " << flag << std::endl;
        }
    }
}

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
		std::cout << "User::sendNotification called with Channel =      " << args[0] << std::endl;

		Channel *chptr = _server->getChannel(args[0]);
		if (chptr != NULL) 
			chptr->broadcastMsg(RPY_ChannelNotification(args[1], chptr), std::make_pair(true, (User *) this));
		// else
			// execption Channel dont exists
	}
	else
	{
		std::cout << std::endl << std::endl << "User::sendNotification called with nickname of target:   <" << args[0] << ">" << std::endl;

		User *target = _server->getUser(args[0]);
		if (target != NULL)
		{
			sendMsgToTargetClient(RPY_PrivateNotification(args[1], target), target->getFd());
		}
		// else
		// {
		// 		// 	message and exception that User is not found
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
	if (chptr != NULL)
		chptr->broadcastMsg(RPY_ChannelMsg(args[1], chptr), std::make_pair(true, (User *) this));
	// else
		// execption and message Channel dont exists
		
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
		sendMsgToTargetClient(RPY_PrivateMsg(args[1], target), target->getFd());
	}
	// else
	// {
	// 		// 	message and exception that User is not found
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
