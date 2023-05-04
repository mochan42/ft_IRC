#include "../inc/User.hpp"

std::string User::RPY_welcomeToServer(void)
{
	std::string	replyMessage = ":" + _server->getServerName() + " 001 " + _nickName.c_str() + " :Welcome to " + _server->getServerName() + " " + _nickName + "\n\n" \
	+ "The following commands are integrated into our Server:\n" + \
	"/NICK\n/USER\n/PASS\n/JOIN\n/MODE\n/WHO\n/TOPIC\n/INVITE\n/KICK\n/PART\n/PRIVMSG #Channel\n/PRIVMSG UserNickname\n/NOTICE #Channel\n/NOTICE UserNickname\n/QUIT\n" + 	\
	"\nHave a good time on the server.";
	return (replyMessage);
}

std::string User::RPY_newNick(std::string oldNick)
{
	std::string	replyMessage = ":" + oldNick + "!" + _userName + "@" + _ip + " NICK " + _nickName;
	return (replyMessage);
}

std::string User::RPY_registeredSucessfully()
{
	_replyMessage = "pass :successfully registered";
	return (_replyMessage);
}

std::string User::RPY_ChannelMsg(std::string message, Channel* channel)
{
	std::string	replyMessage = ":" + this->getNickName() + "!" + this->getUserName() + "@" + this->getIP() + " PRIVMSG " + channel->getChannelName() + " " + message;
	return (replyMessage);
}

std::string		User::RPY_PrivateMsg(std::string message, User* target)
{
	std::string	replyMessage = ":" + this->getNickName() + "!" + this->getUserName() + "@" + this->getIP() + " PRIVMSG " + target->getNickName() + " " + message;
	return (replyMessage);
}

std::string User::RPY_ChannelNotification(std::string message, Channel* channel)
{
	std::string	replyMessage = ":" + this->getNickName() + "!" + this->getUserName() + "@" + this->getIP() + " NOTICE " + channel->getChannelName() + " " + message;
	return (replyMessage);
}

std::string		User::RPY_PrivateNotification(std::string message, User* target)
{
	std::string	replyMessage = ":" + this->getNickName() + "!" + this->getUserName() + "@" + this->getIP() + " NOTICE " + target->getNickName() + " " + message;
	return (replyMessage);
}

std::string User::RPY_joinChannelBroadcast(Channel* channel, bool op)
{
	std::string	replyMessage;
	if (op == true)
		replyMessage = ":" + this->getNickName() + "!" + this->getNickName() + "@" + this->getIP() + " JOIN :" + channel->getChannelName();
	else
		replyMessage = ":" + this->getNickName() + "!" + this->getNickName() + "@" + this->getIP() + " JOIN " + channel->getChannelName();
	return (replyMessage);
}

std::string User::RPY_joinChannel(Channel* channel)
{
	std::string	replyMessage = "Joined channel " + channel->getChannelName() + ". You are not an operator.";
	return (replyMessage);
}

std::string User::RPY_createChannel(Channel* channel)
{
	std::string	replyMessage = "New channel " + channel->getChannelName() + " created by you. You are operator.";
	return (replyMessage);
}

std::string 	User::RPY_353_joinWho(Channel* channel)
{
	std::string replyMessage = ":" + _server->getServerName() + " 353 " + this->getNickName() + " = " + channel->getChannelName() + " :";
	std::list<User *> *listOper = channel->getListPtrOperators();
	std::list<User *>::iterator iterOper = listOper->begin();
	while (iterOper != listOper->end())
	{
		replyMessage += "@" + (*iterOper)->getNickName() + " ";
		++iterOper;
	}

	std::list<User *> *listOrden =  channel->getListPtrOrdinaryUsers();
	std::list<User *>::iterator iterOrden = listOrden->begin();
	while (iterOrden != listOrden->end())
	{
		replyMessage += (*iterOrden)->getNickName() + " ";
		++iterOrden;
	}
	return (replyMessage);	
}

std::string User::RPY_inviteMessage(std::string otherNick, std::string channel)
{
	_replyMessage = ":" + _nickName + "!" + _userName + "@" + _ip + " INVITE " + otherNick + " " + channel;
	return (_replyMessage.c_str());
}

std::string User::RPY_341_userAddedtoInviteList(std::string otherNick, std::string channel)
{
	_replyMessage = ":" + _server->getServerName() + " 341 " + _nickName + " " + otherNick + " " + channel;
	return (_replyMessage.c_str());
}

std::string User::RPY_kickedMessage(std::string otherNick, std::string channel, std::string reason)
{
	if (reason == "")
		_replyMessage = ":" + _nickName + "!" + _userName + "@" + _ip + " KICK " + channel + " " + otherNick;
	else
		_replyMessage = ":" + _nickName + "!" + _userName + "@" + _ip + " KICK " + channel + " " + otherNick + " :" + reason;
	return (_replyMessage.c_str());
}

std::string User::RPY_leaveChannel(std::string channel)
{
	_replyMessage = ":" + _nickName + "!" + _userName + "@" + _ip + " PART " + channel + " :Leaving";
	return (_replyMessage.c_str());
}

std::string User::RPY_331_channelTopic(std::string channel)
{
	_replyMessage = ":" + _server->getServerName() + " 331 " + _nickName + " " + channel + " :No topic is set.";
	return (_replyMessage.c_str());
}

std::string User::RPY_332_channelTopic(std::string channel, std::string topic)
{
	_replyMessage = ":" + _server->getServerName() + " 332 " + _nickName + " " + channel + " :" + topic;
	return (_replyMessage.c_str());
}

std::string User::RPY_newTopic(std::string channel, std::string newTopic)
{
	_replyMessage = ":" + _nickName + "!" + _userName + "@" + _ip + " TOPIC " + channel + " :" + newTopic;
	return (_replyMessage.c_str());
}

std::string User::RPY_324_printMode(std::string channel, std::string flags)
{
	_replyMessage = ":" + _server->getServerName() + " 324 " + _nickName + " " + channel + " " + flags;
	return (_replyMessage.c_str());
}

std::string User::RPY_352_whoUser(User *user, std::string channel, bool op)
{
	std::string flag = " H";
	if (op)
		flag = " H@";
	std::string mode = "xz";
	std::string own = " :3 ";
	if (user->_nickName == _nickName)
		own = " :0 ";
	_replyMessage = ":" + _server->getServerName() + " 352 " + _nickName + " " + channel + " " + user->_userName + " " + user->_ip + " " + _server->getServerName() + " " + user->_nickName + flag + mode + own + _realName;
	return (_replyMessage.c_str());
}

std::string User::RPY_315_endWhoList(std::string channel)
{
	_replyMessage = ":" + _server->getServerName() + " 315 " + _nickName + " " + channel + " :End of WHO list";
	return (_replyMessage.c_str());
}

std::string	User::RPY_ERR_commandNotfound(std::string command)
{
	std::string prefix = ":" + this->getNickName() + "!" + this->getIP() + " ";
	std::string	replyMessage = command + " : Unkown command";
	return (replyMessage);
}

std::string User::RPY_ERR462_alreadyRegistered()
{
	_replyMessage = ":" + _server->getServerName() + " 462 " + _nickName + " :Unauthorized command (already registered)";
	return (_replyMessage.c_str());
}

std::string		User::RPY_ERR451_notRegistered()
{
	_replyMessage = ":" + _server->getServerName() + " 451 " + _nickName + " :You have not registered";
	return (_replyMessage.c_str());
}

std::string User::RPY_ERR401_noSuchNickChannel(std::string nickchannel)
{
	_replyMessage = ":" + _server->getServerName() + " 401 " + _nickName + " " + nickchannel + " :No such nick/channel";
	return (_replyMessage.c_str());
}

std::string User::RPY_ERR443_alreadyOnChannel(std::string otherNick, std::string channel)
{
	_replyMessage = ":" + _server->getServerName() + " 443 " + _nickName + " " + otherNick + " " + channel + " :User is already on that channel";
	return (_replyMessage.c_str());
}

std::string User::RPY_ERR432_errorneusNickname(std::string nick)
{
	_replyMessage = ":" + _server->getServerName() + " 432 * " + nick + " :Erroneous nickname";
	return (_replyMessage.c_str());
}

std::string User::RPY_ERR433_nickInUse(std::string nick)
{
	_replyMessage = ":" + _server->getServerName() + " 433 * " + nick + " :Nickname is already in use";
	return (_replyMessage.c_str());
}

std::string User::RPY_ERR476_badChannelMask(std::string channel)
{
	_replyMessage = ":" + _server->getServerName() + " 476 " + _nickName + " " + channel + " :Bad Channel Mask";
	return (_replyMessage.c_str());
}

std::string User::RPY_ERR475_canNotJoinK(std::string channel)
{
	_replyMessage = ":" + _server->getServerName() + " 475 " + _nickName + " " + channel + " :Cannot join channel (+k)";
	return (_replyMessage.c_str());
}

std::string User::RPY_ERR473_canNotJoinI(std::string channel)
{
	_replyMessage = ":" + _server->getServerName() + " 473 " + _nickName + " " + channel + " :Cannot join channel (+i)";
	return (_replyMessage.c_str());
}

std::string User::RPY_ERR471_canNotJoinL(std::string channel)
{
	_replyMessage = ":" + _server->getServerName() + " 471 " + _nickName + " " + channel + " :Cannot join channel (+l)";
	return (_replyMessage.c_str());
}

std::string User::RPY_ERR472_unknownMode(std::string flag)
{
	_replyMessage = ":" + _server->getServerName() + " 472 " + _nickName + " " + flag + " :is unknown mode char to me";
	return (_replyMessage.c_str());
}

std::string User::RPY_ERR482_notChannelOp(std::string channel)
{
	_replyMessage = ":" + _server->getServerName() + " 482 " + _nickName + " " + channel + " :You're not channel operator";
	return (_replyMessage.c_str());
}

std::string User::RPY_ERR441_kickNotOnChannel(std::string otherNick, std::string channel)
{
	_replyMessage = ":" + _server->getServerName() + " 441 " + _nickName + " " + otherNick + " :Is not on channel " + channel;
	return (_replyMessage.c_str());
}

std::string User::RPY_ERR403_noSuchChannel(std::string channel)
{
	_replyMessage = ":" + _server->getServerName() + " 403 " + _nickName + " " + channel + " :No such channel";
	return (_replyMessage.c_str());
}

std::string User::RPY_ERR442_youreNotOnThatChannel(std::string channel)
{
	_replyMessage = ":" + _server->getServerName() + " 442 " + _nickName + " " + channel + " :You're not on that channel";
	return (_replyMessage.c_str());
}

std::string User::RPY_ERR467_keyAlreadySet(std::string channel)
{
	_replyMessage = ":" + _server->getServerName() + " 467 " + _nickName + " " + channel  + " :Channel key already set";
	return (_replyMessage.c_str());
}

std::string User::RPY_ERR461_notEnoughParametersMode(std::string flag)
{
	_replyMessage = ":" + _server->getServerName() + " 461 " + _nickName + " MODE " + flag  + " :Not enough parameters";
	return (_replyMessage.c_str());
}

std::string User::RPY_ERR464_PASSWDMISMATCH()
{
	_replyMessage = ":" + _server->getServerName() + " 464 " + ":Password incorrect";
	return (_replyMessage);
}

std::string User::RPY_ERR461_notEnoughParameters()
{
	_replyMessage = ":" + _server->getServerName() + " 461 " + ":Not enough parameters";
	return (_replyMessage);
}

std::string User::RPY_ERR404_cannotSendToChannel(std::string channel)
{
	_replyMessage = ":" + _server->getServerName() + " 404 " + _nickName + " " + channel + " :Cannot send to channel";
	return (_replyMessage.c_str());
}
